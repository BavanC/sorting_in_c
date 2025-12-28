#include <helpers.h>

int copy_ints_bounded(ArrayCursor *from_cursor_ptr, ArrayCursor *to_cursor_ptr)
{
    int copied_int_count = 0;

    while (is_cursor_within_bounds(from_cursor_ptr) && is_cursor_within_bounds(to_cursor_ptr)) {
        *to_cursor_ptr->position = *from_cursor_ptr->position;
        
        from_cursor_ptr->position++;
        to_cursor_ptr->position++;
        copied_int_count++;
    }

    return copied_int_count;
}


int merge_subarrays(ArrayCursor *source_cursor_ptr, ArrayCursor *buffer_cursor_ptr,
                    size_t block_size, size_t L_subarray_size)
{
    // Left subarray
    int *L_start = source_cursor_ptr->lower_bound;
    ArrayCursor L_subcursor = init_arraycursor(L_start, L_subarray_size, 0);

    // Right subarray, starting after end of the left one, going to the end of the block
    int *R_start = L_start + L_subarray_size;
    size_t R_subarray_size = block_size - L_subarray_size;
    ArrayCursor R_subcursor = init_arraycursor(R_start, R_subarray_size, 0);
    
    ArrayCursor *lower_subcursor_ptr;
    do { // find and copy the lower of the two values into the buffer, then increment cursors
        lower_subcursor_ptr = *L_subcursor.position <= *R_subcursor.position ? &L_subcursor : &R_subcursor;
        *buffer_cursor_ptr->position = *lower_subcursor_ptr->position;

        buffer_cursor_ptr->position++;
        lower_subcursor_ptr->position++;
    } while (is_cursor_within_bounds(buffer_cursor_ptr) && is_cursor_within_bounds(lower_subcursor_ptr));

    // if we've exhausted the array we just copied a value from, dump the other array entirely in order
    ArrayCursor *upper_subcursor_ptr = lower_subcursor_ptr == &L_subcursor ? &R_subcursor : &L_subcursor;
    copy_ints_bounded(upper_subcursor_ptr, buffer_cursor_ptr);
    return 0;
}


int mergesort_blocks(ArrayCursor *sorted_cursor, int *buffer_start_ptr, 
                     size_t block_size, size_t subarray_size)
{
    if (block_size == 1) return 0;

    ArrayCursor block_cursor, buffer_cursor;
    
    while (is_cursor_within_bounds(sorted_cursor)) {
        // if we are in the final block, it might not actually fill the space we expect
        // since this can only happen on the final loop, we can change block_size itself
        block_size = MIN(block_size, (size_t)(sorted_cursor->upper_bound - sorted_cursor->position + 1));
        block_cursor = init_arraycursor(sorted_cursor->position, block_size, 0);
        buffer_cursor = init_arraycursor(buffer_start_ptr, block_size, 0);
        
        // merge the left and right subarrays of the block if they both have valid values then
        // copy numbers from the buffer back into the sorted array, error if counts dont match
        if (block_size > subarray_size) {
            merge_subarrays(&block_cursor, &buffer_cursor, block_size, subarray_size);
            reset_array_cursor(&buffer_cursor);
        } else {
            if (copy_ints_bounded(&block_cursor, &buffer_cursor) != (int)block_size) goto exit_on_error;
            reset_array_cursor(&block_cursor);
            reset_array_cursor(&buffer_cursor);
        }
        if (copy_ints_bounded(&buffer_cursor, &block_cursor) != (int)block_size) goto exit_on_error;
        
        // the while loop overshoot means we can actually take the position of the block cursor directly
        sorted_cursor->position = block_cursor.position;
    }
    return 0;

    exit_on_error:
        printf("mergesort_blocks errored\n");
        dump_integer_array_contents(buffer_cursor.lower_bound, block_size);
        dump_integer_array_contents(block_cursor.lower_bound, block_size);
        return 1; // this is caught and routed to the main functions error dump too
}


int main()
{
    char *unsorted_numbers_filename = LIST_FILE;
    FILE *fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("File does not exist\n");
        return 1;
    }

    int integer_list[LIST_SIZE];
    ArrayCursor sorted_cursor = init_arraycursor(integer_list, LIST_SIZE, 0);
    
    read_file_into_array(fptr, &sorted_cursor);
    printf("unsorted array:\n");
    dump_integer_array_contents(integer_list, LIST_SIZE);

    size_t block_size, subarray_size;
    int holding_buffer[LIST_SIZE];
    
    for (block_size = 1; block_size <= LIST_SIZE; block_size = block_size * 2) {
        // the function does nothing and exits on the first loop due to block_size = 1
        // which then allows subarray size to always be set to the previous block size
        if (mergesort_blocks(&sorted_cursor, holding_buffer, block_size, subarray_size)) goto exit_on_error;
        
        reset_array_cursor(&sorted_cursor);
        subarray_size = block_size;
    }
    if (block_size > LIST_SIZE) { // handling the final merge if needed
        size_t final_block_size = block_size / 2;
        ArrayCursor buffer_cursor = init_arraycursor(holding_buffer, LIST_SIZE, 0);
        
        // both subarrays are ordered already, so its just one final merge with asymmetrically sized blocks
        // since its still a bisection, we only need to pass the size of one block
        merge_subarrays(&sorted_cursor, &buffer_cursor, LIST_SIZE, final_block_size);
        reset_array_cursor(&buffer_cursor);
        if (copy_ints_bounded(&buffer_cursor, &sorted_cursor) != LIST_SIZE) goto full_buffer_dump;
    }

    printf("final sorted list:\n");
    dump_integer_array_contents(integer_list, LIST_SIZE);
    return 0;


    // error dumping
    full_buffer_dump:
        printf("final merge error\n");
        dump_integer_array_contents(holding_buffer, LIST_SIZE);
    exit_on_error:
        dump_integer_array_contents(integer_list, LIST_SIZE);
        return 1;
}