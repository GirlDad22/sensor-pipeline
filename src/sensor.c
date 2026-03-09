
#include <stdlib.h>
#include "../include/sensor.h"


SensorReading read_temperature(void) {
    /*
    
    generate a random number for value, and use arithmetic to make it between 32 - 100

    set isValid to true (1) 99.9% of the time, with the other 0.1% being invalid (0)

    */ 

    SensorReading reading;



    reading.value = (rand() % 69) + 32.0f;

    reading.isValid = (rand() % 1000) != 0;

    return reading;
    
}
