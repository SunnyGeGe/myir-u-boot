/*
 * Pinmux configuration for MYIR Tech MYD-Y335X board
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
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/hardware.h>
#include <asm/arch/mux.h>
#include <asm/io.h>
#include <i2c.h>

static struct module_pin_mux uart0_pin_mux[] = {
	{OFFSET(uart0_rxd), (MODE(0) | PULLUP_EN | RXACTIVE)},	/* UART0_RXD */
	{OFFSET(uart0_txd), (MODE(0) | PULLUDEN)},		/* UART0_TXD */
	{-1},
};

static struct module_pin_mux uart2_pin_mux[] = {
	{OFFSET(mii1_crs), (MODE(6) | PULLUP_EN | RXACTIVE)},
	{OFFSET(mii1_rxerr), (MODE(6) | PULLUDEN)},
	{-1},
};


static struct module_pin_mux mmc0_pin_mux[] = {
	{OFFSET(mmc0_dat3), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT3 */
	{OFFSET(mmc0_dat2), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT2 */
	{OFFSET(mmc0_dat1), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT1 */
	{OFFSET(mmc0_dat0), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT0 */
	{OFFSET(mmc0_clk), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_CLK */
	{OFFSET(mmc0_cmd), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_CMD */
	{-1},
};

static struct module_pin_mux i2c0_pin_mux[] = {
	{OFFSET(i2c0_sda), (MODE(0) | RXACTIVE |
			PULLUDEN | SLEWCTRL)}, /* I2C_DATA */
	{OFFSET(i2c0_scl), (MODE(0) | RXACTIVE |
			PULLUDEN | SLEWCTRL)}, /* I2C_SCLK */
	{-1},
};

static struct module_pin_mux i2c1_pin_mux[] = {
	{OFFSET(spi0_d1), (MODE(2) | RXACTIVE |
			PULLUDEN | SLEWCTRL)},	/* I2C_DATA */
	{OFFSET(spi0_cs0), (MODE(2) | RXACTIVE |
			PULLUDEN | SLEWCTRL)},	/* I2C_SCLK */
	{-1},
};



static struct module_pin_mux rgmii1_pin_mux[] = {
	{OFFSET(mii1_txen), MODE(2)},			/* RGMII1_TCTL */
	{OFFSET(mii1_rxdv), MODE(2) | RXACTIVE},	/* RGMII1_RCTL */
	{OFFSET(mii1_txd3), MODE(2)},			/* RGMII1_TD3 */
	{OFFSET(mii1_txd2), MODE(2)},			/* RGMII1_TD2 */
	{OFFSET(mii1_txd1), MODE(2)},			/* RGMII1_TD1 */
	{OFFSET(mii1_txd0), MODE(2)},			/* RGMII1_TD0 */
	{OFFSET(mii1_txclk), MODE(2)},			/* RGMII1_TCLK */
	{OFFSET(mii1_rxclk), MODE(2) | RXACTIVE},	/* RGMII1_RCLK */
	{OFFSET(mii1_rxd3), MODE(2) | RXACTIVE},	/* RGMII1_RD3 */
	{OFFSET(mii1_rxd2), MODE(2) | RXACTIVE},	/* RGMII1_RD2 */
	{OFFSET(mii1_rxd1), MODE(2) | RXACTIVE},	/* RGMII1_RD1 */
	{OFFSET(mii1_rxd0), MODE(2) | RXACTIVE},	/* RGMII1_RD0 */
	{OFFSET(mdio_data), MODE(0) | RXACTIVE | PULLUP_EN},/* MDIO_DATA */
	{OFFSET(mdio_clk), MODE(0) | PULLUP_EN},	/* MDIO_CLK */
	{-1},
};


#ifdef CONFIG_NAND
#pragma message("NAND is activated!")
static struct module_pin_mux nand_pin_mux[] = {
	{OFFSET(gpmc_ad0),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD0  */
	{OFFSET(gpmc_ad1),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD1  */
	{OFFSET(gpmc_ad2),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD2  */
	{OFFSET(gpmc_ad3),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD3  */
	{OFFSET(gpmc_ad4),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD4  */
	{OFFSET(gpmc_ad5),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD5  */
	{OFFSET(gpmc_ad6),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD6  */
	{OFFSET(gpmc_ad7),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD7  */
#ifdef CONFIG_SYS_NAND_BUSWIDTH_16BIT
	{OFFSET(gpmc_ad8),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD8  */
	{OFFSET(gpmc_ad9),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD9  */
	{OFFSET(gpmc_ad10),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD10 */
	{OFFSET(gpmc_ad11),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD11 */
	{OFFSET(gpmc_ad12),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD12 */
	{OFFSET(gpmc_ad13),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD13 */
	{OFFSET(gpmc_ad14),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD14 */
	{OFFSET(gpmc_ad15),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD15 */
#endif
	{OFFSET(gpmc_wait0),	(MODE(0) | PULLUP_EN | RXACTIVE)}, /* nWAIT */
	{OFFSET(gpmc_wpn),	(MODE(7) | PULLUP_EN)},		   /* nWP */
	{OFFSET(gpmc_csn0),	(MODE(0) | PULLUP_EN)},		   /* nCS */
	{OFFSET(gpmc_wen),	(MODE(0) | PULLDOWN_EN)},	   /* WEN */
	{OFFSET(gpmc_oen_ren),	(MODE(0) | PULLDOWN_EN)},	   /* OE */
	{OFFSET(gpmc_advn_ale),	(MODE(0) | PULLDOWN_EN)},	   /* ADV_ALE */
	{OFFSET(gpmc_be0n_cle),	(MODE(0) | PULLDOWN_EN)},	   /* BE_CLE */
	{-1},
};
#endif

static struct module_pin_mux emmc_pin_mux[] = {
	{OFFSET(gpmc_csn1), (MODE(2) | PULLUDDIS | RXACTIVE)}, /* EMMC_CLK */
	{OFFSET(gpmc_csn2), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* EMMC_CMD */
	{OFFSET(gpmc_ad0),  (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT0 */
	{OFFSET(gpmc_ad1),  (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT1 */
	{OFFSET(gpmc_ad2), (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT2 */
	{OFFSET(gpmc_ad3), (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT3 */
	{OFFSET(gpmc_ad4), (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT4 */
	{OFFSET(gpmc_ad5), (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT5 */
	{OFFSET(gpmc_ad6), (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT6 */
	{OFFSET(gpmc_ad7), (MODE(1) | PULLUP_EN | RXACTIVE)}, /* EMMC_DAT7 */
	{-1},
};



static struct module_pin_mux status_led_pin_mux[] = {
	{OFFSET(mcasp0_aclkr), (MODE(7) | PULLUDEN)},	/* GPIO3_18 */
	{-1},
};

static struct module_pin_mux myd_wdt_pin_mux[] = {
	{OFFSET(emu1), (MODE(7) | PULLUDDIS | RXACTIVE)},	/* GPIO3_8 */
	{-1},
};
void set_uart_mux_conf(void)
{
	configure_module_pin_mux(uart0_pin_mux);
	configure_module_pin_mux(uart2_pin_mux);
}

void set_mux_conf_regs(void)
{
	configure_module_pin_mux(i2c0_pin_mux);
	configure_module_pin_mux(i2c1_pin_mux);
	configure_module_pin_mux(rgmii1_pin_mux);
	configure_module_pin_mux(mmc0_pin_mux);
#if defined(CONFIG_NAND)
	
	configure_module_pin_mux(nand_pin_mux);
#else
	configure_module_pin_mux(emmc_pin_mux);
#endif
	configure_module_pin_mux(status_led_pin_mux);
	configure_module_pin_mux(myd_wdt_pin_mux);
}
