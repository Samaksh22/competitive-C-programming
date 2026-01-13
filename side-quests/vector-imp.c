#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    size_t len;
    size_t cap;
}vec;

/*
 * Extensible array that allows append, insert, search, delete, sort
 *
 *
 * -- LIFECYCLE --
 * 1. vec_init
 * -> for empty vectors init
 *
 * 2. vec_with_cap
 * -> with given capacity
 *
 * 3. vec_drop
 * -> free all the allocated memory and NULL the pointer
 *
 * 4. vec_clear
 * -> reset length to zero and capacity the same
 *
 *
 *
 * -- SIZE --
 * 5. vec_len
 * -> # of elems
 *
 * 6. vec_cap
 * -> curr capacity
 *
 * 7. vec_empty
 * -> if length is zero?
 *
 *
 *
 * -- ELEMENT ACCESS --
 * no check if index is in bounds
 *
 * 8. vec_get
 * -> get elem at index
 *
 * 9. vec_set
 * -> set elem at index
 *
 * 10. vec_front
 * -> first elem
 *
 * 11. vec_back
 * -> last elem
 *
 *
 * -- MUTATION --
 * 12. vec_push
 * -> append to end
 *
 * 13. vec_pop
 * -> remove and return last elem
 *
 * 14. vec_insert
 * -> insert at some index (maximum at the end)
 *
 * 15. vec_erase
 * -> remove elem at index
 *
 * -- MISC --
 * 16. vec_find
 * -> find elem in array
 *
 * 17. vec_sort
 *
 * 18. vec_reserve
 *
 * 19. vec_shrink
 *
 * 20. vec_copy
 *
 */

int main()
{
    printf("hellow");

    return 0;
}
