/*
 * Board functions for MYIR Tech MYD-C335X board
 *
 * Copyright (C) 2016, MYIR Tech Ltd - http://www.myirtech.com/
 *
 * Author: Sunny Guo <sunny.guo@myirtech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <errno.h>
#include <spl.h>
#include <serial.h>
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/omap.h>
#include <asm/arch/ddr_defs.h>
#include <asm/arch/clock.h>
#include <asm/arch/clk_synthesizer.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mem.h>
#include <asm/io.h>
#include <asm/emif.h>
#include <asm/gpio.h>
#include <i2c.h>
#include <miiphy.h>
#include <cpsw.h>
#include <environment.h>
#include <watchdog.h>
#include <environment.h>
#include <libfdt.h>
#include <fdt_support.h>


DECLARE_GLOBAL_DATA_PTR;

/* GPIO that controls power to DDR on EVM-SK */
#define GPIO_TO_PIN(bank, gpio)		(32 * (bank) + (gpio))
#define GPIO_DDR_VTT_EN		GPIO_TO_PIN(0, 7)
#define ICE_GPIO_DDR_VTT_EN	GPIO_TO_PIN(0, 18)
#define GPIO_PR1_MII_CTRL	GPIO_TO_PIN(3, 4)
#define GPIO_MUX_MII_CTRL	GPIO_TO_PIN(3, 10)
#define GPIO_FET_SWITCH_CTRL	GPIO_TO_PIN(0, 7)
#define GPIO_PHY_RESET		GPIO_TO_PIN(2, 5)
#define GPIO_ETH0_MODE		GPIO_TO_PIN(0, 11)
#define GPIO_ETH1_MODE		GPIO_TO_PIN(1, 26)

//static struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

#define GPIO0_RISINGDETECT	(AM33XX_GPIO0_BASE + OMAP_GPIO_RISINGDETECT)
#define GPIO1_RISINGDETECT	(AM33XX_GPIO1_BASE + OMAP_GPIO_RISINGDETECT)

#define GPIO0_IRQSTATUS1	(AM33XX_GPIO0_BASE + OMAP_GPIO_IRQSTATUS1)
#define GPIO1_IRQSTATUS1	(AM33XX_GPIO1_BASE + OMAP_GPIO_IRQSTATUS1)

#define GPIO0_IRQSTATUSRAW	(AM33XX_GPIO0_BASE + 0x024)
#define GPIO1_IRQSTATUSRAW	(AM33XX_GPIO1_BASE + 0x024)

#ifndef CONFIG_DM_SERIAL
struct serial_device *default_serial_console(void)
{
		return &eserial1_device;
}
#endif

/*
 * Basic board specific setup.  Pinmux has been handled already.
 */
int board_init(void)
{
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
#if defined(CONFIG_NOR) || defined(CONFIG_NAND)
	gpmc_init();
#endif

#if defined(CONFIG_STATUS_LED) && defined(STATUS_LED_BOOT)
	status_led_set(STATUS_LED_BOOT, STATUS_LED_OFF);
#endif
	return 0;
}

#if defined (CONFIG_DRIVER_TI_CPSW) && !defined(CONFIG_SPL_BUILD)
static void cpsw_control(int enabled)
{
	/* VTP can be added here */
	return;
}

static struct cpsw_slave_data cpsw_slave = {
	.slave_reg_ofs	= 0x208,
	.sliver_reg_ofs	= 0xd80,
	.phy_addr	= 4,
	.phy_if		= PHY_INTERFACE_MODE_RGMII,
};

static struct cpsw_platform_data cpsw_data = {
	.mdio_base		= CPSW_MDIO_BASE,
	.cpsw_base		= CPSW_BASE,
	.mdio_div		= 0xff,
	.channels		= 8,
	.cpdma_reg_ofs		= 0x800,
	.slaves			= 1,
	.slave_data		= &cpsw_slave,
	.ale_reg_ofs		= 0xd00,
	.ale_entries		= 1024,
	.host_port_reg_ofs	= 0x108,
	.hw_stats_reg_ofs	= 0x900,
	.bd_ram_ofs		= 0x2000,
	.mac_control		= (1 << 5),
	.control		= cpsw_control,
	.host_port_num		= 0,
	.version		= CPSW_CTRL_VERSION_2,
};

