#ifndef FILEREAD_H
#define FILEREAD_H

#include <stdio.h>
#include <arraycursor.h>

#define LIST_FILE "unsorted_numbers.txt"
#define LIST_SIZE 25

int read_file_into_array(FILE *fptr, ArrayCursor *intlist_cursor);

#endif
