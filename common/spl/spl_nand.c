/*
 * Copyright (C) 2011
 * Corscience GmbH & Co. KG - Simon Schwarz <schwarz@corscience.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <config.h>
#include <spl.h>
#include <asm/io.h>
#include <nand.h>
#include <libfdt_env.h>
#include <fdt.h>

#if defined(CONFIG_SPL_NAND_RAW_ONLY)
int spl_nand_load_image(void)
{
	nand_init();

	nand_spl_load_image(CONFIG_SYS_NAND_U_BOOT_OFFS,
			    CONFIG_SYS_NAND_U_BOOT_SIZE,
			    (void *)CONFIG_SYS_NAND_U_BOOT_DST);
	spl_set_header_raw_uboot();
	nand_deselect();

	return 0;
}
#else

static ulong spl_nand_fit_read(struct spl_load_info *load, ulong offs,
			       ulong size, void *dst)
{
	int ret;

	ret = nand_spl_load_image(offs, size, dst);
	if (!ret)
		return size;
	else
		return 0;
}

static int spl_nand_load_element(int offset, struct image_header *header)
{
	int err;

	err = nand_spl_load_image(offset, sizeof(*header), (void *)header);
	if (err)
		return err;

	if (IS_ENABLED(CONFIG_SPL_LOAD_FIT) &&
	    image_get_magic(header) == FDT_MAGIC) {
		struct spl_load_info load;

		debug("Found FIT\n");
		load.dev = NULL;
		load.priv = NULL;
		load.filename = NULL;
		load.bl_len = 1;
		load.read = spl_nand_fit_read;
		return spl_load_simple_fit(&load, offset, header);
	} else {
		err = spl_parse_image_header(header);
		if(err!=0){
			printf("\n spl: nand  error image header at 0x%x !\n", offset);
			return err;
		}
		
		nand_spl_load_image(offset, spl_image.size,
					   (void *)spl_image.load_addr);

		u32 dcrc = crc32(0, (const unsigned char *)spl_image.entry_point, spl_image.size-sizeof(struct image_header));
		
		debug("spl: nand u-boot dcrc = 0x%x, header->ih_dcrc= 0x%x\n", dcrc, spl_image.dcrc);
		if(dcrc == spl_image.dcrc){
				return 0;
		}
		else
		{
			return 1;
		}
	}
}

int spl_nand_load_image(void)
{
	int err;
	struct image_header *header;
	int *src __attribute__((unused));
	int *dst __attribute__((unused));

#ifdef CONFIG_SPL_NAND_SOFTECC
	debug("spl: nand - using sw ecc\n");
#else
	debug("spl: nand - using hw ecc\n");
#endif
	nand_init();

	/*use CONFIG_SYS_TEXT_BASE as temporary storage area */
	header = (struct image_header *)(CONFIG_SYS_TEXT_BASE);
#ifdef CONFIG_SPL_OS_BOOT
	if (!spl_start_uboot()) {
		/*
		 * load parameter image
		 * load to temp position since nand_spl_load_image reads
		 * a whole block which is typically larger than
		 * CONFIG_CMD_SPL_WRITE_SIZE therefore may overwrite
		 * following sections like BSS
		 */
		nand_spl_load_image(CONFIG_CMD_SPL_NAND_OFS,
			CONFIG_CMD_SPL_WRITE_SIZE,
			(void *)CONFIG_SYS_TEXT_BASE);
		/* copy to destintion */
		for (dst = (int *)CONFIG_SYS_SPL_ARGS_ADDR,
				src = (int *)CONFIG_SYS_TEXT_BASE;
				src < (int *)(CONFIG_SYS_TEXT_BASE +
				CONFIG_CMD_SPL_WRITE_SIZE);
				src++, dst++) {
			writel(readl(src), dst);
		}

		/* load linux */
		nand_spl_load_image(CONFIG_SYS_NAND_SPL_KERNEL_OFFS,
			sizeof(*header), (void *)header);
		spl_parse_image_header(header);
		if (header->ih_os == IH_OS_LINUX) {
			/* happy - was a linux */
			err = nand_spl_load_image(
				CONFIG_SYS_NAND_SPL_KERNEL_OFFS,
				spl_image.size,
				(void *)spl_image.load_addr);
			nand_deselect();
			return err;
		} else {
			puts("The Expected Linux image was not "
				"found. Please check your NAND "
				"configuration.\n");
			puts("Trying to start u-boot now...\n");
		}
	}
#endif
#ifdef CONFIG_NAND_ENV_DST
	debug("CONFIG_NAND_ENV_DST\n");
	spl_nand_load_element(CONFIG_ENV_OFFSET, header);
	debug("CONFIG_NAND_ENV_DST.\n");
#ifdef CONFIG_ENV_OFFSET_REDUND
	debug("CONFIG_ENV_OFFSET_REDUND\n");
	spl_nand_load_element(CONFIG_ENV_OFFSET_REDUND, header);
	debug("CONFIG_ENV_OFFSET_REDUND.\n");
#endif
#endif
	/* Load u-boot */
	debug("CONFIG_SYS_NAND_U_BOOT_OFFS\n");
	err = spl_nand_load_element(CONFIG_SYS_NAND_U_BOOT_OFFS, header);
	debug("CONFIG_SYS_NAND_U_BOOT_OFFS.\n");
#ifdef CONFIG_MYIR_UBOOT_BACKUP	
	if(err!=0){
		debug("CONFIG_SYS_NAND_U_BOOT1_OFFS\n");
		err = spl_nand_load_element(CONFIG_SYS_NAND_U_BOOT1_OFFS, header);
		debug("CONFIG_SYS_NAND_U_BOOT1_OFFS.\n");
	}
	else
	{
		spl_set_uboot_id(0);
		nand_deselect();
		return err;
	}

	if(err!=0){
		debug("CONFIG_SYS_NAND_U_BOOT2_OFFS\n");
		err = spl_nand_load_element(CONFIG_SYS_NAND_U_BOOT2_OFFS, header);
		debug("CONFIG_SYS_NAND_U_BOOT2_OFFS.\n");
		spl_set_uboot_id(2);
	}	
	else
	{
		spl_set_uboot_id(1);
	}
#endif	
	nand_deselect();
	return err;
}
#endif
