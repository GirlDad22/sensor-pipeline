#include "../include/sensor.h"
#include "../include/circular_buffer.h"
#include "../include/config.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

typedef enum {
    STATE_NORMAL,
    STATE_WARNING,
    STATE_CRITICAL
} SystemState;


int main() {

    srand(time(NULL));

    CircularBuffer buf;
    cb_init(&buf);
    SensorReading data;
    SystemState state;

    while(1) {
        // main read and log loop

        data = read_temperature();
        cb_write(&buf, data.value, data.isValid);

        if(buf.average > CRITICAL_HIGH || buf.average < CRITICAL_LOW) state = STATE_CRITICAL;
        else if(buf.average > WARNING_HIGH || buf.average < WARNING_LOW) state = STATE_WARNING;
        else state = STATE_NORMAL;

        switch(state) {

            case STATE_CRITICAL: printf("***CRITICAL***: CURRENT AVERAGE TEMPERATURE IS %.1f\n", buf.average); break;
            case STATE_WARNING: printf("**WARNING**: CURRENT AVERAGE TEMPERATURE IS %.1f\n", buf.average); break;
            case STATE_NORMAL: printf("CURRENT AVERAGE TEMPERATURE IS %.1f\n", buf.average); break;
        }

        sleep(1);
    }

    return 0;
}



