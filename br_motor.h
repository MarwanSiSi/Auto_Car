#include <stdbool.h>
#include <stdint.h>

#define DIRECTION_PIN_3 34
#define DIRECTION_PIN_4 32
#define PWM_PIN_BR 3

void motor_init_back_right(void);
void motor_control_back_right(uint8_t speed, bool forward);


