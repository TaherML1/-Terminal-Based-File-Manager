CC = gcc
CFLAGS = -Wall -g
SRC = main.c file_operations.c directory_ops.c permissions.c logger.c
OBJ = $(SRC:.c=.o)
TARGET = bin/file_manager
LIBS = -lreadline

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
