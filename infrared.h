#include <stdbool.h>
#ifndef INFRARED_SENSOR_PORT
#define INFRARED_SENSOR_PORT 16

void init_infrared_sensor();
bool get_infrared_reading();
#endif      