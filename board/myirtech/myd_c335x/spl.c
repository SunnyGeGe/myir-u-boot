/*
 * SPL specific code for MYIR Tech MYD-C335X board
 *
 * Copyright (C) 2016, MYIR Tech Ltd - http://www.myirtech.com/
 *
 * Author: Sunny Guo <sunny.guo@myirtech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <common.h>
#include <errno.h>

#include <asm/arch/ddr_defs.h>
#include <asm/arch/clock.h>
#include <asm/arch/clocks_am33xx.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/hardware_am33xx.h>
#include <linux/sizes.h>

const struct ctrl_ioregs ioregs = {
	.cm0ioctl		= MT41J128MJT125_IOCTRL_VALUE,
	.cm1ioctl		= MT41J128MJT125_IOCTRL_VALUE,
	.cm2ioctl		= MT41J128MJT125_IOCTRL_VALUE,
	.dt0ioctl		= MT41J128MJT125_IOCTRL_VALUE,
	.dt1ioctl		= MT41J128MJT125_IOCTRL_VALUE,
};

static const struct ddr_data ddr3_data = {
	.datardsratio0		= MT41J128MJT125_RD_DQS_400MHz,
	.datawdsratio0		= MT41J128MJT125_WR_DQS_400MHz,
	.datafwsratio0		= MT41J128MJT125_PHY_FIFO_WE_400MHz,
	.datawrsratio0		= MT41J128MJT125_PHY_WR_DATA_400MHz,
};

static const struct cmd_control ddr3_cmd_ctrl_data = {
	.cmd0csratio		= MT41J128MJT125_RATIO_400MHz,
	.cmd0iclkout		= MT41J128MJT125_INVERT_CLKOUT_400MHz,

	.cmd1csratio		= MT41J128MJT125_RATIO_400MHz,
	.cmd1iclkout		= MT41J128MJT125_INVERT_CLKOUT_400MHz,

	.cmd2csratio		= MT41J128MJT125_RATIO_400MHz,
	.cmd2iclkout		= MT41J128MJT125_INVERT_CLKOUT_400MHz,
};

static struct emif_regs ddr3_emif_reg_data = {
	.sdram_config		= MT41J128MJT125_EMIF_SDCFG_400MHz,
	.ref_ctrl		= MT41J128MJT125_EMIF_SDREF_400MHz,
	.sdram_tim1		= MT41J128MJT125_EMIF_TIM1_400MHz,
	.sdram_tim2		= MT41J128MJT125_EMIF_TIM2_400MHz,
	.sdram_tim3		= MT41J128MJT125_EMIF_TIM3_400MHz,
	.zq_config		= MT41J128MJT125_ZQ_CFG_400MHz,
	.emif_ddr_phy_ctlr_1	= MT41J128MJT125_EMIF_READ_LATENCY_400MHz|
					PHY_EN_DYN_PWRDN,
};

const struct dpll_params dpll_ddr = {
/*       M           N            M2  M3  M4  M5  M6 */
	400, (V_OSCK/1000000) - 1, 1, -1, -1, -1, -1};

void am33xx_spl_board_init(void)
{
	struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

	/* Get the frequency */
	dpll_mpu_opp100.m = am335x_get_efuse_mpu_max_freq(cdev);

	/* Set CORE Frequencies to OPP100 */
	do_setup_dpll(&dpll_core_regs, &dpll_core_opp100);

	/* Set MPU Frequency to what we detected now that voltages are set */
	do_setup_dpll(&dpll_mpu_regs, &dpll_mpu_opp100);
}

const struct dpll_params *get_dpll_ddr_params(void)
{
	return &dpll_ddr;
}

static void probe_sdram_size(long size)
{
	switch (size) {
	case SZ_512M:
		ddr3_emif_reg_data.sdram_config = MT41J256MJT125_EMIF_SDCFG;
		break;
	case SZ_256M:
//		ddr3_emif_reg_data.sdram_config = MT41J128MJT125_EMIF_SDCFG;
		ddr3_emif_reg_data.sdram_config = MT41J128MJT125_EMIF_SDCFG_400MHz;
		break;
	case SZ_128M:
		ddr3_emif_reg_data.sdram_config = MT41J64MJT125_EMIF_SDCFG;
		break;
	default:
		puts("Failed configuring DRAM, resetting...\n\n");
		reset_cpu(0);
	}
	debug("%s: setting DRAM size to %ldM\n", __func__, size >> 20);
	config_ddr(400, &ioregs, &ddr3_data,
		   &ddr3_cmd_ctrl_data, &ddr3_emif_reg_data, 0);
}

void sdram_init(void)
{
	long size = SZ_1G;

	do {
		size = size / 2;
		probe_sdram_size(size);
	} while (get_ram_size((void *)CONFIG_SYS_SDRAM_BASE, size) < size);

	return;
}
