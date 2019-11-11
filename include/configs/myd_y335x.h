/*
 * Config file for MYIR Tech MYD_Y335X board
 *
 * Copyright (C) 2016, MYIR Tech Ltd - http://www.myirtech.com/
 *
 * Author: Sunny Guo <sunny.guo@myirtech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef __CONFIG_MYD_Y335X_H
#define __CONFIG_MYD_Y335X_H

#include <configs/ti_am335x_common.h>

#define CONFIG_GPIO_MDIO 1

#ifndef CONFIG_SPL_BUILD
# define CONFIG_TIMESTAMP
# define CONFIG_LZO
#endif

#ifdef CONFIG_MYIR_OLD_UBOOT
#define CONFIG_CMDLINE_TAG              /* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS		/* enable passing of mem ATAGs */
#define CONFIG_INITRD_TAG               /* Required for ramdisk support */
#endif

#if defined(CONFIG_MYIR_UBOOT_BACKUP)
#define CONFIG_SPL_PANIC_ON_RAW_IMAGE 1
#endif

#define CONFIG_SYS_BOOTM_LEN		(16 << 20)

#define MACH_TYPE_MYD_Y335X		3589	/* Until the next sync */
#define CONFIG_MACH_TYPE		MACH_TYPE_MYD_Y335X
#undef CONFIG_BOARD_LATE_INIT
#undef CONFIG_SYS_BOOT_RAMDISK_HIGH
#undef CONFIG_SPL_OS_BOOT
/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

/* GPIO pin + bank to pin ID mapping */
#define GPIO_PIN(_bank, _pin)		((_bank << 5) + _pin)

/* Always 128 KiB env size */
#define CONFIG_ENV_SIZE			(128 << 10)

/* Enhance our eMMC support / experience. */
#define CONFIG_CMD_GPT
#define CONFIG_EFI_PARTITION

/* Enable Atheros phy driver */
#define CONFIG_PHY_ATHEROS

#ifdef CONFIG_NAND
#define CONFIG_RBTREE 1
#define CONFIG_MTD 1
#define CONFIG_MTD_PARTITIONS 1
#define CONFIG_CMD_UBI 1
#define CONFIG_CMD_UBIFS 1
#define LOADMLO \
	"loadmlo=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/MLO\0" 
#define LOADUBOOT \
	"loaduboot=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/u-boot.img\0" 
#ifdef CONFIG_MYIR_OLD_UBOOT
#define LOADKERNEL \
	"loadkernel=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/uImage\0"
#ifdef CONFIG_MYIR_UBOOT_BACKUP
#define LOADRECOVERY \
		"loadrecovery=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/recovery.img; \0"
#else
#define LOADRECOVERY "loadrecovery=echo 'no recovery partitions.'; \0"
#endif
#else
#ifdef CONFIG_MYIR_UBOOT_BACKUP
#define LOADKERNEL \
	"loadkernel=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/kernel.img; \0"
#define LOADRECOVERY \
	"loadrecovery=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/recovery.img; \0"
#else
#define LOADKERNEL \
	"loadkernel=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/${bootfile}\0"
#define LOADRECOVERY "loadrecovery=echo 'no recovery partitions.'; \0"
#endif
#endif	
#ifdef CONFIG_MYIR_OLD_UBOOT
#define LOADFILESYSTEM \
	"loadrootfs=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/ubi.img\0" 
#else
#define LOADFILESYSTEM \
	"loadrootfs=load ${devtype} ${devnum} ${loadaddr} ${bootdir}/rootfs.ubi\0" 
#endif
#define UPDATEMLO 	\
	"updatemlo=if run loadmlo; then " \
				"nand erase.part NAND.SPL; " \
				"nand write ${loadaddr} 0 ${filesize};" \
				"nand erase.part NAND.SPL.backup1; " \
				"nand write ${loadaddr} NAND.SPL.backup1 ${filesize};" \
				"nand erase.part NAND.SPL.backup2; " \
				"nand write ${loadaddr} NAND.SPL.backup2 ${filesize};" \
				"nand erase.part NAND.SPL.backup3; " \
				"nand write ${loadaddr} NAND.SPL.backup3 ${filesize};" \
			"fi;\0"
#ifdef CONFIG_MYIR_UBOOT_BACKUP			
#define UPDATEUBOOT \
	"updateuboot=if run loaduboot; then " \
				"nand erase.part NAND.u-boot;" \
				"nand write ${loadaddr} NAND.u-boot ${filesize};" \
				"nand erase.part NAND.u-boot.backup1;" \
				"nand write ${loadaddr} NAND.u-boot.backup1 ${filesize};" \
				"nand erase.part NAND.u-boot.backup2;" \
				"nand write ${loadaddr} NAND.u-boot.backup2 ${filesize};" \
				"nand erase.part NAND.u-boot-env;" \
				"nand erase.part NAND.u-boot-env.backup1;" \
			"fi;\0" 
#else
#ifdef CONFIG_MYIR_OLD_UBOOT
#define UPDATEUBOOT \
	"updateuboot=if run loaduboot; then " \
				"nand erase.part NAND.u-boot;" \
				"nand write ${loadaddr} NAND.u-boot ${filesize};" \
			"fi;\0" 
