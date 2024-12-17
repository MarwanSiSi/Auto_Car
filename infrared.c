#include "infrared.h"
#include "pico/stdlib.h"


void init_infrared_sensor() {
    gpio_init(INFRARED_SENSOR_PORT);
    gpio_set_dir(INFRARED_SENSOR_PORT, GPIO_IN);
}

bool get_infrared_reading() {
    return gpio_get(INFRARED_SENSOR_PORT);
}