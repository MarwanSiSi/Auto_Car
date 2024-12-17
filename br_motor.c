#include "br_motor.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

void motor_init_back_right(void) {
    gpio_init(DIRECTION_PIN_3);
    gpio_set_dir(DIRECTION_PIN_3, GPIO_OUT);

    gpio_init(DIRECTION_PIN_4);
    gpio_set_dir(DIRECTION_PIN_4, GPIO_OUT);
    
    gpio_set_function(PWM_PIN_BR, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN_BR);

    pwm_set_wrap(slice_num, 255); // speed levels
    pwm_set_clkdiv(slice_num, 4.0f);

    pwm_set_enabled(slice_num, true); // enable pwm for the slice
}

void motor_control_back_right(uint8_t speed, bool forward) {
    if(speed > 255){
        speed = 255;
    }
    else if(speed == 0 || speed < 0){
        speed = 0;
    }
    else if(speed < 151){
        speed = 151;
    }

    if(forward){
        gpio_put(DIRECTION_PIN_3, 0); 
        gpio_put(DIRECTION_PIN_4, 1);
    }else{
        gpio_put(DIRECTION_PIN_3, 1);
        gpio_put(DIRECTION_PIN_4, 0);
    }

    // Set the PWM duty cycle (range is BRom 0 to 255)
    pwm_set_gpio_level(PWM_PIN_BR, speed);  // Channel A controls the motor
    
}