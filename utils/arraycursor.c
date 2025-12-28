#include <arraycursor.h>

ArrayCursor init_arraycursor(int *array_start_ptr, size_t array_size, int starting_cursor_offset)
{
    return (ArrayCursor){
        array_start_ptr,
        array_start_ptr + array_size - 1,
        array_start_ptr + starting_cursor_offset
    };
}


int is_cursor_within_bounds(ArrayCursor *ac_ptr)
{
    return (
        ac_ptr->position >= ac_ptr->lower_bound && 
        ac_ptr->position <= ac_ptr->upper_bound
    );
}


int reset_array_cursor(ArrayCursor *ac_ptr)
{
    ac_ptr->position = ac_ptr->lower_bound;
    return 0;
}
