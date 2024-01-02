# Compiler settings
CC = gcc
CFLAGS = -Wall -Icmath/include -g

# Linker settings
LDFLAGS = -lm

# Project files
SRC_DIR = cmath/src
SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(SRCS:%.c=%.o)
TARGET = test

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

leak:
	valgrind --leak-check=full --show-leak-kinds=all ./test

