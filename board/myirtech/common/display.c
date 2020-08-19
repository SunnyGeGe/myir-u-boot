/*
 * common.c
 *
 * common board functions for B&R boards
 *
 * Copyright (C) 2013 Hannes Schmelzer <oe5hpm@oevsv.at>
 * Bernecker & Rainer Industrieelektronik GmbH - http://www.br-automation.com
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 */
#include <version.h>
#include <common.h>
#include <errno.h>
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/omap.h>
#include <asm/arch/clock.h>
#include <asm/arch/gpio.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <i2c.h>
#include <miiphy.h>
#include <cpsw.h>
#include <lcd.h>
#include <fs.h>
#include "../../../drivers/video/am335x-fb.h"
//#include "../../../drivers/lcd/image.h"
#include "hw_lcdc.h"
#include "raster.h"
#include "hw_types.h"
#include "hw_control_AM335x.h"
#include "soc_AM335x.h"
#include "hw_cm_per.h"
#include "hw_cm_dpll.h"
#include <nand.h>
#include <fdt_simplefb.h>
#include <splash.h>

static struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

DECLARE_GLOBAL_DATA_PTR;

/* --------------------------------------------------------------------------*/
#if defined(CONFIG_LCD) && defined(CONFIG_AM335X_LCD) && \
	!defined(CONFIG_SPL_BUILD)


/**  
 * \brief  This API returns a unique number which identifies itself  
 *         with the LCDC IP in AM335x SoC.  
 * \param  None  
 * \return This returns a number '2' which is unique to LCDC IP in AM335x.
 */
unsigned int LCDVersionGet(void)
{
    return 2;
}

/**  
 * \brief  This API pin multiplexes the lcd data and control signal lines. 
 * 
 * \param  None  
 */

unsigned int LCDPinMuxSetup(void)
{
    unsigned int profile = 0;

    //profile = EVMProfileGet();

    //if(profile == 0 ||
    //   profile == 1 ||
    //   profile == 2 ||
    //   profile == 7)

    {

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(0)) =
                   (0 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(1)) =
                   (0 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_SLEWCTRL_SHIFT);  

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(2)) =
                   (0 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_SLEWCTRL_SHIFT);  

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(3)) =
                   (0 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(4)) =
                   (0 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_SLEWCTRL_SHIFT); 
 
         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(5)) =
                   (0 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(6)) =
                   (0 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(7)) =
                   (0 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(8)) =
                   (0 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(9)) =
                   (0 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_MMODE_SHIFT)    |
                   (1 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUDEN_SHIFT)    |
                   (0 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUTYPESEL_SHIFT)|
                   (1 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_RXACTIVE_SHIFT) |
                   (0 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(10)) =
                 (0 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_MMODE_SHIFT)    |
                 (1 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUDEN_SHIFT)    |
                 (0 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUTYPESEL_SHIFT)|
                 (1 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_RXACTIVE_SHIFT) |
                 (0 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(11)) =
                 (0 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_MMODE_SHIFT)     |
                 (1 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_RXACTIVE_SHIFT)  |
                   (0 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_SLEWCTRL_SHIFT); 

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(12)) =
                 (0 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_MMODE_SHIFT)     |
                 (1 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(13)) =
                 (0 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_MMODE_SHIFT)     |
                 (1 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(14)) =
                 (0 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_MMODE_SHIFT)     |
                 (1 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(15)) =
                 (0 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_MMODE_SHIFT)     |
                 (1 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(15) ) =
                 (1 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(14) ) =
                 (1 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUTYPESEL_SHIFT) |
                 (1<< CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(13) ) =
                 (1 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_RXACTIVE_SHIFT)  |
                   (0 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(12) ) =
                 (1 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUTYPESEL_SHIFT) |
                 (1<< CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(11) ) =
                 (1 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUTYPESEL_SHIFT) |
                 (1<< CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(10) ) =
                 (1 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(9) ) =
                 (1 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(8) ) =
                 (1 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_VSYNC) =
                 (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_HSYNC) =
                 (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_PCLK) =
                 (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_SLEWCTRL_SHIFT);

         HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_AC_BIAS_EN) =
                 (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_MMODE_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUDEN_SHIFT)     |
                 (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUTYPESEL_SHIFT) |
                 (1 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_RXACTIVE_SHIFT)  |
                 (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_SLEWCTRL_SHIFT);
         return TRUE;
     }
     return FALSE;
}


