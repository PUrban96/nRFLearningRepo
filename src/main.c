/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

#define BUTTON0_NODE DT_ALIAS(sw0)
#define BUTTON1_NODE DT_ALIAS(sw1)
#define BUTTON2_NODE DT_ALIAS(sw2)
#define BUTTON3_NODE DT_ALIAS(sw3)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);
static struct gpio_callback button0_callback;

static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(BUTTON1_NODE, gpios);
static struct gpio_callback button1_callback;

static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(BUTTON2_NODE, gpios);
static struct gpio_callback button2_callback;

static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(BUTTON3_NODE, gpios);
static struct gpio_callback button3_callback;

void button0_pressed_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	gpio_pin_toggle_dt(&led0);
}

void button1_pressed_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	gpio_pin_toggle_dt(&led1);
}

void button2_pressed_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	gpio_pin_toggle_dt(&led2);
}

void button3_pressed_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	gpio_pin_toggle_dt(&led3);
}

int main(void)
{
	gpio_pin_configure_dt(&led0, GPIO_OUTPUT);
	gpio_pin_configure_dt(&led1, GPIO_OUTPUT);
	gpio_pin_configure_dt(&led2, GPIO_OUTPUT);
	gpio_pin_configure_dt(&led3, GPIO_OUTPUT);

	gpio_pin_configure_dt(&button0, GPIO_INPUT);
	gpio_pin_configure_dt(&button1, GPIO_INPUT);
	gpio_pin_configure_dt(&button2, GPIO_INPUT);
	gpio_pin_configure_dt(&button3, GPIO_INPUT);

	gpio_init_callback(&button0_callback, button0_pressed_handler, BIT(button0.pin));
	gpio_add_callback(button0.port, &button0_callback);
	gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&button1_callback, button1_pressed_handler, BIT(button1.pin));
	gpio_add_callback(button1.port, &button1_callback);
	gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&button2_callback, button2_pressed_handler, BIT(button2.pin));
	gpio_add_callback(button2.port, &button2_callback);
	gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&button3_callback, button3_pressed_handler, BIT(button3.pin));
	gpio_add_callback(button3.port, &button3_callback);
	gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE);

	while (1)
	{
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
