#include "../sort_utils.h"

#define LIST_SIZE 25


int main() {
    FILE* fptr;
    char* unsorted_numbers_filename = "unsorted_numbers.txt";
    int unsorted_ints[LIST_SIZE];
    int sorted_ints[LIST_SIZE];
    int holding_ints[LIST_SIZE];
    size_t array_index;
    for (array_index = 0; array_index < LIST_SIZE; array_index++) {
        holding_ints[array_index] = 0;
    }
    
    fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("file does not exist\n");
        return 1;
    }

    read_file_into_array(fptr, unsorted_ints);
    read_file_into_array(fptr, sorted_ints);
    printf("unsorted array: \n");
    dump_integer_array_contents(unsorted_ints, LIST_SIZE);

    int* intlist_cursor = sorted_ints;
    int left_val, right_val;
    long comparison_count = 0;
    while (intlist_cursor < sorted_ints + LIST_SIZE - 1) {
        left_val = *intlist_cursor;
        right_val = *(intlist_cursor + 1);
        if (left_val > right_val) {
            *intlist_cursor = right_val;
            *(intlist_cursor + 1) = left_val;
        }
        
        comparison_count++;
        intlist_cursor = intlist_cursor + 2;
    }

    printf("first level sorting: \n");
    dump_integer_array_contents(sorted_ints, LIST_SIZE);

    size_t subarray_size = 2;
    intlist_cursor = sorted_ints;
    int* holding_cursor = holding_ints;
    int* left_subarray_cursor;
    int* right_subarray_cursor;

    while (intlist_cursor < sorted_ints + LIST_SIZE - 1) {
        printf("block to sort: \n");
        dump_integer_array_contents(intlist_cursor, subarray_size * 2);
        
        left_subarray_cursor = intlist_cursor;
        right_subarray_cursor = intlist_cursor + subarray_size;

        while (holding_cursor < holding_ints + subarray_size * 2) {
            left_val = *left_subarray_cursor;
            right_val = *right_subarray_cursor;

            if (left_val <= right_val) {
                *holding_cursor = left_val;
                left_subarray_cursor++;
            } else {
                *holding_cursor = right_val;
                right_subarray_cursor++;
            }
            holding_cursor++;

            dump_integer_array_contents(holding_ints, 2 * subarray_size);
            if (left_subarray_cursor >= intlist_cursor + subarray_size) {
                while (right_subarray_cursor < intlist_cursor + 2 * subarray_size) {
                    *holding_cursor = *right_subarray_cursor;
                    right_subarray_cursor++;
                    holding_cursor++;
                }
                dump_integer_array_contents(holding_ints, 2 * subarray_size);
            } else if (right_subarray_cursor >= intlist_cursor + 2 * subarray_size) {
                while (left_subarray_cursor < intlist_cursor + subarray_size) {
                    *holding_cursor = *left_subarray_cursor;
                    left_subarray_cursor++;
                    holding_cursor++;
                }
                dump_integer_array_contents(holding_ints, 2 * subarray_size);
            }
        }

        for (array_index = 0; array_index < 2 * subarray_size; array_index++) {
            *(intlist_cursor + array_index) = holding_ints[array_index];
        }
        intlist_cursor = intlist_cursor + 2 * subarray_size;
        holding_cursor = holding_ints;
        dump_integer_array_contents(sorted_ints, LIST_SIZE);
    }
    dump_integer_array_contents(sorted_ints, LIST_SIZE);

    return 0;
}