#include "../sort_utils.h"
#define LIST_SIZE 25

int main() {
    FILE* fptr;
    char* unsorted_numbers_filename = "unsorted_numbers.txt";
    int unsorted_ints[LIST_SIZE];
    int sorted_ints[LIST_SIZE];
    
    fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("file does not exist\n");
        return 1;
    }

    read_file_into_array(fptr, unsorted_ints);
    read_file_into_array(fptr, sorted_ints);
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

    dump_integer_array_contents(sorted_ints, LIST_SIZE);

    return 0;
}