#else
#define UPDATEUBOOT \
	"updateuboot=if run loaduboot; then " \
				"nand erase.part NAND.u-boot;" \
				"nand erase.part NAND.u-boot-env;" \
				"nand erase.part NAND.u-boot-env.backup1;" \
				"nand write ${loadaddr} NAND.u-boot ${filesize};" \
			"fi;\0" 
#endif
#endif

#ifdef CONFIG_MYIR_OLD_UBOOT
#define UPDATEFDT  "updatefdt=echo no fdt;\0" 
#else
#define UPDATEFDT  \
	"updatefdt=if run loadfdt; then " \
				"nand erase.part NAND.u-boot-spl-os;" \
				"nand write ${fdtaddr} NAND.u-boot-spl-os ${filesize};" \
			"fi;\0" 
#endif

#ifdef CONFIG_MYIR_UBOOT_BACKUP			
#define UPDATEKERNEL \
	"updatekernel=if run loadkernel; then " \
				"nand erase.part NAND.kernel;" \
				"nand write ${loadaddr} NAND.kernel ${filesize};" \
				"nand erase.part NAND.kernel.backup1;" \
				"nand write ${loadaddr} NAND.kernel.backup1 ${filesize};" \
			"fi; \0" 
#else
#ifdef CONFIG_MYIR_OLD_UBOOT
#define UPDATEKERNEL \
	"updatekernel=if run loadkernel; then " \
			"nand erase.part NAND.kernel;" \
			"nand write ${loadaddr} NAND.kernel ${filesize};" \
		"fi; \0" 
#else
#define UPDATEKERNEL \
	"updatekernel=if run loadkernel; then " \
			"nand erase.part NAND.kernel;" \
			"nand write ${loadaddr} NAND.kernel ${filesize};" \
		"fi; \0" 
#endif
#endif

#ifdef CONFIG_MYIR_UBOOT_BACKUP			
#define  UPDATERECOVERY \
	"updaterecovery=if run loadrecovery; then " \
	"nand erase.part NAND.recovery;" \
	"nand write ${loadaddr} NAND.recovery ${filesize};" \
	"fi; \0"
#else
#define UPDATERECOVERY "updaterecovery=echo 'no recovery partitions.'; \0"
#endif

#ifdef CONFIG_MYIR_UBOOT_BACKUP			
#define UPDATEFILESYSTEM \
	"updatefilesystem=if run loadrootfs; then " \
				"nand erase.part NAND.rootfs;" \
				"nand write ${loadaddr} NAND.rootfs ${filesize};" \
				"nand erase.part NAND.rootfs.backup1;" \
				"nand write ${loadaddr} NAND.rootfs.backup1 ${filesize};" \
			"fi; \0" 
#else
#ifdef CONFIG_MYIR_OLD_UBOOT
#define UPDATEFILESYSTEM \
	"updatefilesystem=if run loadrootfs; then " \
				"nand erase.part NAND.rootfs;" \
				"nand write ${loadaddr} NAND.rootfs ${filesize};" \
			"fi; \0" 
#else
#define UPDATEFILESYSTEM \
	"updatefilesystem=if run loadrootfs; then " \
				"nand erase.part NAND.rootfs;" \
				"nand write ${loadaddr} NAND.rootfs ${filesize};" \
			"fi; \0" 
#endif
#endif
#define UPDATEALL \
	"updatesys=mmc dev 0;" \
		"if mmc rescan; then " \
			"setenv mmcdev 0; " \
			"setenv devtype mmc; " \
			"setenv devnum 0; " \
			"setenv bootdir /; " \
			"setenv bootpart 0:1;" \
		"fi; " \
		"usb start ${usbdev}; " \
		"if usb dev ${usbdev}; then " \
			"setenv devtype usb;" \
			"setenv devnum 0;" \
		"fi; "\
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenvfile};" \
			"run importbootenv;" \
		"fi; " \
		"if test -n $updatecmd; then " \
			"echo Running updatecmd ...;" \
			"run updatecmd;" \
		"else " \
			"run updatemlo; " \
			"run updateuboot; " \
			"run updatefdt; " \
			"run updatekernel; " \
			"run updaterecovery; " \
			"run updatefilesystem; " \
			"saveenv; saveenv; " \
		"fi; " \
		"if usb dev ${usbdev}; then " \
			"usb stop ${usbdev};" \
		"fi; \0" 	
#ifdef CONFIG_MYIR_UBOOT_BACKUP			
#define CHECKUBOOT \
	"checkuboot=if test ${ubootid} = 2; then " \
					"nand erase.part NAND.u-boot;" \
					"nand erase.part NAND.u-boot.backup1;" \
					"nand read ${loadaddr} NAND.u-boot.backup2; " \
					"nand write ${loadaddr} NAND.u-boot 0x100000; " \
					"nand write ${loadaddr} NAND.u-boot.backup1 0x100000; " \
				"else; " \
					"if test ${ubootid} = 1; then " \
						"nand erase.part NAND.u-boot;" \
						"nand read ${loadaddr} NAND.u-boot.backup1; " \
						"nand write ${loadaddr} NAND.u-boot 0x100000; " \
					"fi;" \
				"fi;\0" 