/**
 * \brief   This function will configure the required clocks for LCDC instance.
 *
 * \return  None.
 *
 */
void LCDModuleClkConfig(void)
{
    HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) |= 
                             CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;


    while((HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & 
     CM_PER_L3S_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) |= 
                             CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & 
     CM_PER_L3_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) |= 
                             CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) & 
                               CM_PER_L3_INSTR_CLKCTRL_MODULEMODE) != 
                                   CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) |= 
                             CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) & 
        CM_PER_L3_CLKCTRL_MODULEMODE) != CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) |= 
                             CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & 
                              CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL) != 
                                CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) |= 
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & 
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL) != 
                               CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) |= 
                             CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) & 
      CM_PER_L4LS_CLKCTRL_MODULEMODE) != CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE);

    /* lcd pixel clock is derived from peripheral pll */
    /* Using reset value, modify by panxeusong @ 2017.6.22 */   
    HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_LCDC_PIXEL_CLK) = 
                             CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL1;

    HWREG(SOC_PRCM_REGS + CM_PER_LCDC_CLKCTRL) |= 
                             CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_LCDC_CLKCTRL) & 
      CM_PER_LCDC_CLKCTRL_MODULEMODE) != CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE);

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & 
            CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & 
            CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & 
           (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK | 
            CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & 
           (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK | 
            CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK)));
    
}


/**
* \brief This function Enables the clock for the DMA submodule,LIDD submodule and
*        for the core(which encompasses the Raster active matrix and Passive matrix).
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterClocksEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) =  (LCDC_CLKC_ENABLE_CORE |
                                           LCDC_CLKC_ENABLE_DMA  |
                                           LCDC_CLKC_ENABLE_LIDD);
}

/**
* \brief  This function will Enable Raster Control.\n
*
* \param baseAddr is the Memory address of the LCD.\n
*
* \return none.
**/
void RasterEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_RASTER_EN;
}

/**
* \brief  This function will Disable Raster Control.\n
*
* \param baseAddr is the Memory address of the LCD.\n
*
* \return none.
**/
void RasterDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_RASTER_EN;
}

/**
* \brief  This function orders the frame buffer data from
*         least to most significant bit bit/nibble/byte/word/
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \return None.   
**/
void RasterLSBDataOrderSelect(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_RD_ORDER; 
}

/**
* \brief  This function orders the frame buffer data from
*         most to least significant bit bit/nibble/byte/word/
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \return None.
**/
void RasterMSBDataOrderSelect(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_RD_ORDER;
}

