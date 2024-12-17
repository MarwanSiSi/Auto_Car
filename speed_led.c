#include "speed_led.h"
#include "pico/stdlib.h"

void init_speed_led() {
    gpio_init(SPEED_LED_PIN);
    gpio_set_dir(SPEED_LED_PIN, GPIO_OUT);
}

void speed_led_on() {
    gpio_put(SPEED_LED_PIN, 1);
}

void speed_led_off() {
    gpio_put(SPEED_LED_PIN, 0);
}