/* recoveryid  0/null: normal  1: update  2: reset2factory */				
#define CHECKRECOVERY "checkrecovery=if test -n $recoveryid && test ${recoveryid} != 0; then " \
					"nand read ${loadaddr}  NAND.recovery; " \
					"setenv optargs recoveryid=${recoveryid}; " \
					"run ramargs; " \
					"bootm  ${loadaddr}; " \
				"fi;\0" 
/* kernelid  0/null: normal  1: backup1 */
#define CHECKKERNEL "checkkernel=if test -n $kernelid && test ${kernelid} = 1; then " \
				"nand read ${loadaddr} NAND.kernel.backup1; " \
				"nand read ${fdtaddr} NAND.u-boot-spl-os; " \
				"if bootm ${loadaddr}; then " \
					"echo 'boot success, never run here!'; "\
				"else; " \
					"echo 'NAND.kernel.backup1 error, try NAND.kernel'; "\
					"nand erase.part NAND.kernel.backup1; "\
					"nand read ${loadaddr} NAND.kernel; " \
					"nand write ${loadaddr} NAND.kernel.backup1 0x800000; " \
					"setenv kernelid 0; saveenv; saveenv;" \
					"if bootm ${loadaddr}; then " \
						"echo 'boot success, never run here!'; "\
					"else; " \
						"setenv recoveryid 2; saveenv; saveenv; run checkrecovery; " \
					"fi; " \
				"fi; "	\
			"fi; " \
			"setenv kernelid 0; saveenv; saveenv;" \
			"nand read ${loadaddr} NAND.kernel; " \
			"nand read ${fdtaddr} NAND.u-boot-spl-os; " \
			"if bootm ${loadaddr}; then " \
				"echo 'boot success, never run here!'; "\
			"else; " \
				"echo 'NAND.kernel error, try NAND.kernel.backup1'; "\
				"nand erase.part NAND.kernel; "\
				"nand read ${loadaddr} NAND.kernel.backup1; " \
				"nand write ${loadaddr} NAND.kernel 0x800000; " \
				"setenv kernelid 1; saveenv; saveenv;" \
				"if bootm ${loadaddr}; then " \
					"echo 'boot success, never run here!'; "\
				"else; " \
					"setenv recoveryid 2; saveenv; saveenv; run checkrecovery; " \
				"fi; " \
			"fi; \0"	

/* rootfsid 0/null: normal  1: backup1 2: recovery(all corrupted)*/
#define CHECKROOTFS "checkrootfs=if test -n $rootfsid; then " \
					"echo 'rootfsid='$rootfsid; " \
				"else; " \
					"echo 'rootfsid not defined, set to 0 as default'; setenv rootfsid 0; " \
				"fi; " \
       				 "if test ${rootfsid} = 0; then " \
					"if ubi part NAND.rootfs 2048; then " \
						"if ubifsmount ubi0:rootfs; then " \
			               			"setenv rootfsid 0; " \
		    					"setenv nandroot ubi0:rootfs rw ubi.mtd=NAND.rootfs,2048; " \
			        		"else; " \
			                		"setenv rootfsid 1; " \
							"if ubi part NAND.rootfs.backup1 2048; then " \
								"if ubifsmount ubi0:rootfs; then " \
		    						  "setenv nandroot ubi0:rootfs rw ubi.mtd=NAND.rootfs.backup1,2048; " \
								"else; " \
								  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
								"fi; " \
							"else; " \
							  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
							"fi; " \
						"fi; " \
					"else; " \
			               			"setenv rootfsid 1; " \
							"if ubi part NAND.rootfs.backup1 2048; then " \
								"if ubifsmount ubi0:rootfs; then " \
		    						  "setenv nandroot ubi0:rootfs rw ubi.mtd=NAND.rootfs.backup1,2048; " \
								"else; " \
								  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
								"fi; " \
							"else; " \
							  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
							"fi; " \
					"fi; " \
				"fi; " \
       				 "if test ${rootfsid} = 1; then " \
					"if ubi part NAND.rootfs.backup1 2048; then " \
						"if ubifsmount ubi0:rootfs; then " \
			               			"setenv rootfsid 1; " \
		    					"setenv nandroot ubi0:rootfs rw ubi.mtd=NAND.rootfs.backup1,2048; " \
			        		"else; " \
			                		"setenv rootfsid 0; " \
							"if ubi part NAND.rootfs 2048; then " \
								"if ubifsmount ubi0:rootfs; then " \
		    						  "setenv nandroot ubi0:rootfs rw ubi.mtd=NAND.rootfs,2048; " \
								"else; " \
								  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
								"fi; " \
							"else; " \
							  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
							"fi; " \
						"fi; " \
					"else; " \
			               			"setenv rootfsid 0; " \
							"if ubi part NAND.rootfs 2048; then " \
								"if ubifsmount ubi0:rootfs; then " \
		    						  "setenv nandroot ubi0:rootfs rw ubi.mtd=NAND.rootfs,2048; " \
								"else; " \
								  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
								"fi; " \
							"else; " \
							  "setenv rootfsid 2; setenv recoveryid 2;saveenv;saveenv;run checkrecovery; " \
							"fi; " \
					"fi; " \
				"fi; " \
			"saveenv; saveenv; \0"
