#include <stdbool.h>
#include <stdint.h>

#define DIRECTION_PIN_1 6
#define DIRECTION_PIN_2 7
#define PWM_PIN_BR 8

void motor_init_back_right(void);
void motor_control_back_right(uint8_t speed, bool forward);


