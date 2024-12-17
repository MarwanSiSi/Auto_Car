#include "stdbool.h"

#define FR_MOTOR_PIN1 16
#define FR_MOTOR_PIN2 17
#define FR_MOTOR_PWM_PIN 18


// function declarations
void motor_init_front_right();
void motor_control_front_right(int speed, bool forward);