#else
#define CHECKUBOOT "checkuboot=echo 'no uboot backup partitions.';\0"
#define CHECKRECOVERY "checkrecovery=echo 'check no recovery partitions.'; \0"
#define CHECKKERNEL "checkkernel=echo 'no kernel backup partitions.'; \0"
#define CHECKROOTFS "checkrootfs=echo 'no rootfs backup partitions.'; \0"
#endif
#ifdef CONFIG_MYIR_UBOOT_BACKUP			
#define NANDBOOTCMD \
	"nandboot=echo Booting from nand ...; " \
		"run checkuboot; " \
		"run checkrecovery; " \
		"run checkrootfs; " \
		"run nandargs; " \
		"run checkkernel; \0"
#else
#ifdef CONFIG_MYIR_OLD_UBOOT
#define NANDBOOTCMD \
	"nandboot=echo Booting from nand ...; " \
		"run nandargs; " \
		"nand read ${loadaddr} NAND.kernel; " \
		"if bootm ${loadaddr}; then " \
			"echo 'boot success, never run here!'; "\
		"fi;\0"	
#else
#define NANDBOOTCMD \
	"nandboot=echo Booting from nand ...; " \
		"run nandargs; " \
		"nand read ${fdtaddr} NAND.u-boot-spl-os; " \
		"nand read ${loadaddr} NAND.kernel; " \
		"if bootz ${loadaddr} - ${fdtaddr}; then " \
			"echo 'boot success, never run here!'; "\
		"fi;\0"	
#endif
#endif
#ifdef CONFIG_MYIR_NAND_8G08
#define NANDROOT \
	"nandroot=ubi0:rootfs rw ubi.mtd=NAND.rootfs,4096\0" \
	"nandrootfstype=ubifs rootwait=1\0" 
#else
#define NANDROOT \
	"nandroot=ubi0:rootfs rw ubi.mtd=NAND.rootfs,2048\0" \
	"nandrootfstype=ubifs rootwait=1\0" 
#endif
#define NANDARGS  \
	LOADMLO \
	LOADUBOOT \
	LOADKERNEL \
	LOADRECOVERY \
	LOADFILESYSTEM \
	CHECKUBOOT \
	CHECKRECOVERY \
	CHECKKERNEL \
	CHECKROOTFS \
	UPDATEMLO \
	UPDATEUBOOT \
	UPDATEFDT \
	UPDATEKERNEL \
	UPDATERECOVERY \
	UPDATEFILESYSTEM \
	UPDATEALL \
	"mtdids=" MTDIDS_DEFAULT "\0" \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	"nandargs=setenv bootargs console=${console} " \
		"${optargs} ${mtdparts} " \
		" root=${nandroot} " \
		"rootfstype=${nandrootfstype}\0" \
	NANDROOT \
	NANDBOOTCMD
#else
#define NANDARGS ""
#endif
#undef NETARGS
#ifdef CONFIG_CMD_NET
#define NETARGS \
        "static_ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}" \
                "::off\0" \
        "nfsopts=nolock\0" \
        "rootpath=/export/rootfs\0" \
        "netloadimage=tftp ${loadaddr} ${bootfile}\0" \
        "netloadfdt=tftp ${fdtaddr} ${fdtfile}\0" \
        "netargs=setenv bootargs console=${console} " \
                "${optargs} " \
                "root=/dev/nfs " \
                "nfsroot=${serverip}:${rootpath},${nfsopts} rw " \
                "ip=dhcp\0" \
        "netboot=echo Booting from network ...; " \
                "setenv autoload no; " \
                "run netloadimage; " \
                "run netloadfdt; " \
                "run netargs; " \
                "bootz ${loadaddr} - ${fdtaddr}\0"
#else
#define NETARGS ""
#endif


#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#define BOOTENV_DEV_LEGACY_MMC(devtypeu, devtypel, instance) \
	"bootcmd_" #devtypel #instance "=" \
	"setenv mmcdev " #instance"; "\
	"setenv bootpart " #instance":2 ; "\
	"run mmcboot\0"

#define BOOTENV_DEV_NAME_LEGACY_MMC(devtypeu, devtypel, instance) \
	#devtypel #instance " "

#define BOOTENV_DEV_NAND(devtypeu, devtypel, instance) \
	"bootcmd_" #devtypel #instance "=" \
	"run nandboot\0"

#define BOOTENV_DEV_NAME_NAND(devtypeu, devtypel, instance) \
	#devtypel #instance " "

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0) \
	func(LEGACY_MMC, legacy_mmc, 0) \
	func(MMC, mmc, 1) \
	func(LEGACY_MMC, legacy_mmc, 1) \
	func(NAND, nand, 0) \
	func(PXE, pxe, na) \
	func(DHCP, dhcp, na)