/**
* \brief  This function will configures LCD to MonoChrome or color mode,
*         TFT or STN mode and palette loading mode.\n
*
* \param baseAddr    is the Memory address of the LCD.\n
* \param displayMode is the vlaue to select either TFT or STN mode.\n
*
*         displayMode can take following value.\n
*
*         RASTER_DISPLAY_MODE_TFT  -  TFT mode is selected.\n
*         RASTER_DISPLAY_MODE_STN  -  STN mode is selected.\n
*
*         Below mentioned macros are only applicable to AM335x.
*
*         RASTER_DISPLAY_MODE_TFT_PACKED   - TFT mode is selected with
*                                            24 bit packed data support.  
*         RASTER_DISPLAY_MODE_TFT_UNPACKED - TFT mode is selected with
*                                            24 bit unpacked data support.  
*
* \param displayType is the value to select either color or monochrome mode.\n
*
*         displayType can take following value.\n
*
*         RASTER_MONOCHROME  - monochrome mode is selected.\n
*         RASTER_COLOR       - color mode is selected.\n
*         
* \param paletteMode is the value to select type of palette loading.\n
* 
*        paletteMode can take following values.\n
*         
*        RASTER_PALETTE_DATA   - palette and  data is loaded.\n
*        RASTER_PALETTE        - only palette is loaded.\n
*        RASTER_DATA           - only data is loaded.\n
*
* \param flag  Optional argument depending on the display mode and type
* 
*        flag can take following values.\n
*
*        RASTER_RIGHT_ALIGNED - Right aligned output pixel data
*        RASTER_EXTRAPOLATE   - Extrapolated (to RGB565) output pixel data
*        RASTER_MONO8B        - Output 8 bit mono pixel data
*        RASTER_MONO4B        - Output 4 bit mono pixel data
* 
* \return none.
**/
void RasterModeConfig(unsigned int baseAddr, unsigned int displayMode,
                      unsigned int paletteMode, unsigned int displayType,
                      unsigned flag)
{
    /* Configures raster to TFT or STN Mode */
    HWREG(baseAddr + LCDC_RASTER_CTRL) = displayMode | paletteMode | displayType;

    if(displayMode ==  RASTER_DISPLAY_MODE_TFT)
    {
         if(flag == RASTER_RIGHT_ALIGNED)
         {
              /* Output pixel data for 1,2,4 and 8 bpp is converted to 565 format */
              HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~(LCDC_RASTER_CTRL_TFT_ALT_MAP);
         }
         else
         {
              /* Output pixel data for 1,2,4 and 8 bpp will be right aligned */
             HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_TFT_ALT_MAP;
         }
    }
    else
    {
         if(flag ==  RASTER_MONO8B)
         {
              HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_MONO8B;
         }
         else
         {
              HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_MONO8B;
         }
    }
}

/**
* \brief  This function configures clkdiv to generate required frequency of 
*         of pixel clock and selects the raster control.\n
*
* \param  baseAddr   is the Memory address of LCD.\n
* \param  pClk       is the required Pixel Clock frequency.\n
* \param  modulck    is the input clk to LCD module from PLL.\n
* 
* \return none.
**/
void RasterClkConfig(unsigned int baseAddr, unsigned int pClk,
                     unsigned int moduleClk)
{
    unsigned int clkDiv;

    clkDiv = moduleClk / pClk ;

    HWREG(baseAddr + LCDC_LCD_CTRL) = LCDC_LCD_CTRL_MODESEL;
   
    HWREG(baseAddr + LCDC_LCD_CTRL) |= (clkDiv <<  LCDC_LCD_CTRL_CLKDIV_SHIFT);
}

/**
* \brief This function configures input FIFO delay.
*
* \param baseAddr is the Memory address of LCD module.
*
* \return None
**/
void RasterFIFODMADelayConfig(unsigned int baseAddr, unsigned int delay)
{

    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_FIFO_DMA_DELAY;
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= (delay <<                  \
                                          LCDC_RASTER_CTRL_FIFO_DMA_DELAY_SHIFT);
}
/**
* \brief This function configuers horizontal timing parametes and number of 
*        pixel per line.
*
* \param baseAddr is the Memory address of the LCD module
*
* \param numOfppl is a value which determine no of pixel required per line.
*
* \param hsw      is a value which detemines the width of HSYNC.
*
* \param hfp      horizontal front porch.
*
* \para  hbp      horizontal back porch.
**/
void RasterHparamConfig(unsigned int baseAddr, unsigned int numOfppl,
                        unsigned int hsw, unsigned int hfp,
                        unsigned hbp)
{
    unsigned int ppl;
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         ppl = numOfppl - 1;

         ppl = (ppl & 0x000003f0) | ((ppl & 0x00000400) >> 7);

         HWREG(baseAddr + LCDC_RASTER_TIMING_0) = ppl; 
    }
    else if(RASTER_REV_AM1808 == version)
    {
   
         ppl = (numOfppl / 16) - 1;

         HWREG(baseAddr + LCDC_RASTER_TIMING_0) =  (ppl <<                       
                                                LCDC_RASTER_TIMING_0_PPL_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }
    
    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hsw - 1) <<                   
                                               LCDC_RASTER_TIMING_0_HSW_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hfp - 1) <<                   
                                               LCDC_RASTER_TIMING_0_HFP_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hbp - 1) <<
                                               LCDC_RASTER_TIMING_0_HBP_SHIFT);
}

