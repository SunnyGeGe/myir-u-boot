/*
 * PCF8575 I2C GPIO EXPANDER DRIVER
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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

/*
 * Driver for TI pcf-8575 16 bit I2C gpio expander. Based on
 * gpio-pcf857x Linux 4.0 kernel driver and pca953x driver in u-boot
 */

#include <common.h>
#include <i2c.h>
#include <pcf8575.h>

enum {
	PCF8575_CMD_INFO,
	PCF8575_CMD_DEVICE,
	PCF8575_CMD_OUTPUT,
	PCF8575_CMD_INPUT,
};

struct pcf8575_chip {
	uint8_t addr;
/* current direction of the pcf lines */
	unsigned int out;
};


/* NOTE:  these chips have strange "quasi-bidirectional" I/O pins.
 * We can't actually know whether a pin is configured (a) as output
 * and driving the signal low, or (b) as input and reporting a low
 * value ... without knowing the last value written since the chip
 * came out of reset (if any).  We can't read the latched output.
 * In short, the only reliable solution for setting up pin direction
 * is to do it explicitly.
 *
 * Using "out" avoids that trouble. It flags the status of the pins at
 * boot.
 *
 * Each struct stores address of an instance of pcf
 * and state(direction) of each gpio line for that instance.
 */
static struct pcf8575_chip pcf8575_chips[] =
	CONFIG_SYS_I2C_PCF8575_CHIP;

static struct pcf8575_chip *pcf8575_chip_get(uint8_t addr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pcf8575_chips); i++)
		if (pcf8575_chips[i].addr == addr)
			return &pcf8575_chips[i];

	return 0;
}


/* Read/Write to 16-bit I/O expander */

static int pcf8575_i2c_write(uint8_t addr, unsigned word)
{
	unsigned word_be = ((word & 0xff) << 8) |
			   ((word & 0xff00) >> 8);
	uint8_t buf = 0;
	int status;

	status = i2c_write(addr, word_be, 2, &buf, 1);

	return (status < 0) ? status : 0;
}

static int pcf8575_i2c_read(uint8_t addr)
{
	u8 buf[2];
	int status;

	status = i2c_read(addr, 0, 1, buf, 2);
	if (status < 0)
		return status;

	return (buf[1] << 8) | buf[0];
}

int pcf8575_input(uint8_t addr, unsigned offset)
{
	struct pcf8575_chip *chip = pcf8575_chip_get(addr);
	int status;

	chip->out |= (1 << offset);
	status = pcf8575_i2c_write(addr, chip->out);

	return status;
}

int pcf8575_get_val(uint8_t addr, unsigned offset)
{
	int             value;

	value = pcf8575_i2c_read(addr);
	return (value < 0) ? 0 : (value & (1 << offset));
}

int pcf8575_output(uint8_t addr, unsigned offset, int value)
{
	struct pcf8575_chip *chip = pcf8575_chip_get(addr);
	unsigned        bit = 1 << offset;
	int             status;

	if (value)
		chip->out |= bit;
	else
		chip->out &= ~bit;
	status = pcf8575_i2c_write(addr, chip->out);

	return status;
}
