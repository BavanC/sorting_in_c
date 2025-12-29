INCLUDE_DIR = include
UTILS_SRC = $(wildcard utils/*.c)
UTILS_OBJ = $(UTILS_SRC:.c=.o)

CC = gcc
CFLAGS = -std=c17 -I$(INCLUDE_DIR) -Wall -Wextra -pedantic -MMD -MP
DEBUGFLAGS = -g -O0

all: sorting_algorithms

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

sorting_algorithms: main.o algorithms/bubblesort.o algorithms/mergesort.o $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

run: sorting_algorithms
	./sorting_algorithms

debug: CFLAGS += $(DEBUGFLAGS)
debug: sorting_algorithms

clean:
	rm -f sorting_algorithms
	rm -f main.o main.d
	rm -f algorithms/*.o algorithms/*.d
	rm -f utils/*.o utils/*.d

-include $(wildcard */*.d)

.PHONY: all run debug clean