#define CONFIG_BOOTCOMMAND \
	"run findfdt; " \
	"run envboot;" \
	"usb dev 0;" \
	"run usbboot;" \
	"mmc dev 0;" \
	"if mmc rescan; then " \
		"setenv mmcdev 0;" \
		"setenv devtype mmc; " \
		"setenv devnum 0;" \
		"setenv bootpart 0:2; " \
		"run findfdt; " \
		"run mmcboot;" \
	"fi; " \
	"mmc dev 1; " \
	"if mmc rescan; then " \
		"setenv mmcdev 1;" \
		"setenv devtype mmc;" \
		"setenv devnum 1;" \
		"setenv bootpart 1:2; " \
		"run findfdt; " \
		"run mmcboot;" \
	"fi; " \
 	"run nandboot; "


#ifndef CONFIG_SPL_BUILD
#define CONFIG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	DEFAULT_MMC_TI_ARGS \
	"boot_fdt=try\0" \
	"bootpart=0:2\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"fdtfile=undefined\0" \
	"console=ttyO0,115200n8\0" \
	"partitions=" \
		"uuid_disk=${uuid_gpt_disk};" \
		"name=rootfs,start=2MiB,size=-,uuid=${uuid_gpt_rootfs}\0" \
	"optargs=board-am335xevm.display_mode=lcd7ir\0" \
	"usbroot=/dev/sda2 rw\0" \
	"usbrootfstype=ext4 rootwait\0" \
	"usbdev=0\0" \
	"ramroot=/dev/ram0 rw\0" \
	"ramrootfstype=ext2\0" \
	"spiroot=/dev/mtdblock4 rw\0" \
	"spirootfstype=jffs2\0" \
	"spisrcaddr=0xe0000\0" \
	"spiimgsize=0x362000\0" \
	"spibusno=0\0" \
	"spiargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${spiroot} " \
		"rootfstype=${spirootfstype}\0" \
	"usbargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${usbroot} " \
		"rootfstype=${usbrootfstype}\0" \
	"ramargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${ramroot} " \
		"rootfstype=${ramrootfstype}\0" \
	"loadramdisk=load ${devtype} ${devnum} ${rdaddr} ramdisk.gz\0" \
	"loadimage=load ${devtype} ${bootpart} ${loadaddr} ${bootdir}/${bootfile}\0" \
	"loadfdt=load ${devtype} ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}\0" \
	"loadbootenv=load ${devtype} ${devnum} ${loadaddr} ${bootenvfile}\0" \
	"importbootenv=echo Importing environment from ${devtype} ...; " \
		"env import -t ${loadaddr} ${filesize}\0" \
	"mmcloados=run args_mmc; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"mmcboot=mmc dev ${mmcdev}; " \
		"setenv devnum ${mmcdev}; " \
		"setenv devtype mmc; " \
		"if mmc rescan; then " \
			"echo SD/MMC found on device ${mmcdev};" \
			"run envboot; " \
			"if run loadimage; then " \
				"run mmcloados;" \
			"fi;" \
		"fi;\0" \
	"spiboot=echo Booting from spi ...; " \
		"run spiargs; " \
		"sf probe ${spibusno}:0; " \
		"sf read ${loadaddr} ${spisrcaddr} ${spiimgsize}; " \
		"bootz ${loadaddr}\0" \
	"ramboot=echo Booting from ramdisk ...; " \
		"run ramargs; " \
		"bootz ${loadaddr} ${rdaddr} ${fdtaddr}\0" \
	"usbboot=" \
		"setenv devnum ${usbdev}; " \
		"setenv devtype usb; " \
		"usb start ${usbdev}; " \
		"if usb dev ${usbdev}; then " \
			"if run loadbootenv; then " \
				"echo Loaded environment from ${bootenvfile};" \
				"run importbootenv;" \
			"fi;" \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...;" \
				"run uenvcmd;" \
			"fi;" \
			"if run loadimage; then " \
				"run loadfdt; " \
				"echo Booting from usb ${usbdev}...; " \
				"run usbargs;" \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"fi;" \
		"fi\0" \
		"fi;" \
		"usb stop ${usbdev};\0" \
	"findfdt="\
		"if test $board_name = A335BONE; then " \
			"setenv fdtfile am335x-bone.dtb; fi; " \
		"if test $board_name = A335BNLT; then " \
			"setenv fdtfile am335x-boneblack.dtb; fi; " \
		"if test $board_name = BBG1; then " \
			"setenv fdtfile am335x-bonegreen.dtb; fi; " \
		"if test $board_name = A33515BB; then " \
			"setenv fdtfile am335x-evm.dtb; fi; " \
		"if test $board_name = A335X_SK; then " \
			"setenv fdtfile am335x-evmsk.dtb; fi; " \
		"if test $board_name = A335_ICE; then " \
			"setenv fdtfile am335x-icev2.dtb; fi; " \
		"if test $board_name = myd_y335x; then " \
			"setenv fdtfile myd_y335x.dtb; fi; " \
		"if test $fdtfile = undefined; then " \
			"echo WARNING: Could not determine device tree to use; fi; \0" \
	"init_console=" \
		"if test $board_name = A335_ICE; then "\
			"setenv console ttyO3,115200n8;" \
		"else " \
			"setenv console ttyO0,115200n8;" \
		"fi;\0" \
	NANDARGS \
	NETARGS \

