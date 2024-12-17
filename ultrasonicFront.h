// ultrasonicFront.h
#ifndef ULTRASONIC_FRONT_H
#define ULTRASONIC_FRONT_H

#include "pico/stdlib.h"

extern volatile uint32_t front_start_time;
extern volatile uint32_t front_end_time;
extern volatile bool front_measurement_done;

// Pin definitions
#define TRIGGER_PIN_FRONT 14
#define ECHO_PIN_FRONT 15
#define SOUND_SPEED2 0.0343

// Variable declarations - note the extern keyword
extern volatile uint32_t front_start_time;
extern volatile uint32_t front_end_time;
extern volatile bool front_measurement_done;

// Function declarations
void init_ultrasonic_sensor_front(void);
float get_distance_front_cm(void);
void echo_isr_front(uint gpio, uint32_t events);

#endif