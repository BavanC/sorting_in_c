#ifndef HELPERS_H
#define HELPERS_H

#include <arraycursor.h>
#include <fileread.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int dump_integer_array_contents(int* intlist, long array_size);

#endif
