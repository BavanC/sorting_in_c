#include <fileread.h>

int ascii_to_positive_int(char *raw_int)
{
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

int read_file_into_array(FILE *fptr, ArrayCursor *intlist_cursor)
{
    char buf[100];

    while (fgets(buf, sizeof(buf), fptr) != NULL && is_cursor_within_bounds(intlist_cursor)){
        if (ascii_to_positive_int(buf) == -1) {
            printf("Integer overflow!\n");
        }
        else {
            *intlist_cursor->position = ascii_to_positive_int(buf);
            intlist_cursor->position++;
        }
    }

    rewind(fptr);
    reset_array_cursor(intlist_cursor);
    return 0;
}