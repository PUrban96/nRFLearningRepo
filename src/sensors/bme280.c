#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

const struct device *bme280_dev = DEVICE_DT_GET_ANY(bosch_bme280);

static struct sensor_value temp, press, hum;

void bme280_init(void)
{
    if (!device_is_ready(bme280_dev))
    {
        printk("BME280 not ready!\n");
    }
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