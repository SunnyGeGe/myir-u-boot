/*
 * SPL specific code for MYIR Tech MYD-Y335X board
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
#include <i2c.h>
#include <power/tps65217.h>

const struct ctrl_ioregs ioregs = {
	.cm0ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.cm1ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.cm2ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.dt0ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.dt1ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
};

static const struct ddr_data ddr3_data = {
	.datardsratio0 = MT41K256M16HA125E_RD_DQS,
	.datawdsratio0 = MT41K256M16HA125E_WR_DQS,
	.datafwsratio0 = MT41K256M16HA125E_PHY_FIFO_WE,
	.datawrsratio0 = MT41K256M16HA125E_PHY_WR_DATA,
};

static const struct cmd_control ddr3_cmd_ctrl_data = {
	.cmd0csratio = MT41K256M16HA125E_RATIO,
	.cmd0iclkout = MT41K256M16HA125E_INVERT_CLKOUT,

	.cmd1csratio = MT41K256M16HA125E_RATIO,
	.cmd1iclkout = MT41K256M16HA125E_INVERT_CLKOUT,

	.cmd2csratio = MT41K256M16HA125E_RATIO,
	.cmd2iclkout = MT41K256M16HA125E_INVERT_CLKOUT,
};

static struct emif_regs ddr3_emif_reg_data = {
	.sdram_config = MT41K256M16HA125E_EMIF_SDCFG,
	.ref_ctrl = MT41K256M16HA125E_EMIF_SDREF,
	.sdram_tim1 = MT41K256M16HA125E_EMIF_TIM1,
	.sdram_tim2 = MT41K256M16HA125E_EMIF_TIM2,
	.sdram_tim3 = MT41K256M16HA125E_EMIF_TIM3,
	.zq_config = MT41K256M16HA125E_ZQ_CFG,
	.emif_ddr_phy_ctlr_1 = MT41K256M16HA125E_EMIF_READ_LATENCY,
};

const struct dpll_params dpll_ddr = {
/*       M           N            M2  M3  M4  M5  M6 */
	400, (V_OSCK/1000000) - 1, 1, -1, -1, -1, -1};

void am33xx_spl_board_init(void)
{
	struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;
	uchar pmic_status_reg;
	int usb_cur_lim;
	int mpu_vdd;

	/* Get the frequency */
	dpll_mpu_opp100.m = am335x_get_efuse_mpu_max_freq(cdev);
	i2c_set_bus_num(0);
	if (i2c_probe(TPS65217_CHIP_PM))
	{
		puts("PMIC NOT DETECTED!\n");
		return;
	}

	puts("PMIC DETECTED: TPS65217 \n");

	if (tps65217_reg_read(TPS65217_STATUS,
					      &pmic_status_reg))

	{	
		return;
	}

	if (!(pmic_status_reg & TPS65217_PWR_SRC_AC_BITMASK)) {
		puts("No AC power, disabling frequency switch\n");
		return;
	}	
	/*
	 * Increase USB current limit to 1300mA or 1800mA and set
	 * the MPU voltage controller as needed.
	 */
	if (dpll_mpu_opp100.m == MPUPLL_M_1000) {
		usb_cur_lim = TPS65217_USB_INPUT_CUR_LIMIT_1800MA;
		mpu_vdd = TPS65217_DCDC_VOLT_SEL_1325MV;
	} else {
		usb_cur_lim = TPS65217_USB_INPUT_CUR_LIMIT_1300MA;
		mpu_vdd = TPS65217_DCDC_VOLT_SEL_1275MV;
	}
	
	if (tps65217_reg_write(TPS65217_PROT_LEVEL_NONE,
				   TPS65217_POWER_PATH,
				   usb_cur_lim,
				   TPS65217_USB_INPUT_CUR_LIMIT_MASK))
		puts("tps65217_reg_write failure\n");
	
	/* Set DCDC3 (CORE) voltage to 1.125V */
	if (tps65217_voltage_update(TPS65217_DEFDCDC3,
					TPS65217_DCDC_VOLT_SEL_1125MV)) {
		puts("tps65217_voltage_update failure\n");
		return;
	}
	
	/* Set CORE Frequencies to OPP100 */
	do_setup_dpll(&dpll_core_regs, &dpll_core_opp100);
	
	/* Set DCDC2 (MPU) voltage */
	if (tps65217_voltage_update(TPS65217_DEFDCDC2, mpu_vdd)) {
		puts("tps65217_voltage_update failure\n");
		return;
	}
	/*
	 * Set LDO3 to 1.8V and LDO4 to 3.3V for MYD_J335X board.
	 */
	if (tps65217_reg_write(TPS65217_PROT_LEVEL_2,
					   TPS65217_DEFLS1,
					   TPS65217_LDO_VOLTAGE_OUT_1_8,
					   TPS65217_LDO_MASK))
	{		
		puts("tps65217_reg_write failure\n");
	}
	
	if (tps65217_reg_write(TPS65217_PROT_LEVEL_2,
				   TPS65217_DEFLS2,
				   TPS65217_LDO_VOLTAGE_OUT_3_3,
				   TPS65217_LDO_MASK))
	{	
		puts("tps65217_reg_write failure\n");
	}

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
		ddr3_emif_reg_data.sdram_config = MT41J128MJT125_EMIF_SDCFG;
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
