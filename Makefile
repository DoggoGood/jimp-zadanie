CC = gcc
CFLAGS = -Wall -Wextra
TARGET = indx
OBJS = indx.o vector.o skorowidz.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

indx.o: indx.c vector.h skorowidz.h
	$(CC) $(CFLAGS) -c indx.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

skorowidz.o: skorowidz.c skorowidz.h vector.h
	$(CC) $(CFLAGS) -c skorowidz.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
