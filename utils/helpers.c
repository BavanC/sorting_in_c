#include <helpers.h>

int dump_integer_array_contents(int *intlist, long array_size)
{
    int i = 0;
    do {
        printf("%d, ", intlist[i]);
        i++;
    } while (i < array_size - 1);
    printf("%d\n", intlist[i]);

    return 0;
}