static void get_efuse_mac0_addr(uchar *enetaddr)
{
	uint32_t mac_hi, mac_lo;
	struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

	mac_lo = readl(&cdev->macid0l);
	mac_hi = readl(&cdev->macid0h);
	enetaddr[0] = mac_hi & 0xFF;
	enetaddr[1] = (mac_hi & 0xFF00) >> 8;
	enetaddr[2] = (mac_hi & 0xFF0000) >> 16;
	enetaddr[3] = (mac_hi & 0xFF000000) >> 24;
	enetaddr[4] = mac_lo & 0xFF;
	enetaddr[5] = (mac_lo & 0xFF00) >> 8;
}

static void get_efuse_mac1_addr(uchar *enetaddr)
{
	uint32_t mac_hi, mac_lo;
	struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

	mac_lo = readl(&cdev->macid1l);
	mac_hi = readl(&cdev->macid1h);
	enetaddr[0] = mac_hi & 0xFF;
	enetaddr[1] = (mac_hi & 0xFF00) >> 8;
	enetaddr[2] = (mac_hi & 0xFF0000) >> 16;
	enetaddr[3] = (mac_hi & 0xFF000000) >> 24;
	enetaddr[4] = mac_lo & 0xFF;
	enetaddr[5] = (mac_lo & 0xFF00) >> 8;
}

/*
 * Routine: handle_mac0_address
 * Description: prepare MAC address for on-board Ethernet.
 */
static int handle_mac0_address(void)
{
	uchar enetaddr[6];
	int rv;

	rv = eth_getenv_enetaddr("ethaddr", enetaddr);
	if (rv)
		return 0;

		get_efuse_mac0_addr(enetaddr);

	if (!is_valid_ethaddr(enetaddr))
		return -1;

	return eth_setenv_enetaddr("ethaddr", enetaddr);
}
/*
 * Routine: handle_mac1_address
 * Description: prepare MAC address for on-board Ethernet.
 */
static int handle_mac1_address(void)
{
	uchar enetaddr[6];
	int rv;

	rv = eth_getenv_enetaddr("eth1addr", enetaddr);
	if (rv)
		return 0;

		get_efuse_mac1_addr(enetaddr);

	if (!is_valid_ethaddr(enetaddr))
		return -1;

	return eth_setenv_enetaddr("eth1addr", enetaddr);
}

#define AR8051_PHY_DEBUG_ADDR_REG	0x1d
#define AR8051_PHY_DEBUG_DATA_REG	0x1e
#define AR8051_DEBUG_RGMII_CLK_DLY_REG	0x5
#define AR8051_RGMII_TX_CLK_DLY		0x100

int board_eth_init(bd_t *bis)
{
	int rv, n = 0;
	const char *devname;
	struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

	rv = handle_mac0_address();
	if (rv)
		printf("No MAC address for mac0 found!\n");

	rv = handle_mac1_address();
	if(rv)
		printf("No MAC address for mac1 found!\n");

	writel(RGMII_MODE_ENABLE | RGMII_INT_DELAY, &cdev->miisel);
	rv = cpsw_register(&cpsw_data);
	if (rv < 0)
		printf("Error %d registering CPSW switch\n", rv);
	else
		n += rv;

	/*
	 * CPSW RGMII Internal Delay Mode is not supported in all PVT
	 * operating points.  So we must set the TX clock delay feature
	 * in the AR8051 PHY.  Since we only support a single ethernet
	 * device, we only do this for the first instance.
	 */
	devname = miiphy_get_current_dev();

	miiphy_write(devname, 0x0, AR8051_PHY_DEBUG_ADDR_REG,
		     AR8051_DEBUG_RGMII_CLK_DLY_REG);
	miiphy_write(devname, 0x0, AR8051_PHY_DEBUG_DATA_REG,
		     AR8051_RGMII_TX_CLK_DLY);
	return n;
}
#endif /* CONFIG_DRIVER_TI_CPSW && !CONFIG_SPL_BUILD */
