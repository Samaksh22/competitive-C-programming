#pragma once

// -----------------------------
// Dependencies
// -----------------------------

#include <stddef.h>
#include <stdlib.h>

// -----------------------------
// variables
// -----------------------------

typedef struct {
    char *data;
    size_t len;
} str;

// -----------------------------
// Functions
// -----------------------------

static inline size_t _cstr_len(const char *cstr) {
    if (cstr == NULL) {
        return 0;
    }

    size_t i = 0;
    while (cstr[i]) {
        i++;
    }
    return i;
}

static inline char *_cstr_dup(const char *cstr) {
    if (!cstr) {
        return NULL;
    }

    size_t n = _cstr_len(cstr);
    char *mem = malloc(sizeof(char) * (n + 1));
    if (!mem) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        mem[i] = cstr[i];
    }
    mem[n] = 0;

    return mem;
}

static inline str str_new(void) {
    return (str){.data = _cstr_dup(""), .len = 0};
}

static inline str str_from(const char *cstr) {
    if (cstr == NULL) {
        return str_new();
    }
    return (str){.len = _cstr_len(cstr), .data = _cstr_dup(cstr)};
}

static inline void str_drop(str *s) {
    if (s->data) {
        free(s->data);
        s->data = NULL;
    }
    s->len = 0;
}

static inline size_t str_len(str s) {
    return s.len;
}

static inline const char *str_cstr(str s) {
    return s.data;
}

static inline str str_copy(str s) {
    return str_from(s.data);
}

static inline int str_cmp(str a, str b) {
    char *aa = a.data;
    char *bb = b.data;

    while (*aa && *bb && *aa == *bb) {
        aa++;
        bb++;
    }

    return *aa - *bb;
}

static inline int str_eq(str a, str b) {
    return (str_cmp(a, b) == 0);
}

static inline str str_cat(str a, str b) {
    size_t ll = a.len + b.len;
    char *d = malloc(sizeof(char) * (ll + 1));

    if (d == NULL) {
        return str_new();
    }

    for (size_t i = 0; i < a.len; i++) {
        d[i] = a.data[i];
    }
    for (size_t i = a.len; i < ll; i++) {
        d[i] = b.data[i - a.len];
    }
    d[ll] = 0;

    return (str){d, ll};
}

static inline str str_ccat(str a, const char *cstr) {
    if (cstr == NULL) {
        return str_copy(a);
    }

    size_t ll = a.len + _cstr_len(cstr);

    char *d = malloc(sizeof(char) * (ll + 1));

    if (d == NULL) {
        return str_new();
    }

    for (size_t i = 0; i < a.len; i++) {
        d[i] = a.data[i];
    }
    for (size_t i = a.len; i < ll; i++) {
        d[i] = cstr[i - a.len];
    }
    d[ll] = 0;

    return (str){d, ll};
}
