#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

#include "leds_pwm.h"

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
static const struct pwm_dt_spec pwm_led1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
static const struct pwm_dt_spec pwm_led2 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led2));
static const struct pwm_dt_spec pwm_led3 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led3));

void led_pwm_init(void)
{
    pwm_set_dt(&pwm_led0, (uint32_t)1000UL, (uint32_t)200UL);
    pwm_set_dt(&pwm_led1, (uint32_t)1000UL, (uint32_t)200UL);
    pwm_set_dt(&pwm_led2, (uint32_t)1000UL, (uint32_t)200UL);
    pwm_set_dt(&pwm_led3, (uint32_t)1000UL, (uint32_t)200UL);
}
