#include "../sort_utils.h"

struct ArrayCursor {
    int* lower_bound;
    int* upper_bound;
    int* position;
};


struct ArrayCursor init_arraycursor(
    int* array_start_ptr, 
    size_t array_size, 
    int starting_cursor_offset
) {
    return (struct ArrayCursor) {
        array_start_ptr,
        array_start_ptr + array_size - 1,
        array_start_ptr + starting_cursor_offset
    };
}


int reset_array_cursor(struct ArrayCursor* ac_ptr) {
    ac_ptr->position = ac_ptr->lower_bound;
    return 0;
}


int is_cursor_within_bounds(struct ArrayCursor* ac_ptr) {
    return (
        ac_ptr->position >= ac_ptr->lower_bound && 
        ac_ptr->position <= ac_ptr->upper_bound
    );
}


int min(size_t a, size_t b) {
    return a < b ? a : b;
}


int copy_ints_to_array(
    struct ArrayCursor* from_cursor_ptr,
    struct ArrayCursor* to_cursor_ptr
) {
    int copied_int_count = 0;

    while (is_cursor_within_bounds(from_cursor_ptr) && is_cursor_within_bounds(to_cursor_ptr)) {
        *to_cursor_ptr->position = *from_cursor_ptr->position;
        
        from_cursor_ptr->position++;
        to_cursor_ptr->position++;
        copied_int_count++;
    }

    return copied_int_count;
}


int merge_subarrays(
    struct ArrayCursor *source_cursor_ptr,
    struct ArrayCursor *buffer_cursor_ptr,
    size_t block_size,
    size_t left_subarray_size
) {
    int* left_start = source_cursor_ptr->lower_bound;
    int* right_start = left_start + left_subarray_size;
    size_t right_subarray_size = block_size - left_subarray_size;

    struct ArrayCursor left_subcursor = init_arraycursor(left_start, left_subarray_size, 0);
    struct ArrayCursor right_subcursor = init_arraycursor(right_start, right_subarray_size, 0);

    while (is_cursor_within_bounds(buffer_cursor_ptr)) {
        if (*left_subcursor.position <= *right_subcursor.position) {
            *buffer_cursor_ptr->position = *left_subcursor.position;
            left_subcursor.position++;
        } else {
            *buffer_cursor_ptr->position = *right_subcursor.position;
            right_subcursor.position++;
        }
        buffer_cursor_ptr->position++;

        if (!is_cursor_within_bounds(&left_subcursor)) {
            copy_ints_to_array(&right_subcursor, buffer_cursor_ptr);
        } else if (!is_cursor_within_bounds(&right_subcursor)) {
            copy_ints_to_array(&left_subcursor, buffer_cursor_ptr);
        }
    }

    return 0;
}


int mergesort_blocks(
    struct ArrayCursor *sorted_cursor,
    size_t block_size,
    size_t subarray_size,
    int* buffer_start_ptr
) {
    if (block_size == 1) return 0;

    struct ArrayCursor block_cursor, buffer_cursor;
    
    while (is_cursor_within_bounds(sorted_cursor)) {
        // if we are in the final block, it might not actually fill the space we expect
        // since this can only happen on the final loop, we can change block_size itself
        block_size = min(block_size, sorted_cursor->upper_bound - sorted_cursor->position + 1);
        block_cursor = init_arraycursor(sorted_cursor->position, block_size, 0);
        buffer_cursor = init_arraycursor(buffer_start_ptr, block_size, 0);
        
        // merge the left and right subarrays of the block if they both have valid values then
        // copy numbers from the buffer back into the sorted array, error if counts dont match
        if (block_size > subarray_size) {
            merge_subarrays(&block_cursor, &buffer_cursor, block_size, subarray_size);
            reset_array_cursor(&buffer_cursor);
        } else {
            if (copy_ints_to_array(&block_cursor, &buffer_cursor) != (int)block_size) goto exit_on_error;
            reset_array_cursor(&block_cursor);
            reset_array_cursor(&buffer_cursor);
        }
        if (copy_ints_to_array(&buffer_cursor, &block_cursor) != (int)block_size) goto exit_on_error;
        
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


int main() {
    char* unsorted_numbers_filename = LIST_FILE;
    FILE* fptr = fopen(unsorted_numbers_filename, "r");
    if (fptr == NULL) {
        printf("File does not exist\n");
        return 1;
    }

    int integer_list[LIST_SIZE];
    read_file_into_array(fptr, integer_list);
    printf("unsorted array:\n");
    dump_integer_array_contents(integer_list, LIST_SIZE);

    struct ArrayCursor sorted_cursor = init_arraycursor(integer_list, LIST_SIZE, 0);
    size_t block_size, subarray_size;
    int holding_buffer[LIST_SIZE];
    
    for (block_size = 1; block_size <= LIST_SIZE; block_size = block_size * 2) {
        // the function does nothing and exits on the first loop due to block_size = 1
        // which then allows subarray size to always be set to the previous block size
        if (mergesort_blocks(&sorted_cursor, block_size, subarray_size, holding_buffer)) goto exit_on_error;
        
        reset_array_cursor(&sorted_cursor);
        subarray_size = block_size;
    }
    if (block_size > LIST_SIZE) { // handling the final merge if needed
        size_t final_block_size = block_size / 2;
        struct ArrayCursor buffer_cursor = init_arraycursor(holding_buffer, LIST_SIZE, 0);
        
        // both subarrays are ordered already, so its just one final merge with asymmetrically sized blocks
        // since its still a bisection, we only need to pass the size of one block
        merge_subarrays(&sorted_cursor, &buffer_cursor, LIST_SIZE, final_block_size);
        reset_array_cursor(&buffer_cursor);
        if (copy_ints_to_array(&buffer_cursor, &sorted_cursor) != LIST_SIZE) goto full_buffer_dump;
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