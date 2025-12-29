#include <helpers.h>
#include <bubblesort.h>

void bubblesort(int *array, size_t size, unsigned long long *op_count)
{
    ArrayCursor sorting_cursor = init_arraycursor(array, size, 0);

    int left_val, right_val;
    while (sorting_cursor.upper_bound > sorting_cursor.lower_bound) {
        left_val = *sorting_cursor.position;
        right_val = *(sorting_cursor.position + 1);

        if (left_val > right_val) {
            *sorting_cursor.position = right_val;
            *(sorting_cursor.position + 1) = left_val;
            (*op_count)++; // swap
        }
        (*op_count)++; // comparison
        sorting_cursor.position++;

        // if we reach the end of the list, the final value is now locked in
        // and we reduce the sorting cursor's window, reset it, and restart the loop
        if (sorting_cursor.position == sorting_cursor.upper_bound) {
            sorting_cursor.upper_bound--;
            reset_array_cursor(&sorting_cursor);
        }
    }
}
