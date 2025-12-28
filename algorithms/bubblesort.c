#include <helpers.h>

unsigned long long operation_count = 0;

int main() 
{
    char *unsorted_numbers_filename = LIST_FILE;
    FILE *fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("file does not exist\n");
        return 1;
    }

    int integer_list[LIST_SIZE];
    ArrayCursor sorting_cursor = init_arraycursor(integer_list, LIST_SIZE, 0);

    read_file_into_array(fptr, &sorting_cursor);
    // printf("unsorted array:\n");
    // dump_integer_array_contents(integer_list, LIST_SIZE);

    int left_val, right_val;
    while (sorting_cursor.upper_bound > sorting_cursor.lower_bound) {      
        left_val = *sorting_cursor.position;
        right_val = *(sorting_cursor.position + 1);

        if (left_val > right_val) {
            *sorting_cursor.position = right_val;
            *(sorting_cursor.position + 1) = left_val;
            operation_count++; // swap
        }
        operation_count++; // comparison
        sorting_cursor.position++;
        
        // if we reach the end of the list, the final value is now locked in
        // and we reduce the sorting cursor's window, reset it, and restart the loop
        if (sorting_cursor.position == sorting_cursor.upper_bound) {
            sorting_cursor.upper_bound--;
            reset_array_cursor(&sorting_cursor);
        }
    }

    printf("number of operations: %llu\n", operation_count);
    // printf("sorted array:\n");
    // dump_integer_array_contents(integer_list, LIST_SIZE);
    return 0;
}