/**
* \brief This function configuers vertical timing parameters and number of
*        lines per panel.
*
* \param baseAddr is the Memory address of the LCD module
*
* \param lpp      is a value which determine the lines per panel.
*
* \param vsw      is a value which detemines the width of VSYNC.
*
* \param vfp      vertical front porch.
*
* \para  vbp      vertical back porch.
**/
void RasterVparamConfig(unsigned int baseAddr, unsigned int lpp,
                        unsigned int vsw, unsigned int vfp,
                        unsigned vbp)
{
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {

         HWREG(baseAddr + LCDC_RASTER_TIMING_1) = ((lpp - 1) & 0x3ff);

         HWREG(baseAddr + LCDC_RASTER_TIMING_2) &=  0xfbffffff;
  
         HWREG(baseAddr + LCDC_RASTER_TIMING_2) |=  (((lpp - 1) & 0x400) >> 10) 
                                                    << LCDC_RASTER_TIMING_2_LPP_B10_SHIFT;           
    }
    else if(RASTER_REV_AM1808 == version)
    {
 
         HWREG(baseAddr + LCDC_RASTER_TIMING_1) =  ((lpp - 1) <<             
                                              LCDC_RASTER_TIMING_1_LPP_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= ((vsw - 1) <<                  
                                               LCDC_RASTER_TIMING_1_VSW_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vfp <<                       
                                               LCDC_RASTER_TIMING_1_VFP_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vbp <<
                                               LCDC_RASTER_TIMING_1_VBP_SHIFT);
}
/** 
* \brief This function configures the polartiy of various timing parameters of
*        LCD Controller.
*
* \param baseAddr  is the Memory Address of the LCD Module.
*
* \param flag      is the value which detemines polarity of various timing 
*                  parameter of LCD controller.\n
*
*                  flag can take following values.\n 
*
*                   RASTER_FRAME_CLOCK_HIGH - active high frame clock.\n                
*                   RASTER_FRAME_CLOCK_LOW  - active low frame clock.\n
*                   RASTER_LINE_CLOCK_HIGH  - active high line clock.\n
*                   RASTER_LINE_CLOCK_LOW   - active low line clock.\n
*                   RASTER_PIXEL_CLOCK_HIGH - active high pixel clock.\n               
*                   RASTER_PIXEL_CLOCK_LOW  - active low pixel clock.\n               
*                   RASTER_AC_BIAS_HIGH     - active high ac bias.\n           
*                   RASTER_AC_BIAS_LOW      - active low ac bias.\n          
*                   RASTER_SYNC_EDGE_RISING - rising sync edge.\n
*                   RASTER_SYNC_EDGE_FALLING- falling sync edge.\n
*                   RASTER_SYNC_CTRL_ACTIVE - active sync control.\n
*                   RASTER_SYNC_CTRL_INACTIVE-inactive sync control.\n
*
* \param acb_i      is the value which specify the number of AC Bias
*                   (LCD_AC_ENB_CS) output transition counts before 
*                   setting the AC bias interrupt bit in register LCD_STAT.
*
* \param acb        is value which defines the number of Line Clock
*                   (LCD_HSYNC) cycles to count before transitioning
*                    signal LCD_AC_ENB_CS.
*
* \return None.
*
**/
void RasterTiming2Configure(unsigned int baseAddr, unsigned int flag,
                            unsigned int acb_i, unsigned int acb)
{
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= flag;

    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb_i <<                    \
                                              LCDC_RASTER_TIMING_2_ACB_I_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb <<                      \
                                             LCDC_RASTER_TIMING_2_ACB_SHIFT);

}
/**
* \brief This function configures DMA present inside LCD controller.
*
* \param  baseAddr is the Memory address of LCD module.
*
* \param  frmMode  is the value which detemines either to use single frame 
*                  or double frame buffer.\n
*
*                 frmMode can take following values.\n
*
*                 RASTER_SINGLE_FRAME_BUFFER - single frame buffer.\n     
*                 RASTER_DOUBLE_FRAME_BUFFER - double frame buffer.\n
*          
* \param bustSz   is the value which detemines burst size of DMA.\n
* 
*                 bustSz can take following values.\n
* 
*                 RASTER_BURST_SIZE_1   -  burst size of DMA is one.\n                
*                 RASTER_BURST_SIZE_2   -  burst size of DMA is two.\n            
*                 RASTER_BURST_SIZE_4   -  burst size of DMA is four.\n              
*                 RASTER_BURST_SIZE_16  -  burst size of DMA is sixteen.\n
*
* \param fifoTh   is the value which detemines when the input FIFO can be 
*                 read by raster controller.\n
*
*                 fifoTh can take following values.\n
*
*                 RASTER_FIFO_THRESHOLD_8    -   DMA FIFO Threshold is eight.\n             
*                 RASTER_FIFO_THRESHOLD_16   -   DMA FIFO Threshold is sixteen.\n          
*                 RASTER_FIFO_THRESHOLD_32   -   DMA FIFO Threshold is thirtytwo.\n       
*                 RASTER_FIFO_THRESHOLD_64   -   DMA FIFO Threshold is sixtyfour.\n     
*                 RASTER_FIFO_THRESHOLD_128  -   DMA FIFO Threshold is one twenty 
*                                                eight.\n
*                 RASTER_FIFO_THRESHOLD_256  -   DMA FIFO Threshold is two 
*                                                fifty six.\n     
*                 RASTER_FIFO_THRESHOLD_512  -   DMA FIFO Threshold is five 
*                                                twelve.\n    
*
* \param endian   is value determines whether to use big endian for data 
*                 reordering or not.\n
*
*                 endian can take following values.\n
*
*                 RASTER_BIG_ENDIAN_ENABLE - big endian enabled.\n
*                 RASTER_BIG_ENDIAN_ENABLE - big endian disabled.\n
*
* \return None
**/          
void RasterDMAConfig(unsigned int baseAddr, unsigned int frmMode,
                     unsigned int bustSz, unsigned int fifoTh,
                     unsigned int endian)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) = frmMode | bustSz | fifoTh | endian;
}

