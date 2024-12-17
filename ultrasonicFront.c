#include "pico/stdlib.h"
#include "stdio.h"
#include "ultrasonicFront.h"

// Variable definitions
volatile uint32_t front_start_time = 0;
volatile uint32_t front_end_time = 0;
volatile bool front_measurement_done = false;

void init_ultrasonic_sensor_front() {
    gpio_init(TRIGGER_PIN_FRONT);
    gpio_set_dir(TRIGGER_PIN_FRONT, GPIO_OUT);
    gpio_put(TRIGGER_PIN_FRONT, 0);

    gpio_init(ECHO_PIN_FRONT);
    gpio_set_dir(ECHO_PIN_FRONT, GPIO_IN);
    
    
}

float get_distance_front_cm() {
    front_measurement_done = false;
    
    // Send trigger pulse
    gpio_put(TRIGGER_PIN_FRONT, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN_FRONT, 0);
    
    // Wait for measurement to complete or timeout
    uint32_t timeout_start = time_us_32();
    while (!front_measurement_done) {
        if (time_us_32() - timeout_start > 26000) {
            return -1.0f;
        }
        tight_loop_contents();
    }
    
    // Calculate distance
    uint32_t duration = front_end_time - front_start_time;
    float distance = (duration * SOUND_SPEED2) / 2;
    
    return distance;
}