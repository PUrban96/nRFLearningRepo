# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(my_blinky)

set(DIRECTION_APP
    src
    src/leds_buttons
    src/leds_pwm
    src/sensors
)

set(SOURCE_APP
    src/main.c
    src/leds_buttons/leds_buttons.c
    src/leds_pwm/leds_pwm.c
    src/sensors/bme280.c
)

target_sources(app PRIVATE ${SOURCE_APP})
zephyr_include_directories(${DIRECTION_APP})
