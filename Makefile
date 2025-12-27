CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -pedantic
DEBUGFLAGS = -g -O0

all: bubble merge

# Build bubblesort
bubblesort/bubblesort: bubblesort/bubblesort.c sort_utils.c sort_utils.h
	$(CC) $(CFLAGS) bubblesort/bubblesort.c sort_utils.c -o bubblesort/bubblesort

# Alias for building
bubble: bubblesort/bubblesort

# Build and run bubblesort
run-bubble: bubblesort/bubblesort
	./bubblesort/bubblesort

# Build mergesort
mergesort/mergesort: mergesort/mergesort.c sort_utils.c sort_utils.h
	$(CC) $(CFLAGS) mergesort/mergesort.c sort_utils.c -o mergesort/mergesort

# Alias for building
merge: mergesort/mergesort

# Build and run mergesort
run-merge: mergesort/mergesort
	./mergesort/mergesort

# Debug builds with debug symbols
debug-bubble: bubblesort/bubblesort.c sort_utils.c sort_utils.h
	$(CC) $(CFLAGS) $(DEBUGFLAGS) bubblesort/bubblesort.c sort_utils.c -o bubblesort/bubblesort

debug-merge: mergesort/mergesort.c sort_utils.c sort_utils.h
	$(CC) $(CFLAGS) $(DEBUGFLAGS) mergesort/mergesort.c sort_utils.c -o mergesort/mergesort

# Clean all built files
clean:
	rm -f bubblesort/bubblesort mergesort/mergesort

.PHONY: all bubble run-bubble merge run-merge debug-bubble debug-merge clean