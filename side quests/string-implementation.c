#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t len;
} str;

/*
 * What functions are needed
 *
 * 1. create -> empty, using char*
 * string string_create_empty(void)
 * string string_create_char(char *s)
 *
 * -> create a string object, that will live on stack
 * -> the char array will live on heap
 *
 *
 * 2. destroy
 * void string_destroy(string* s)
 * -> free the memory on the heap
 *
 * 3. length
 * size_t string_length(string s)
 * -> return length of the string
 *
 * 4. data
 * char *string_char(string s)
 * -> return char array
 *
 * 5. copy
 * string string_copy(string s)
 * -> create a deep copy, allocate new memory on the heap and copy elements
 * there
 *
 * 6. compare
 * string string_compare(string s, string t)
 * -> compare two strings, same as strcmp
 *
 * 7. append string
 * string string_append_string(string s, string t)
 * -> add two strings and return a new string
 *
 * 8. append c_string
 * string string_append_char(string s, char *t)
 * -> create new string with s + t
 *
 *
 */

/*
 * Final set of APIs
 */

str str_new(void);
str str_from(const char *cstr);
void str_drop(str *s);

size_t str_len(str s);
const char *str_cstr(str s);

str str_copy(str s);
int str_cmp(str a, str b);

str str_cat(str a, str b);
str str_ccat(str a, const char *cstr);

int str_eq(str a, str b);

int main() {
  str a = str_new();
  printf("Hellow %s", str_cstr(a));

  return 0;
}

str str_new(void) {
  // create a new empty str with void
  return (str){.data = strdup(""), .len = 0};
}

str str_from(const char *cstr) {
  if (cstr == NULL) {
    return str_new();
  }
  return (str){.len = strlen(cstr), .data = strdup(cstr)};
}

void str_drop(str *s) {
  if (s->data) {
    free(s->data);
    s->data = NULL;
  }
  s->len = 0;
}

size_t str_len(str s) { return s.len; }

const char *str_cstr(str s) {
    return s.data;
}

str str_copy(str s) { return str_from(s.data); }

int str_cmp(str a, str b) { return strcmp(a.data, b.data); }

int str_eq(str a, str b) { return (str_cmp(a, b) == 0); }

str str_cat(str a, str b) {
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

str str_ccat(str a, const char *cstr) {
  if (cstr == NULL) {
      return str_copy(a);
  }

  size_t ll = a.len + strlen(cstr);

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
