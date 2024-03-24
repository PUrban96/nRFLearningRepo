#pragma once

void bme280_init(void);

void bme280_readAllChannel(void);

double bme280_getTemperature(void);
double bme280_getPressure(void);
double bme280_getHumidity(void);
