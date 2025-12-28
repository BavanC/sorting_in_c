#ifndef ARRAYCURSOR_H
#define ARRAYCURSOR_H

#include <stdio.h>

typedef struct ArrayCursor
{
    int *lower_bound;
    int *upper_bound;
    int *position;
} ArrayCursor;

ArrayCursor init_arraycursor(int *array_start_ptr, size_t array_size, int starting_cursor_offset);
int is_cursor_within_bounds(ArrayCursor *ac_ptr);
int reset_array_cursor(ArrayCursor *ac_ptr);

#endif