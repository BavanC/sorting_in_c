#include "../sort_utils.h"

int main() {
    FILE* fptr;
    char* unsorted_numbers_filename = LIST_FILE;
    int unsorted_ints[LIST_SIZE];
    int sorted_ints[LIST_SIZE];
    
    fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("file does not exist\n");
        return 1;
    }

    read_file_into_array(fptr, unsorted_ints);
    read_file_into_array(fptr, sorted_ints);
    // dump_integer_array_contents(unsorted_ints);

    int* intlist_cursor = sorted_ints;
    int sorted_so_far = 0;
    int left_val, right_val;
    long comparison_count = 0;
    while (sorted_so_far < LIST_SIZE) {
        if (intlist_cursor + 1 == sorted_ints + LIST_SIZE) {
            sorted_so_far++;
            intlist_cursor = sorted_ints;
            continue;
        }
        comparison_count++;
        
        left_val = *intlist_cursor;
        right_val = *(intlist_cursor + 1);
        if (left_val > right_val) {
            *intlist_cursor = right_val;
            *(intlist_cursor + 1) = left_val;
        }
        
        if ((intlist_cursor - sorted_ints) == (LIST_SIZE - sorted_so_far - 1)) {
            sorted_so_far++;
            intlist_cursor = sorted_ints;
        } else {
            intlist_cursor++;
        }
    }

    // dump_integer_array_contents(sorted_ints);
    printf("number of comparisons: %ld\n", comparison_count);

    return 0;
}