/**
* \brief  This function configures base and ceiling value for
*         Frame buffer one or Frame buffer two.
*
* \param  baseAddr is the Memory Address of the LCD Module
*
* \param  base     is the base address of array which contain
*                  pixels of image to be dispalyed on lcd.
*
* \param  ceiling  is the end address of the array which contain
*                  pixels of image to be displayed on lcd.
*
* \param  flag     is the value which determines whether to write 
*                  base and ceiling to Frame Buffer one or Fram buffer two.
*
*         passing zero(i.e. 0) as argument configures base and ceiling for
*         frame buffer zero(i.e FB0).
*
*         passing one(i.e. 0) as argument configures base and ceiling for
*         frame buffer one(i.e FB1).
*
* \return None.   
*
**/
void RasterDMAFBConfig(unsigned int baseAddr, unsigned int base,
                       unsigned int  ceiling, unsigned int flag)
{
    if(flag == 0)
    {
         HWREG(baseAddr + LCDC_LCDDMA_FB0_BASE) =  base;
         HWREG(baseAddr + LCDC_LCDDMA_FB0_CEILING) = ceiling;
    }
    else
    {
         HWREG(baseAddr + LCDC_LCDDMA_FB1_BASE) =  base;
         HWREG(baseAddr + LCDC_LCDDMA_FB1_CEILING) = ceiling;
    }
}

