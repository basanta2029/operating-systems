# Compiler
CC = gcc

# Compiler flags, now with -std=c99 to support C99 standard
CFLAGS = -Wall -g -std=c99

# List of object files
OBJS = list.o main.o

# Name of the output executable
TARGET = list

# Default target
all: $(TARGET)

# Rule to compile the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile list.c into list.o
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

# Rule to compile main.c into main.o
main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

# Clean rule to remove the object files and executable
clean:
	rm -f $(OBJS) $(TARGET)