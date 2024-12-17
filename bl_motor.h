#include <stdbool.h>
#include <stdint.h>

#define DIRECTION_PIN_3 10
#define DIRECTION_PIN_4 11
#define PWM_PIN_BL 12

void motor_init_back_left(void);
void motor_control_back_left(uint8_t speed, bool forward);


