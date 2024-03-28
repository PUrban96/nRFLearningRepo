#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

#include "bme280.h"

const struct device *bme280_dev = DEVICE_DT_GET_ANY(bosch_bme280);

static struct sensor_value temp, press, hum;

static void readTimerExpiryCallback(struct k_timer *timer_id);
static void readWorkCallback(struct k_work *work_id);
static void printTimerExpiryCallback(struct k_timer *timer_id);

K_WORK_DEFINE(bme280ReadWorkQueue, readWorkCallback);
K_TIMER_DEFINE(bme280ReadTimer, readTimerExpiryCallback, NULL);
K_TIMER_DEFINE(bme280PrintTimer, printTimerExpiryCallback, NULL);

void bme280_init(void)
{
    if (!device_is_ready(bme280_dev))
    {
        printk("BME280 not ready!\n");
    }
    else
    {
        k_timer_start(&bme280ReadTimer, K_SECONDS(1), K_SECONDS(1));
        k_timer_start(&bme280PrintTimer, K_SECONDS(2), K_SECONDS(2));
        printk("BME280 ready!\n");
    }
}

static void readTimerExpiryCallback(struct k_timer *timer_id)
{
    k_work_submit(&bme280ReadWorkQueue);
}

static void readWorkCallback(struct k_work *work_id)
{
    bme280_readAllChannel();
}

static void printTimerExpiryCallback(struct k_timer *timer_id)
{
    printf("Temperature = %.1fst.C ", bme280_getTemperature());
    printf("Pressure = %.1fhPa ", bme280_getPressure());
    printf("Humidity = %.1f% \r\n", bme280_getHumidity());
}

void bme280_readAllChannel(void)
{
    sensor_sample_fetch(bme280_dev);
    sensor_channel_get(bme280_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    sensor_channel_get(bme280_dev, SENSOR_CHAN_PRESS, &press);
    sensor_channel_get(bme280_dev, SENSOR_CHAN_HUMIDITY, &hum);
}

double bme280_getTemperature(void)
{
    return sensor_value_to_double(&temp);
}

double bme280_getPressure(void)
{
    return sensor_value_to_double(&press) * 10.0;
}

double bme280_getHumidity(void)
{
    return sensor_value_to_double(&hum);
}