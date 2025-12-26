#include "sort_utils.h"

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

int dump_integer_array_contents (int* intlist, long list_size) {
    int i = 0;
    do {
        printf("%d, ", intlist[i]);
        i++;
    } while (i < list_size - 1);
    printf("%d\n", intlist[i]);

    return 0;
}
