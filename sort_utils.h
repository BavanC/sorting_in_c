#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <stdio.h>

#define LIST_FILE "v_long_unsorted_numbers.txt"
#define LIST_SIZE 100000

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int ascii_to_positive_int(char *raw_int);
int read_file_into_array(FILE* fptr, int* intlist_cursor);
int dump_integer_array_contents(int* intlist, long array_size);

#endif
