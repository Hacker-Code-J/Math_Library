# Compiler settings
CC = gcc
CFLAGS = -Wall -Icmath/include

# Project files
SRC_DIR = cmath/src
SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(SRCS:%.c=%.o)
TARGET = test

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all