#include <stdio.h>
#include <assert.h>

typedef __data_t* __array_type;
typedef const __data_t* __array_const;

// Sets the length of arrays
size_t __array_len = 0;

// Builds an array from a string
__array_type __array_build(const char* s) {
    if (s == NULL) return NULL;
    __array_len = strlen(s);
    __array_type t = (__array_type)malloc(sizeof(__data_t)*__array_len);
    for (size_t i=0; i<__array_len; ++i)
        t[i] = __data_r(s[i]);
    return t;
}

// Frees the memory occupied by an array
void __array_free(__array_type a) {
    if (a != NULL) free(a);
}

// Checks two arrays for equality
_Bool __array_diff(__array_const a, __array_const b) {
    if (a == NULL && b == NULL) return 0;
    if (a == NULL || b == NULL) return 1;
    for (size_t i=0; i<__array_len; ++i)
        if (a[i] != b[i]) return 1;
    return 0;
}

// Prints an array
void __array_print(__array_const a) {
    if (a == NULL) {
        printf("NULL");
        return;
    }
    printf("[");
    int cnt;
    for (cnt=0; cnt < __array_len && cnt < 10; ++cnt) {
        if (cnt > 0) printf(",");
        printf(__data_f, a[cnt]);
    }
    if (cnt < __array_len && cnt == 10) printf("...");
    printf("]");
}

// Builds a random array string
void __array_rand(char *s, int max_len) {
    __array_len = max_len-1;
    for (int i=0; i<max_len-1; ++i) s[i] = __data_rand();
    s[max_len-1] = 0;
}
