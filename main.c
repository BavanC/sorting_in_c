#include <helpers.h>
#include <bubblesort.h>
#include <mergesort.h>
#include <string.h>

int main()
{
    char *unsorted_numbers_filename = LIST_FILE;
    FILE *fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("File does not exist: %s\n", unsorted_numbers_filename);
        return 1;
    }

    int integer_list[LIST_SIZE];
    ArrayCursor list_cursor = init_arraycursor(integer_list, LIST_SIZE, 0);

    read_file_into_array(fptr, &list_cursor);
    fclose(fptr);

    printf("Select sorting algorithm ([b]ubblesort/[m]ergesort): ");
    char algorithm;
    if (scanf(" %c", &algorithm) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    unsigned long long operation_count = 0;
    int holding_buffer[LIST_SIZE];

    switch (algorithm) {
        case 'b':
            bubblesort(integer_list, LIST_SIZE, &operation_count);
            break;
        case 'm':
            mergesort(integer_list, LIST_SIZE, holding_buffer, &operation_count);
            break;
        default:
            printf("Unknown algorithm: %c\n", algorithm);
            printf("Please use 'b' or 'm'\n");
            return 1;
    }

    printf("number of operations: %llu\n", operation_count);
    // printf("sorted array:\n");
    // dump_integer_array_contents(integer_list, LIST_SIZE);

    return 0;
}