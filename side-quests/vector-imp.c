#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/*
 * Extensible array that allows append, insert, search, delete, sort
 *
 *
 *   typedef struct {
 *       int *arr;
 *       size_t len;
 *       size_t cap;
 *   } vec_int;
 *
 *
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

typedef struct {
    int *arr;
    size_t len;
    size_t cap;
} vec_int;

// --- UTILS ---
size_t next_pow_2(size_t n) {
    if (n == 0) {
        return 0;
    }

    size_t x = 1;
    while (x < n && x < (x << 1)) {
        x <<= 1;
    }

    if (x < n) {
        return 0;
    }

    return x;
}

// --- LIFECYCLE ---
vec_int vec_init() {
    return (vec_int){.arr = NULL, .len = 0, .cap = 0};
}

vec_int vec_with_cap(size_t cap) {
    cap = next_pow_2(cap);
    if (cap == 0) {
        return vec_init();
    }

    int *arr = malloc(sizeof(int) * cap);
    if (arr == NULL) {
        return vec_init();
    }

    return (vec_int){.arr = arr, .len = 0, .cap = cap};
}

void vec_drop(vec_int *v) {
    if (v->arr) {
        free(v->arr);
    }
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void vec_clear(vec_int *v) {
    v->len = 0;
}

// --- SIZE ---
size_t vec_len(vec_int v) {
    return v.len;
}

size_t vec_cap(vec_int v) {
    return v.cap;
}

int vec_empty(vec_int v) {
    return v.len == 0;
}

int main() {
    printf("hellow");

    return 0;
}
