#ifndef SENSOR_H
#define SENSOR_H


typedef struct {
    float value;
    int isValid;
} SensorReading;


SensorReading read_temperature(void);


#endif