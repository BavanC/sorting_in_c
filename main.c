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

    printf("Select sorting algorithm (bubblesort/mergesort): ");
    char algorithm[20];
    if (scanf("%19s", algorithm) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    unsigned long long operation_count = 0;

    if (strcmp(algorithm, "bubblesort") == 0) {
        bubblesort(integer_list, LIST_SIZE, &operation_count);
    } else if (strcmp(algorithm, "mergesort") == 0) {
        int holding_buffer[LIST_SIZE];
        mergesort(integer_list, LIST_SIZE, holding_buffer, &operation_count);
    } else {
        printf("Unknown algorithm: %s\n", algorithm);
        printf("Please use 'bubblesort' or 'mergesort'\n");
        return 1;
    }

    printf("number of operations: %llu\n", operation_count);
    // printf("sorted array:\n");
    // dump_integer_array_contents(integer_list, LIST_SIZE);

    return 0;
}