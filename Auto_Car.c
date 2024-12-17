#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "light.h"
#include "fr_motor.h"
#include "fl_motor.h"
#include "bl_motor.h"
#include "br_motor.h"
#include "speed.h"
#include "led.h"
#include "buzzer.h"
#include "ultrasonicFront.h"
#include "ultrasonicBehind.h"
#include "bluetooth.h"


void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == ECHO_PIN_FRONT) {
        if (events & GPIO_IRQ_EDGE_RISE) {
            front_start_time = time_us_32();
        } else if (events & GPIO_IRQ_EDGE_FALL) {
            front_end_time = time_us_32();
            front_measurement_done = true;
        }
    }
    else if (gpio == ECHO_PIN_BEHIND) {
        if (events & GPIO_IRQ_EDGE_RISE) {
            behind_start_time = time_us_32();
        } else if (events & GPIO_IRQ_EDGE_FALL) {
            behind_end_time = time_us_32();
            behind_measurement_done = true;
        }
    }
     else if (gpio == SPEED_SENSOR_PORT_PIN1) {
        if (events & GPIO_IRQ_EDGE_RISE) {
            pulse_count++;
        }
    }
    
}

int main() {
    stdio_init_all();

    // Initialize all peripherals
    init_light_sensor();
    init_led();

    motor_init_front_left();
    motor_init_front_right();
    motor_init_back_left();
    motor_init_back_right();
    
    init_speed_sensor();
    init_buzzer();
    init_ultrasonic_sensor_front();
    init_ultrasonic_sensor_behind();
    init_bluetooth();  // Initialize Bluetooth module

    // Register callback for ultrasonic sensors
    gpio_set_irq_enabled_with_callback(ECHO_PIN_FRONT, 
                                     GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
                                     true,
                                     &gpio_callback);

    gpio_set_irq_enabled(ECHO_PIN_BEHIND, 
                        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
                        true);

    // Register callback for speed sensor
    gpio_set_irq_enabled(SPEED_SENSOR_PORT_PIN1, GPIO_IRQ_EDGE_RISE, true);

    // Variables for buzzer timing
    uint32_t last_beep_time = 0;
    uint32_t current_time;

    while(true) {
        // Check for Bluetooth commands
        while(bluetooth_has_data()) {
            char cmd = bluetooth_read_char();
            process_bluetooth_command(cmd);
        }

        // Regular sensor readings and processing
        float distanceBehind = get_distance_behind_cm();
        float distanceFront = get_distance_front_cm();
       
        
        current_time = to_ms_since_boot(get_absolute_time());
        
        // Graduated beeping based on distance for both sensors
        uint32_t beep_interval = 0;
        bool should_beep = false;
        
        // Check front distance
        if(distanceFront > 0 && distanceFront < 20) {
            should_beep = true;
            if(distanceFront < 5) {
                beep_interval = 100;
            } else if(distanceFront < 10) {
                beep_interval = 300;
            } else {
                beep_interval = 500;
            }
        }
        
        // Check behind distance
        if(distanceBehind > 0 && distanceBehind < 20) {
            should_beep = true;
            uint32_t behind_interval;
            if(distanceBehind < 5) {
                behind_interval = 100;
            } else if(distanceBehind < 10) {
                behind_interval = 300;
            } else {
                behind_interval = 500;
            }
            beep_interval = (beep_interval > 0) ? 
                (behind_interval < beep_interval ? behind_interval : beep_interval) : 
                behind_interval;
        }
        
        // Handle beeping
        if(should_beep && current_time - last_beep_time >= beep_interval) {
            buzzer_on();
            sleep_ms(50);
            buzzer_off();
            last_beep_time = current_time;
        }

        // Light sensor logic
        int readingLight = get_light_reading();
        if(readingLight > 1900) {
            led_on();
        } else {
            led_off();
        }

        // // Print speed
        int rpm_fast = calculate_motor_speed();
        if(rpm_fast > 0)
             bluetooth_send_sensor_data(rpm_fast);  // Send it every loop iteration
        
        sleep_ms(10); // Small delay to prevent tight polling
    }
}