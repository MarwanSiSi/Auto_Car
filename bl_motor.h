#include <stdbool.h>
#include <stdint.h>

#define DIRECTION_PIN_1 16
#define DIRECTION_PIN_2 17
#define PWM_PIN_BL 18

void motor_init_back_left(void);
void motor_control_back_left(uint8_t speed, bool forward);


