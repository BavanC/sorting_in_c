INCLUDE_DIR = include
UTILS_SRC = $(wildcard utils/*.c)
UTILS_OBJ = $(UTILS_SRC:.c=.o)

CC = gcc
CFLAGS = -std=c17 -I$(INCLUDE_DIR) -Wall -Wextra -pedantic -MMD -MP
DEBUGFLAGS = -g -O0

all: bubble merge

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

algorithms/bubblesort: algorithms/bubblesort.o $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

algorithms/mergesort: algorithms/mergesort.o $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

bubble: algorithms/bubblesort
merge: algorithms/mergesort

run-bubble: algorithms/bubblesort
	./algorithms/bubblesort

run-merge: algorithms/mergesort
	./algorithms/mergesort

debug-bubble: CFLAGS += $(DEBUGFLAGS)
debug-bubble: algorithms/bubblesort

debug-merge: CFLAGS += $(DEBUGFLAGS)
debug-merge: algorithms/mergesort

clean:
	rm -f algorithms/bubblesort algorithms/mergesort
	rm -f algorithms/*.o algorithms/*.d
	rm -f utils/*.o utils/*.d

-include $(wildcard */*.d)

.PHONY: all bubble run-bubble merge run-merge debug-bubble debug-merge clean
