CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -pedantic
DEBUGFLAGS = -g -O0

all: bubble

# Build bubblesort
bubblesort/bubblesort: bubblesort/bubblesort.c
	$(CC) $(CFLAGS) bubblesort/bubblesort.c -o bubblesort/bubblesort

# Alias for building
bubble: bubblesort/bubblesort

# Build and run bubblesort
run-bubble: bubblesort/bubblesort
	./bubblesort/bubblesort

# Clean all built files
clean:
	rm -f bubblesort/bubblesort

.PHONY: all bubble run-bubble clean