#endif

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000	/* UART0 */
#define CONFIG_SYS_NS16550_COM3		0x48024000	/* UART2 */
#define CONFIG_BAUDRATE			115200

/* I2C Configuration */
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* Main EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	1
#define CONFIG_SYS_I2C_EEPROM_BUS	0
/* PMIC support */
#define CONFIG_POWER_TPS65217

/* SPL */
#ifndef CONFIG_NOR_BOOT
#define CONFIG_SPL_POWER_SUPPORT
#define CONFIG_SPL_YMODEM_SUPPORT

/* Bootcount using the RTC block */

/* USB gadget RNDIS */

#define CONFIG_SPL_LDSCRIPT		"$(CPUDIR)/am33xx/u-boot-spl.lds"
#endif
#ifdef CONFIG_NAND
/* NAND: device related configs */
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_COUNT	(CONFIG_SYS_NAND_BLOCK_SIZE / \
					 CONFIG_SYS_NAND_PAGE_SIZE)
#ifdef CONFIG_MYIR_NAND_8G08
#define CONFIG_SYS_NAND_PAGE_SIZE	4096
#define CONFIG_SYS_NAND_OOBSIZE		224
#define CONFIG_SYS_NAND_BLOCK_SIZE	(512*1024)
/* NAND: driver related configs */
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_NAND_OMAP_GPMC_PREFETCH
#define CONFIG_NAND_OMAP_ELM
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS		{ 2, 3, 4, 5, 6, 7, 8, 9, \
					 10, 11, 12, 13, 14, 15, 16, 17, \
					 18, 19, 20, 21, 22, 23, 24, 25, \
					 26, 27, 28, 29, 30, 31, 32, 33, \
					 34, 35, 36, 37, 38, 39, 40, 41, \
					 42, 43, 44, 45, 46, 47, 48, 49, \
					 50, 51, 52, 53, 54, 55, 56, 57, \
					 58, 59, 60, 61, 62, 63, 64, 65, \
					 66, 67, 68, 69, 70, 71, 72, 73, \
					 74, 75, 76, 77, 78, 79, 80, 81, \
					 82, 83, 84, 85, 86, 87, 88, 89, \
					 90, 91, 92, 93, 94, 95, 96, 97, \
					 98, 99, 100, 101, 102, 103, 104, 105, \
					 106, 107, 108, 109, 110, 111, 112, 113}
#else
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_OOBSIZE		64
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128*1024)
/* NAND: driver related configs */
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_NAND_OMAP_GPMC_PREFETCH
#define CONFIG_NAND_OMAP_ELM
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS		{ 2, 3, 4, 5, 6, 7, 8, 9, \
					 10, 11, 12, 13, 14, 15, 16, 17, \
					 18, 19, 20, 21, 22, 23, 24, 25, \
					 26, 27, 28, 29, 30, 31, 32, 33, \
					 34, 35, 36, 37, 38, 39, 40, 41, \
					 42, 43, 44, 45, 46, 47, 48, 49, \
					 50, 51, 52, 53, 54, 55, 56, 57, }
#endif
#define CONFIG_SYS_NAND_ECCSIZE		512
#define CONFIG_SYS_NAND_ECCBYTES	14
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_NAND_OMAP_ECCSCHEME	OMAP_ECC_BCH8_CODE_HW
#define MTDIDS_DEFAULT			"nand0=omap2-nand.0"

#ifdef CONFIG_MYIR_UBOOT_BACKUP
#define MTDPARTS_DEFAULT		"mtdparts=omap2-nand.0:" \
					"128k(NAND.SPL)," \
					"128k(NAND.SPL.backup1)," \
					"128k(NAND.SPL.backup2)," \
					"128k(NAND.SPL.backup3)," \
					"256k(NAND.u-boot-spl-os)," \
					"1m(NAND.u-boot)," \
					"128k(NAND.u-boot-env)," \
					"128k(NAND.u-boot-env.backup1)," \
					"1m(NAND.u-boot.backup1)," \
					"1m(NAND.u-boot.backup2)," \
					"8m(NAND.kernel)," \
					"8m(NAND.kernel.backup1)," \
					"32m(NAND.recovery)," \
					"64m(NAND.rootfs)," \
					"64m(NAND.rootfs.backup1)," \
					"32m(NAND.overlay)," \
					"-(NAND.userdata)"
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x000c0000
#define CONFIG_SYS_NAND_U_BOOT1_OFFS	0x00200000
#define CONFIG_SYS_NAND_U_BOOT2_OFFS	0x00300000
#else
#ifdef CONFIG_MYIR_OLD_UBOOT
#define MTDPARTS_DEFAULT		"mtdparts=omap2-nand.0:" \
					"128k(NAND.SPL)," \
					"128k(NAND.SPL.backup1)," \
					"128k(NAND.SPL.backup2)," \
					"128k(NAND.SPL.backup3)," \
					"1920k(NAND.u-boot)," \
					"128k(NAND.u-boot-env)," \
					"5120k(NAND.kernel)," \
					"-(NAND.rootfs)"
