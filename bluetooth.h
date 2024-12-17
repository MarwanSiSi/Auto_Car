// bluetooth.h
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdbool.h>
#include "pico/stdlib.h"

// Define UART configuration
#define BLUETOOTH_UART uart1
#define BLUETOOTH_BAUD_RATE 9600
#define BLUETOOTH_TX_PIN 4
#define BLUETOOTH_RX_PIN 5

// Command definitions
#define CMD_FORWARD 'f'
#define CMD_BACKWARD 'b'
#define CMD_LEFT 'l'
#define CMD_RIGHT 'r'
#define CMD_STOP 's'
#define CMD_GET_SENSORS 'g'

// Function declarations
void init_bluetooth(void);
void bluetooth_send_sensor_data(int speed);
void process_bluetooth_command(char cmd);
bool bluetooth_has_data(void);
char bluetooth_read_char(void);
void bluetooth_send_message(const char* message);

#endif // BLUETOOTH_H