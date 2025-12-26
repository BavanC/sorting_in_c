#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <stdio.h>

int ascii_to_positive_int(char *raw_int);
int read_file_into_array(FILE* fptr, int* intlist_cursor);
int dump_integer_array_contents(int* intlist, long list_size);

#endif