#else
#ifdef CONFIG_MYIR_NAND_8G08
#define MTDPARTS_DEFAULT		"mtdparts=omap2-nand.0:" \
					"512k(NAND.SPL)," \
					"512k(NAND.SPL.backup1)," \
					"512k(NAND.SPL.backup2)," \
					"512k(NAND.SPL.backup3)," \
					"512k(NAND.u-boot-spl-os)," \
					"1m(NAND.u-boot)," \
					"512k(NAND.u-boot-env)," \
					"512k(NAND.u-boot-env.backup1)," \
					"8m(NAND.kernel)," \
					"214m(NAND.rootfs)," \
					"-(NAND.userdata)"
#else
#define MTDPARTS_DEFAULT		"mtdparts=omap2-nand.0:" \
					"128k(NAND.SPL)," \
					"128k(NAND.SPL.backup1)," \
					"128k(NAND.SPL.backup2)," \
					"128k(NAND.SPL.backup3)," \
					"256k(NAND.u-boot-spl-os)," \
					"1m(NAND.u-boot)," \
					"128k(NAND.u-boot-env)," \
					"128k(NAND.u-boot-env.backup1)," \
					"8m(NAND.kernel)," \
					"214m(NAND.rootfs)," \
					"-(NAND.userdata)"
#endif
#endif
#if defined(CONFIG_MYIR_OLD_UBOOT)
#define CONFIG_SYS_NAND_U_BOOT_OFFS		0x00080000
#else
#ifdef CONFIG_MYIR_NAND_8G08
#define CONFIG_SYS_NAND_U_BOOT_OFFS		0x00280000
#else
#define CONFIG_SYS_NAND_U_BOOT_OFFS		0x000c0000
#endif
#endif
#endif

/* NAND: SPL related configs */
#ifdef CONFIG_SPL_NAND_SUPPORT
#define CONFIG_SPL_NAND_AM33XX_BCH
#endif
#ifdef CONFIG_SPL_OS_BOOT
#ifdef CONFIG_MYIR_NAND_8G08
#define CONFIG_CMD_SPL_NAND_OFS	0x00200000 /* os parameters */
#else
#define CONFIG_CMD_SPL_NAND_OFS	0x00080000 /* os parameters */
#endif

#if defined(CONFIG_MYIR_OLD_UBOOT)
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00280000 /* kernel offset */
#else
#ifdef CONFIG_MYIR_NAND_8G08
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00480000 /* kernel offset */
#else
#ifdef CONFIG_MYIR_UBOOT_BACKUP
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00400000 /* kernel offset */
#else
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00200000 /* kernel offset */
#endif
#endif
#endif
#define CONFIG_CMD_SPL_WRITE_SIZE	CONFIG_SYS_NAND_BLOCK_SIZE
#endif
#endif /* !CONFIG_NAND */

/*
 * For NOR boot, we must set this to the start of where NOR is mapped
 * in memory.
 */
#ifdef CONFIG_NOR_BOOT
#define CONFIG_SYS_TEXT_BASE		0x08000000
#endif

/*
 * USB configuration.  We enable MUSB support, both for host and for
 * gadget.  We set USB0 as peripheral and USB1 as host, based on the
 * board schematic and physical port wired to each.  Then for host we
 * add mass storage support and for gadget we add both RNDIS ethernet
 * and DFU.
 */
#define CONFIG_USB_MUSB_DSPS
#define CONFIG_ARCH_MISC_INIT
#define CONFIG_USB_MUSB_PIO_ONLY
#define CONFIG_USB_MUSB_DISABLE_BULK_COMBINE_SPLIT
#define CONFIG_AM335X_USB0
#define CONFIG_AM335X_USB0_MODE	MUSB_PERIPHERAL
#define CONFIG_AM335X_USB1
#define CONFIG_AM335X_USB1_MODE MUSB_HOST

#ifndef CONFIG_SPL_USBETH_SUPPORT
/* Fastboot */
#define CONFIG_USB_FUNCTION_FASTBOOT
#define CONFIG_CMD_FASTBOOT
#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_FASTBOOT_BUF_ADDR	CONFIG_SYS_LOAD_ADDR
#define CONFIG_FASTBOOT_BUF_SIZE	0x07000000

/* To support eMMC booting */
#define CONFIG_STORAGE_EMMC
#define CONFIG_FASTBOOT_FLASH_MMC_DEV   1
#endif

#ifdef CONFIG_USB_MUSB_HOST
#define CONFIG_USB_STORAGE
#endif

#ifdef CONFIG_USB_MUSB_GADGET
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_RNDIS
#define CONFIG_USBNET_HOST_ADDR	"de:ad:be:af:00:00"
#endif /* CONFIG_USB_MUSB_GADGET */

/*
 * Disable MMC DM for SPL build and can be re-enabled after adding
 * DM support in SPL
 */
#ifdef CONFIG_SPL_BUILD
#undef CONFIG_DM_MMC
#undef CONFIG_TIMER
#undef CONFIG_DM_NAND
#undef CONFIG_DM_USB
#endif

