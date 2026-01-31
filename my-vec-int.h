#pragma once

// -----------------------------
// Dependencies
// -----------------------------

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------
// variables
// -----------------------------

typedef struct {
    int *arr;
    size_t len;
    size_t cap;
} vec_int;

// -----------------------------
// Functions
// -----------------------------

// --- UTILS ---

static inline size_t _next_pow_2(size_t n) {
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

static inline vec_int vec_init(void) {
    return (vec_int){.arr = NULL, .len = 0, .cap = 0};
}

static inline vec_int vec_with_cap(size_t cap) {
    cap = _next_pow_2(cap);
    if (cap == 0) {
        return vec_init();
    }

    int *arr = malloc(sizeof(int) * cap);
    if (arr == NULL) {
        return vec_init();
    }

    return (vec_int){.arr = arr, .len = 0, .cap = cap};
}

static inline void vec_drop(vec_int *v) {
    if (v->arr) {
        free(v->arr);
    }
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

static inline void vec_clear(vec_int *v) {
    v->len = 0;
}

// --- SIZE ---

static inline size_t vec_len(vec_int v) {
    return v.len;
}

static inline size_t vec_cap(vec_int v) {
    return v.cap;
}

static inline int vec_empty(vec_int v) {
    return v.len == 0;
}

// --- ELEMENT ACCESS ---
// no bounds checks (UB if violated)

static inline int vec_get(vec_int v, size_t idx) {
    return v.arr[idx];
}

static inline void vec_set(vec_int *v, size_t idx, int x) {
    v->arr[idx] = x;
}

static inline int vec_front(vec_int v) {
    return v.arr[0];
}

static inline int vec_back(vec_int v) {
    return v.arr[v.len - 1];
}

// --- CAPACITY OPS ---

static inline int vec_reserve(vec_int *v, size_t n) {
    if (n <= v->cap) {
        return 1;
    }

    size_t new_cap = _next_pow_2(n);
    if (new_cap == 0) {
        return 0;
    }

    int *ptr = realloc(v->arr, new_cap * sizeof(int));
    if (ptr == NULL) {
        return 0;
    }

    v->arr = ptr;
    v->cap = new_cap;
    return 1;
}

static inline int vec_shrink(vec_int *v) {
    if (v->len == 0) {
        vec_drop(v);
        return 1;
    }

    size_t new_cap = _next_pow_2(v->len);
    if (new_cap == 0) {
        return 0;
    }

    int *ptr = realloc(v->arr, new_cap * sizeof(int));
    if (ptr == NULL) {
        return 0;
    }

    v->arr = ptr;
    v->cap = new_cap;
    return 1;
}

static inline vec_int vec_copy(vec_int v) {
    vec_int new_v = {.arr = NULL, .len = v.len, .cap = v.cap};

    if (new_v.cap == 0) {
        return vec_init();
    }

    new_v.arr = malloc(new_v.cap * sizeof(int));
    if (new_v.arr == NULL) {
        return vec_init();
    }

    memcpy(new_v.arr, v.arr, new_v.len * sizeof(int));
    return new_v;
}

// --- MUTATIONS ---

static inline int vec_push(vec_int *v, int x) {
    if (vec_reserve(v, v->len + 1) == 0) {
        return 0;
    }
    v->arr[v->len] = x;
    v->len++;
    return 1;
}

static inline int vec_pop(vec_int *v) {
    v->len--;
    return v->arr[v->len];
}

static inline int vec_insert(vec_int *v, size_t i, int x) {
    if (vec_reserve(v, v->len + 1) == 0) {
        return 0;
    }

    for (size_t j = v->len; j > i; j--) {
        v->arr[j] = v->arr[j - 1];
    }

    v->arr[i] = x;
    v->len++;
    return 1;
}

static inline int vec_erase(vec_int *v, size_t i) {
    int x = v->arr[i];

    for (; i + 1 < v->len; i++) {
        v->arr[i] = v->arr[i + 1];
    }

    v->len--;
    return x;
}

// --- MISC ---

static inline size_t vec_find(vec_int v, int x) {
    size_t idx = 0;
    for (; idx < v.len; idx++) {
        if (v.arr[idx] == x) {
            break;
        }
    }
    return idx;
}

// qsort comparators

static inline int _asc_comp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static inline int _desc_comp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}

static inline void vec_sort(vec_int *v, int ascending) {
    if (ascending) {
        qsort(v->arr, v->len, sizeof(int), _asc_comp);
    } else {
        qsort(v->arr, v->len, sizeof(int), _desc_comp);
    }
}
