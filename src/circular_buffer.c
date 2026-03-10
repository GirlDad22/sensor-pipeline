#include "../include/circular_buffer.h"
#include <string.h>


static void setAverage(CircularBuffer* buf, float value, int valid, int idx) {

    // moving average calculation that takes into account validity of current and new reading in data[idx]

    float curValue = buf->data[idx].val;
    int curValidity = buf->data[idx].validity;
    float curSum = buf->average * buf->nValid;
    float newSum;

    /*
    
    dont need to worry about if array is full or not because array is initialized
    with 0's. This means when the array is not full (i.e. in the first BUFSIZE -1) readings
    that the unused array entries wont affect the moving average because they are invalid
    
    */

    if(valid && !curValidity) { // if current slot is NOT valid AND new reading IS
        buf->nValid++;
        newSum = curSum + value;
    }

    else if(valid && curValidity) { // if both ARE valid
        newSum = curSum - curValue + value;
    }

    else { // if current slot IS valid and new reading IS NOT
        newSum = curSum - curValue;
        buf->nValid--;
    }

    buf->average = buf->nValid > 0 ? newSum/buf->nValid : 0.0f;

}

static inline void setNextWrite(CircularBuffer* buf) {

    buf->nextWrite = (buf->nextWrite + 1) % BUF_SIZE;
}

void cb_write(CircularBuffer* buf, float value, int valid) {

    /* write a new reading into the data buffer 
    
    there are 4 cases that need to be considered:

    1: the new reading is valid and the old one is valid
    2: the new reading is valid and the old one is invalid
    3: the new reading is invalid and the old one is invalid
    4: the new reading invalid and the old one is valid
    
    
    */

    int idx = buf->nextWrite;
    int curValid = buf->data[idx].validity;

    if(valid || curValid) setAverage(buf, value, valid, idx); // update avg if either reading is valid

    buf->data[idx].val = value;
    buf->data[idx].validity = valid;
    setNextWrite(buf);

}


void cb_init(CircularBuffer* buf) {

    // initialize all members of buf, to include each node in data array

    buf->nextWrite = 0;
    buf->average = 0;
    buf->nValid = 0;

    memset(buf->data, 0, sizeof(buf->data)); // each node starts of as value = 0 and invalid

}