/*
 * Default to using SPI for environment, etc.
 * 0x000000 - 0x020000 : SPL (128KiB)
 * 0x020000 - 0x0A0000 : U-Boot (512KiB)
 * 0x0A0000 - 0x0BFFFF : First copy of U-Boot Environment (128KiB)
 * 0x0C0000 - 0x0DFFFF : Second copy of U-Boot Environment (128KiB)
 * 0x0E0000 - 0x442000 : Linux Kernel
 * 0x442000 - 0x800000 : Userland
 */
#if defined(CONFIG_SPI_BOOT)
/* SPL related */
#undef CONFIG_SPL_OS_BOOT		/* Not supported by existing map */
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x20000

#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#define CONFIG_ENV_SECT_SIZE		(4 << 10) /* 4 KB sectors */
#define CONFIG_ENV_OFFSET		(768 << 10) /* 768 KiB in */
#define CONFIG_ENV_OFFSET_REDUND	(896 << 10) /* 896 KiB in */
#define MTDIDS_DEFAULT			"nor0=m25p80-flash.0"
#define MTDPARTS_DEFAULT		"mtdparts=m25p80-flash.0:128k(SPL)," \
					"512k(u-boot),128k(u-boot-env1)," \
					"128k(u-boot-env2),3464k(kernel)," \
					"-(rootfs)"
#elif defined(CONFIG_EMMC_BOOT)
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SYS_MMC_ENV_DEV		1
#define CONFIG_SYS_MMC_ENV_PART		2
#define CONFIG_ENV_OFFSET		0x0
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#elif defined(CONFIG_NOR_BOOT)
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_SECT_SIZE		(128 << 10)	/* 128 KiB */
#define CONFIG_ENV_OFFSET		(512 << 10)	/* 512 KiB */
#define CONFIG_ENV_OFFSET_REDUND	(768 << 10)	/* 768 KiB */
#define MTDIDS_DEFAULT			"nor0=physmap-flash.0"
#define MTDPARTS_DEFAULT		"mtdparts=physmap-flash.0:" \
					"512k(u-boot)," \
					"128k(u-boot-env1)," \
					"128k(u-boot-env2)," \
					"4m(kernel),-(rootfs)"
#elif defined(CONFIG_ENV_IS_IN_NAND)
#ifdef CONFIG_MYIR_NAND_8G08
#define CONFIG_ENV_OFFSET		0x00380000
#define CONFIG_ENV_OFFSET_REDUND	0x00400000
#else
#define CONFIG_ENV_OFFSET		0x001c0000
#define CONFIG_ENV_OFFSET_REDUND	0x001e0000
#endif
#define CONFIG_SYS_ENV_SECT_SIZE	CONFIG_SYS_NAND_BLOCK_SIZE
#elif !defined(CONFIG_ENV_IS_NOWHERE)
/* Not NAND, SPI, NOR or eMMC env, so put ENV in a file on FAT */
#define CONFIG_ENV_IS_IN_FAT
#define FAT_ENV_INTERFACE		"mmc"
#define FAT_ENV_DEVICE_AND_PART		"0:1"
#define FAT_ENV_FILE			"uboot.env"
#endif

/* SPI flash. */
#define CONFIG_SF_DEFAULT_SPEED		24000000

/* Network. */
#define CONFIG_PHY_GIGE
#define CONFIG_PHYLIB
#define CONFIG_PHY_SMSC

/*
 * NOR Size = 16 MiB
 * Number of Sectors/Blocks = 128
 * Sector Size = 128 KiB
 * Word length = 16 bits
 * Default layout:
 * 0x000000 - 0x07FFFF : U-Boot (512 KiB)
 * 0x080000 - 0x09FFFF : First copy of U-Boot Environment (128 KiB)
 * 0x0A0000 - 0x0BFFFF : Second copy of U-Boot Environment (128 KiB)
 * 0x0C0000 - 0x4BFFFF : Linux Kernel (4 MiB)
 * 0x4C0000 - 0xFFFFFF : Userland (11 MiB + 256 KiB)
 */
#if defined(CONFIG_NOR)
#undef CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#define CONFIG_SYS_FLASH_PROTECTION
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_FLASH_CFI_MTD
#define CONFIG_SYS_MAX_FLASH_SECT	128
#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_FLASH_BASE		(0x08000000)
#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
#define CONFIG_SYS_FLASH_SIZE		0x01000000
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_FLASH_BASE
#endif  /* NOR support */

#ifdef CONFIG_DRIVER_TI_CPSW
#define CONFIG_CLOCK_SYNTHESIZER
#define CLK_SYNTHESIZER_I2C_ADDR 0x65
#endif

/* Status LED */
#define CONFIG_STATUS_LED
#define CONFIG_GPIO_LED
#define CONFIG_BOARD_SPECIFIC_LED
#define STATUS_LED_BIT			GPIO_PIN(3, 18)
/* Status LED polarity is inversed, so init it in the "off" state */
#define STATUS_LED_STATE		STATUS_LED_OFF
#define STATUS_LED_PERIOD		(CONFIG_SYS_HZ / 2)
#define STATUS_LED_BOOT			0

#endif	/* __CONFIG_MYD_Y335X_H */

