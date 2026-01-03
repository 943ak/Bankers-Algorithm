CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = P2

all: $(TARGET)

$(TARGET): P2.c
	$(CC) $(CFLAGS) P2.c -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
