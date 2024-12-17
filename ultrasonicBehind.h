#ifndef ULTRASONIC_BEHIND_H
#define ULTRASONIC_BEHIND_H

#include "pico/stdlib.h"

extern volatile uint32_t behind_start_time;
extern volatile uint32_t behind_end_time;
extern volatile bool behind_measurement_done;

// Pin definitions
#define TRIGGER_PIN_BEHIND 14
#define ECHO_PIN_BEHIND 15
#define SOUND_SPEED1 0.0343

// Variable declarations
extern volatile uint32_t behind_start_time;
extern volatile uint32_t behind_end_time;
extern volatile bool behind_measurement_done;

// Function declarations
void init_ultrasonic_sensor_behind(void);
float get_distance_behind_cm(void);
void echo_isr_behind(uint gpio, uint32_t events);

#endif