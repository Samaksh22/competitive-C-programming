#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t length;
  char *data;
} string;

/*
 * What functions are needed
 *
 * 1. create -> empty, using char*
 * 2. destroy
 *
 * 3. length
 * 4. data
 * 
 * 5. copy
 * 6. compare
 * 
 * 7. append string
 * 8. append c_string
 * 
 * 9. clear
 * 
 *
 * string str_init_empty(void);
 *
 * string str_init_char(char *s);
 * 
 * void str_free(string s);
 *
 * 
 * string str_cat_str(string s, string t);
 * string str_cat_char(string s, char *t);
 * 
 * string str_cpy(string s)
 *
 *
 */

int main() {
  string a;
  printf("size of string s => %s", a.data);
}
