#include "speed.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int pulse_count = 0;  // Pulse count
float motor_speed = 0.0f;      // Motor speed 

void init_speed_sensor() {
    gpio_init(SPEED_SENSOR_PORT_PIN1);
    gpio_set_dir(SPEED_SENSOR_PORT_PIN1, GPIO_IN);
    
    gpio_init(SPEED_SENSOR_PORT_PIN2);
    gpio_set_dir(SPEED_SENSOR_PORT_PIN2, GPIO_OUT);
    gpio_pull_up(SPEED_SENSOR_PORT_PIN2);
}


int calculate_motor_speed() {
    static uint32_t last_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    uint32_t time_diff = current_time - last_time;
    int motor_speed = 0;

    if (time_diff >= 1000) {  // Every second
        motor_speed = (pulse_count * 60.0f * 1000) / (PULSES_PER_REVOLUTION * time_diff);
                
        pulse_count = 0;
        last_time = current_time;
    }
    
    return motor_speed;
}
