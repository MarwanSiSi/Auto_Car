#include "pico/stdlib.h"
#include "stdio.h"
#include "ultrasonicBehind.h"

// Variable definitions
volatile uint32_t behind_start_time = 0;
volatile uint32_t behind_end_time = 0;
volatile bool behind_measurement_done = false;


void init_ultrasonic_sensor_behind() {
    gpio_init(TRIGGER_PIN_BEHIND);
    gpio_set_dir(TRIGGER_PIN_BEHIND, GPIO_OUT);
    gpio_put(TRIGGER_PIN_BEHIND, 0);

    gpio_init(ECHO_PIN_BEHIND);
    gpio_set_dir(ECHO_PIN_BEHIND, GPIO_IN);
    
    
}

float get_distance_behind_cm() {
    behind_measurement_done = false;
    
    // Send trigger pulse
    gpio_put(TRIGGER_PIN_BEHIND, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN_BEHIND, 0);
    
    // Wait for measurement to complete or timeout
    uint32_t timeout_start = time_us_32();
    while (!behind_measurement_done) {
        if (time_us_32() - timeout_start > 26000) {
            return -1.0f;
        }
        tight_loop_contents();
    }
    
    // Calculate distance
    uint32_t duration = behind_end_time - behind_start_time;
    float distance = (duration * SOUND_SPEED1) / 2;
    
    return distance;
}