void RasterIntEnable(unsigned int baseAddr, unsigned int flag)
{
    unsigned int version = 0;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         HWREG(baseAddr + LCDC_IRQENABLE_SET) |= flag;
    }
    else if(RASTER_REV_AM1808 == version)
    {
         HWREG(baseAddr + LCDC_RASTER_CTRL) |= flag;
    }
    else
    {
         ;/* Do nothing */
    }
}

							

void lcdbacklight(int on)
{
	gpio_set_value(2, on);
}

int load_lcdtiming(struct am335x_lcdpanel *panel)
{
	struct am335x_lcdpanel pnltmp;
	pnltmp.hactive = getenv_ulong("ds1_hactive", 10, 1024UL);
	pnltmp.vactive = getenv_ulong("ds1_vactive", 10, 600UL);
	pnltmp.bpp = getenv_ulong("ds1_bpp", 10, 32UL);
	pnltmp.hfp = getenv_ulong("ds1_hfp", 10, 43UL);
	pnltmp.hbp = getenv_ulong("ds1_hbp", 10, 159UL);
	pnltmp.hsw = getenv_ulong("ds1_hsw", 10, 115UL);
	pnltmp.vfp = getenv_ulong("ds1_vfp", 10, 8UL);
	pnltmp.vbp = getenv_ulong("ds1_vbp", 10, 24UL);
	pnltmp.vsw = getenv_ulong("ds1_vsw", 10, 2UL);
	pnltmp.pxl_clk_div = getenv_ulong("ds1_pxlclkdiv", 10, 51000000UL);
	pnltmp.pxl_clk_div = 102000000/pnltmp.pxl_clk_div;
	pnltmp.pol = getenv_ulong("ds1_pol", 16, 1UL);
	pnltmp.pup_delay = getenv_ulong("ds1_pupdelay", 10, 10UL);
	pnltmp.pon_delay = getenv_ulong("ds1_tondelay", 10, 10UL);
	panel_info.vl_rot = getenv_ulong("ds1_rotation", 10, 0);
	{
		puts("lcd-settings in env/dtb incomplete!\n");
		printf("display-timings:\n"
			"hactive: %d\n"
			"vactive: %d\n"
			"bpp    : %d\n"
			"hfp    : %d\n"
			"hbp    : %d\n"
			"hsw    : %d\n"
			"vfp    : %d\n"
			"vbp    : %d\n"
			"vsw    : %d\n"
			"pxlclk : %d\n"
			"pol    : 0x%08x\n"
			"pupdly: %d\n"
			"pondly : %d\n",
			pnltmp.hactive, pnltmp.vactive, pnltmp.bpp,
			pnltmp.hfp, pnltmp.hbp, pnltmp.hsw,
			pnltmp.vfp, pnltmp.vbp, pnltmp.vsw,
			pnltmp.pxl_clk_div, pnltmp.pol, pnltmp.pup_delay, pnltmp.pon_delay);

	}
	debug("lcd-settings in env complete, taking over.\n");
	memcpy((void *)panel,
	       (void *)&pnltmp,
	       sizeof(struct am335x_lcdpanel));

	return 0;
}

static void br_summaryscreen_printenv(char *prefix,
				       char *name, char *altname,
				       char *suffix)
{
	char *envval = getenv(name);
	if (0 != envval) {
		lcd_printf("%s %s %s", prefix, envval, suffix);
	} else if (0 != altname) {
		envval = getenv(altname);
		if (0 != envval)
			lcd_printf("%s %s %s", prefix, envval, suffix);
	} else {
		lcd_printf("\n");
	}
}
void br_summaryscreen(void)
{
	br_summaryscreen_printenv(" - B&R -", "br_orderno", 0, "-\n");
	br_summaryscreen_printenv(" Serial/Rev :", "br_serial", 0, "\n");
	br_summaryscreen_printenv(" MAC (IF1)  :", "br_mac1", "ethaddr", "\n");
	br_summaryscreen_printenv(" MAC (IF2)  :", "br_mac2", 0, "\n");
	lcd_puts(" Bootloader : " PLAIN_VERSION "\n");
	lcd_puts("\n");
}

