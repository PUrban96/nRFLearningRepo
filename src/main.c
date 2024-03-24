/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "leds_buttons.h"
#include "leds_pwm.h"
#include "bme280.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

int main(void)
{
	// leds_buttons_init();
	led_pwm_init();
	bme280_init();
	printk("My blinky app!\n");

	while (1)
	{
		bme280_readAllChannel();

		printf("Temperature = %.1fst.C ", bme280_getTemperature());
		printf("Pressure = %.1fhPa ", bme280_getPressure());
		printf("Humidity = %.1f% \r\n", bme280_getHumidity());

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
