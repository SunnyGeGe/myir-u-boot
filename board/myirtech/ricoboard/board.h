/*
 * board.h
 *
 * Header file for MYIR Tech MYD-C437X board
 *
 * Copyright (C) 2016, MYIR Tech Ltd - http://www.myirtech.com/
 *
 * Author: Sunny Guo <sunny.guo@myirtech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <asm/arch/omap.h>

#define DEV_ATTR_MAX_OFFSET    5
#define DEV_ATTR_MIN_OFFSET    0

static inline int board_is_myd_c437x_evm(void)
{
	return board_myir_is("MYD43EVM");
}

static inline int board_is_myd_c437x_idk(void)
{
	return board_myir_is("MYD43IDK");
}

static inline int board_is_ricoboard(void)
{
	return true;
//	return board_myir_is("RICOBOARD");
}

void set_i2c_pin_mux();
void set_uart_mux_conf(void);
void set_mux_conf_regs(void);
#endif