vidinfo_t	panel_info = {
		.vl_col = 1366,	/*
				 * give full resolution for allocating enough
				 * memory
				 */
		.vl_row = 768,
		.vl_bpix = 5,
		.priv = 0
};

u8 Log2EX(u32 x)  
{  
	u8 i=0;
	for(i=31;i>=0;i--)
	{
		if(1 ==((x>>i)&0x1)){
			break;
		}
	}
    return i;  
} 

void lcdpower(int on)
{
	
}

struct splash_location splash_locations[] = {
	{
		.name = "nand",
		.storage = SPLASH_STORAGE_NAND,
		.flags = SPLASH_STORAGE_RAW,
		.offset = 0xe000000,
	},
};


void lcd_ctrl_init(void *lcdbase)
{
	struct am335x_lcdpanel lcd_panel;
	memset(&lcd_panel, 0, sizeof(struct am335x_lcdpanel));
	if (load_lcdtiming(&lcd_panel) != 0)
		return;

	panel_info.vl_bpix = Log2EX(lcd_panel.bpp);
	panel_info.vl_col = lcd_panel.hactive;
	panel_info.vl_row = lcd_panel.vactive;

	lcd_panel.panel_power_ctrl = &lcdpower;
		/* Enable clock for LCD Module */
	LCDModuleClkConfig();
	LCDPinMuxSetup();	
#if 0	
		/*
		**Clock for DMA,LIDD and for Core(which encompasses
		** Raster Active Matrix and Passive Matrix logic)
		** enabled.
		*/
		RasterClocksEnable(SOC_LCDC_0_REGS);
	
		/* Disable raster */
		RasterDisable(SOC_LCDC_0_REGS);
	
		/* Configure the pclk */
	//	  RasterClkConfig(SOC_LCDC_0_REGS, 23040000, 192000000);
		RasterClkConfig(SOC_LCDC_0_REGS, 30000000, 192000000);
	
		/* Configuring DMA of LCD controller */
		RasterDMAConfig(SOC_LCDC_0_REGS, RASTER_DOUBLE_FRAME_BUFFER,
						RASTER_BURST_SIZE_16, RASTER_FIFO_THRESHOLD_8,
						RASTER_BIG_ENDIAN_DISABLE);
	
		/* Configuring modes(ex:tft or stn,color or monochrome etc) for raster controller */
	//	  RasterModeConfig(SOC_LCDC_0_REGS, RASTER_DISPLAY_MODE_TFT_UNPACKED,
	//					   RASTER_PALETTE_DATA, RASTER_COLOR, RASTER_RIGHT_ALIGNED);
		RasterModeConfig(SOC_LCDC_0_REGS, RASTER_DISPLAY_MODE_TFT_UNPACKED,
						 RASTER_DATA, RASTER_COLOR, RASTER_RIGHT_ALIGNED);
	
	
		/* Configuring the polarity of timing parameters of raster controller */
		RasterTiming2Configure(SOC_LCDC_0_REGS, RASTER_FRAME_CLOCK_LOW |
												RASTER_LINE_CLOCK_LOW  |
												RASTER_PIXEL_CLOCK_HIGH|
												RASTER_SYNC_EDGE_RISING|
												RASTER_SYNC_CTRL_ACTIVE|
												RASTER_AC_BIAS_HIGH 	, 0, 255);
	
		/* Configuring horizontal timing parameter */
		//RasterHparamConfig(SOC_LCDC_0_REGS, 480, 4, 8, 43);
		RasterHparamConfig(SOC_LCDC_0_REGS, lcd_panel.hactive, lcd_panel.hsw, lcd_panel.hfp, lcd_panel.hbp);
	
		/* Configuring vertical timing parameters */
		//RasterVparamConfig(SOC_LCDC_0_REGS, 272, 10, 4, 12);
		RasterVparamConfig(SOC_LCDC_0_REGS, lcd_panel.vactive, lcd_panel.vsw, lcd_panel.vfp, lcd_panel.vbp);
	
	
		RasterFIFODMADelayConfig(SOC_LCDC_0_REGS, 128);
#if 0
   // Configuring the base ceiling
   RasterDMAFBConfig(SOC_LCDC_0_REGS,
					 (unsigned int)image,
					 (unsigned int)image + sizeof(image) - 2,
					 0);

   RasterDMAFBConfig(SOC_LCDC_0_REGS,
					 (unsigned int)image,
					 (unsigned int)image + sizeof(image) - 2,
					 1);
#else
   // Configuring the base ceiling
   RasterDMAFBConfig(SOC_LCDC_0_REGS,
					 gd->fb_base,
					 gd->fb_base + (lcd_panel.hactive * lcd_panel.vactive *lcd_panel.bpp)<<3,
					 0);

   RasterDMAFBConfig(SOC_LCDC_0_REGS,
					 gd->fb_base,
					 gd->fb_base + (lcd_panel.hactive * lcd_panel.vactive *lcd_panel.bpp)<<3,
					 1);

#endif
   // Enable End of frame0/frame1 interrupt
   RasterIntEnable(SOC_LCDC_0_REGS, RASTER_END_OF_FRAME0_INT |
									RASTER_END_OF_FRAME1_INT);
   // Enable raster
   RasterEnable(SOC_LCDC_0_REGS);
//	 LCDBackLightEnable();

#else

	size_t read_size = 0x200000;
	
	nand_read_skip_bad(&nand_info[nand_curr_device], 0xe000000,
				  &read_size, NULL,
				  nand_info[nand_curr_device].size,
				  (u_char *)0x84000000);

	if (0 != am335xfb_init(&lcd_panel))
		printf("ERROR: failed to initialize video!");
#endif
	/*
	 * modifiy panel info to 'real' resolution, to operate correct with
	 * lcd-framework.
	 */
	panel_info.vl_col = lcd_panel.hactive;
	panel_info.vl_row = lcd_panel.vactive;

	lcd_set_flush_dcache(1);
}

