#include <stdio.h>

#define LIST_SIZE 10001

int ascii_to_positive_int(char *raw_int) {
    int result = 0;
    int temp_result;
    char *cursor = raw_int;

    while (*cursor >= '0' && *cursor <= '9') {
        temp_result = result * 10 + *cursor - '0';
        if (temp_result < result) {
            return -1;
        }
        result = temp_result;
        cursor++;
    }

    return result;
}

int read_file_into_array(FILE* fptr, int* intlist_cursor) {
    char buf[100];

    while (fgets(buf, sizeof(buf), fptr) != NULL){
        if (ascii_to_positive_int(buf) == -1) {
            printf("Integer overflow!\n");
        }
        else {
            *intlist_cursor = ascii_to_positive_int(buf);
            intlist_cursor++;
        }
    }
    
    rewind(fptr);
    return 0;
}

int dump_integer_array_contents (int* intlist) {
    int i = 0;
    do {
        printf("%d, ", intlist[i]);
        i++;
    } while (i < LIST_SIZE - 1);
    printf("%d\n", intlist[i]);

    return 0;
}

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