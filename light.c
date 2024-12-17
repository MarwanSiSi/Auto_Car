#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "light.h"

// initialize the light sensor and set it as input
void init_light_sensor() {
    // enable adc
    adc_init();
    adc_gpio_init(LIGHT_SENSOR_PORT);
    adc_select_input(0);
}

// get the light reading from the light sensor
int get_light_reading() {
    // Read the ADC value (0 to 4095)
    uint16_t light_value = adc_read();  
    
    float voltage = light_value * 3.3f / 4095.0f;

    return voltage * 1000; 
}