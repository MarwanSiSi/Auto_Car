#include "bluetooth.h"
#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "fr_motor.h"
#include "fl_motor.h"
#include "bl_motor.h"
#include "br_motor.h"


void init_bluetooth(void) {
    // Initialize UART for Bluetooth
    uart_init(BLUETOOTH_UART, BLUETOOTH_BAUD_RATE);
    
    // Set GPIO pins to UART function
    gpio_set_function(BLUETOOTH_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(BLUETOOTH_RX_PIN, GPIO_FUNC_UART);
    
    // Enable UART FIFO
    uart_set_fifo_enabled(BLUETOOTH_UART, false);
}

void bluetooth_send_sensor_data(int speed) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "RPM: %d", speed); 
    uart_puts(BLUETOOTH_UART, buffer);
    uart_puts(BLUETOOTH_UART, "\n"); 
}

void bluetooth_send_message(const char* message) {
    uart_puts(BLUETOOTH_UART, message);
    uart_puts(BLUETOOTH_UART, "\n"); 
}

bool bluetooth_has_data(void) {
    return uart_is_readable(BLUETOOTH_UART);
}

char bluetooth_read_char(void) {
    return uart_getc(BLUETOOTH_UART);
}

void process_bluetooth_command(char cmd) {
    switch(cmd) {
        case CMD_FORWARD:
            motor_control_front_left(255, false);
            motor_control_front_right(255, false);
            motor_control_back_left(255, false);
            motor_control_back_right(255, false);
            break;
            
        case CMD_BACKWARD:
            motor_control_front_left(255, true);
            motor_control_front_right(255, true);
            motor_control_back_left(255, true);
            motor_control_back_right(255, true);
            break;
            
        case CMD_LEFT:
            // Left side motors slow/stopped
            motor_control_front_left(0, false);    // Front left stopped
            motor_control_back_left(0, false);     // Back left stopped
            // Right side motors full speed
            motor_control_front_right(255, false); // Front right full speed
            motor_control_back_right(255, false);  // Back right full speed
            break;
            
        case CMD_RIGHT:
            // Right side motors slow/stopped
            motor_control_front_right(0, false);   // Front right stopped
            motor_control_back_right(0, false);    // Back right stopped
            // Left side motors full speed
            motor_control_front_left(255, false);  // Front left full speed
            motor_control_back_left(255, false);   // Back left full speed
            break;
            
        case CMD_STOP:
            motor_control_front_left(0, true);
            motor_control_front_right(0, true);
            motor_control_back_left(0, true);
            motor_control_back_right(0, true);
            break;
    }
}