void lcd_enable(void)
{
	br_summaryscreen();
	
	bmp_display(0x84000000, 0, 0);
	gpio_request(GPIO_TO_PIN(3,20), "lcd_vdd");
	gpio_request(GPIO_TO_PIN(1,18), "lcd_rst");
	gpio_request(GPIO_TO_PIN(0,19), "lcd_disp");
	gpio_direction_output(GPIO_TO_PIN(3,20), 0);
	mdelay(150);
	gpio_direction_output(GPIO_TO_PIN(1,18), 0);
	gpio_direction_output(GPIO_TO_PIN(0,19), 1);
	mdelay(150);
	gpio_direction_output(GPIO_TO_PIN(3,20), 1);
	gpio_direction_output(GPIO_TO_PIN(1,18), 0);
//	gpio_set_value(GPIO_TO_PIN(0,19), 1);
	mdelay(250);
	gpio_direction_output(GPIO_TO_PIN(1,18), 1);
//	gpio_direction_output(GPIO_TO_PIN(0,19),1);

	lcdbacklight(1);
}
#elif CONFIG_SPL_BUILD
#else
#error "LCD-support with a suitable FB-Driver is mandatory !"
#endif /* CONFIG_LCD */
void lcd_setcolreg(ushort regno, ushort red, ushort green, ushort blue) {}


int overwrite_console(void)
{
	return 1;
}
