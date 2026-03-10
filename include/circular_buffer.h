#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#define BUF_SIZE 8

typedef struct {
    float val;
    int validity;
} Node;

typedef struct {
    Node data[BUF_SIZE];
    int nextWrite;
    float average;
    int nValid;

} CircularBuffer;

void cb_write(CircularBuffer* buf, float value, int valid);
void cb_init(CircularBuffer* buf);




#endif
