/*
 * mux configuration code for MYIR Tech ricoboard
 *
 * Copyright (C) 2016, MYIR Tech Ltd - http://www.myirtech.com/
 *
 * Author: Sunny Guo <sunny.guo@myirtech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mux.h>
#include "../common/board_detect.h"
#include "board.h"

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
	{-1},
};

static struct module_pin_mux mdio_pin_mux[] = {
	{OFFSET(mdio_data), MODE(0) | RXACTIVE | PULLUP_EN},/* MDIO_DATA */
	{OFFSET(mdio_clk), MODE(0) | PULLUP_EN},	/* MDIO_CLK */
	{-1},
};

static struct module_pin_mux uart0_pin_mux[] = {
	{OFFSET(uart0_rxd), (MODE(0) | PULLUP_EN | RXACTIVE | SLEWCTRL)},
	{OFFSET(uart0_txd), (MODE(0) | PULLUDDIS | PULLUP_EN | SLEWCTRL)},
	{-1},
};

static struct module_pin_mux mmc0_pin_mux[] = {
	{OFFSET(mmc0_clk), (MODE(0) | PULLUDDIS | RXACTIVE)},  /* MMC0_CLK */
	{OFFSET(mmc0_cmd), (MODE(0) | PULLUP_EN | RXACTIVE)},  /* MMC0_CMD */
	{OFFSET(mmc0_dat0), (MODE(0) | PULLUP_EN | RXACTIVE)}, /* MMC0_DAT0 */
	{OFFSET(mmc0_dat1), (MODE(0) | PULLUP_EN | RXACTIVE)}, /* MMC0_DAT1 */
	{OFFSET(mmc0_dat2), (MODE(0) | PULLUP_EN | RXACTIVE)}, /* MMC0_DAT2 */
	{OFFSET(mmc0_dat3), (MODE(0) | PULLUP_EN | RXACTIVE)}, /* MMC0_DAT3 */
	{-1},
};

static struct module_pin_mux i2c0_pin_mux[] = {
	{OFFSET(i2c0_sda), (MODE(0) | PULLUP_EN | RXACTIVE | SLEWCTRL)},
	{OFFSET(i2c0_scl), (MODE(0) | PULLUP_EN | RXACTIVE | SLEWCTRL)},
	{-1},
};

static struct module_pin_mux gpio3_pin_mux[] = 
{
	{OFFSET(emu0), (MODE(7) | PULLUP_EN)},	/* GPIO3_7 for EEPROM-WP */
	{-1},
};


#ifdef CONFIG_NAND
static struct module_pin_mux nand_pin_mux[] = {
	{OFFSET(gpmc_ad0),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD0 */
	{OFFSET(gpmc_ad1),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD1 */
	{OFFSET(gpmc_ad2),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD2 */
	{OFFSET(gpmc_ad3),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD3 */
	{OFFSET(gpmc_ad4),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD4 */
	{OFFSET(gpmc_ad5),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD5 */
	{OFFSET(gpmc_ad6),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD6 */
	{OFFSET(gpmc_ad7),	(MODE(0) | PULLUDDIS | RXACTIVE)}, /* AD7 */
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
	{OFFSET(gpmc_wait0),	(MODE(0) | RXACTIVE | PULLUP_EN)}, /* Wait */
	{OFFSET(gpmc_wpn),	(MODE(7) | PULLUP_EN)},	/* Write Protect */
	{OFFSET(gpmc_csn0),	(MODE(0) | PULLUP_EN)},	/* Chip-Select */
	{OFFSET(gpmc_wen),	(MODE(0) | PULLDOWN_EN)}, /* Write Enable */
	{OFFSET(gpmc_oen_ren),	(MODE(0) | PULLDOWN_EN)}, /* Read Enable */
	{OFFSET(gpmc_advn_ale),	(MODE(0) | PULLDOWN_EN)}, /* Addr Latch Enable*/
	{OFFSET(gpmc_be0n_cle),	(MODE(0) | PULLDOWN_EN)}, /* Byte Enable */
	{-1},
};
#endif

static __maybe_unused struct module_pin_mux qspi_pin_mux[] = {
	{OFFSET(gpmc_csn0), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_CS0 */
	{OFFSET(gpmc_csn3), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* QSPI_CLK */
	{OFFSET(gpmc_advn_ale), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D0 */
	{OFFSET(gpmc_oen_ren), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D1 */
	{OFFSET(gpmc_wen), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D2 */
	{OFFSET(gpmc_be0n_cle), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D3 */
	{-1},
};

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

void set_i2c_pin_mux()
{
	configure_module_pin_mux(i2c0_pin_mux);
}

void set_uart_mux_conf(void)
{
	configure_module_pin_mux(uart0_pin_mux);
}

void set_mux_conf_regs(void)
{
	configure_module_pin_mux(mmc0_pin_mux);
	configure_module_pin_mux(i2c0_pin_mux);
	configure_module_pin_mux(mdio_pin_mux);
	
	if (board_is_ricoboard()) {
	configure_module_pin_mux(gpio3_pin_mux);
	configure_module_pin_mux(rgmii1_pin_mux);
#if defined(CONFIG_NAND)
	configure_module_pin_mux(nand_pin_mux);
#else
	configure_module_pin_mux(qspi_pin_mux);
	configure_module_pin_mux(emmc_pin_mux);
#endif
	}
}


