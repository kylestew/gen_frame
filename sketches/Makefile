CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

TARGET = image_generator
SOURCES = main.c sketches/sketch.c
OBJECTS = main.o sketches/sketch.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

sketches/sketch.o: sketches/sketch.c
	$(CC) $(CFLAGS) -c sketches/sketch.c -o sketches/sketch.o

clean:
	rm -f $(OBJECTS) $(TARGET) output.ppm

run: $(TARGET)
	./$(TARGET) 