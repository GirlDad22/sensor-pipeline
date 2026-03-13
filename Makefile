CC = gcc
CFLAGS = -Wall -I include

src/sensor.o: src/sensor.c include/sensor.h
	$(CC) $(CFLAGS) -c src/sensor.c -o src/sensor.o

src/circular_buffer.o: src/circular_buffer.c include/circular_buffer.h
	$(CC) $(CFLAGS) -c src/circular_buffer.c -o src/circular_buffer.o

src/main.o: src/main.c include/sensor.h include/circular_buffer.h include/config.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

sensor_pipeline: src/sensor.o src/circular_buffer.o src/main.o
	$(CC) src/sensor.o src/circular_buffer.o src/main.o -o sensor_pipeline

clean:
	rm -f src/*.o sensor_pipeline

