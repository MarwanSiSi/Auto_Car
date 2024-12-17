#include "stdbool.h"

#define FL_MOTOR_PIN1 6
#define FL_MOTOR_PIN2 7
#define FL_MOTOR_PWM_PIN 8


// function declarations
void motor_init_front_left();
void motor_control_front_left(int speed, bool forward);
