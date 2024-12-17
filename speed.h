
#define SPEED_SENSOR_PORT_PIN1 2
#define SPEED_SENSOR_PORT_PIN2 3
#define PULSES_PER_REVOLUTION 20  

extern volatile int pulse_count;

void init_speed_sensor();
int calculate_motor_speed();
