#include <stdio.h>
#include <string.h>

typedef char* __string_type;
typedef const char* __string_const;

// Builds a string from a string
__string_type __string_build(const char* s) {
    if (s == NULL) return NULL;
    __string_type t = malloc(strlen(s)+1);
    strcpy(t, s);
    return t;
}

// Frees the memory occupied by a string
void __string_free(__string_type a) {
    if (a != NULL) free(a);
}

// Checks two strings for equality
_Bool __string_diff(__string_const a, __string_const b) {
    if (a == NULL && b == NULL) return 0;
    if (a == NULL || b == NULL) return 1;
    return strcmp(a, b) != 0;
}

// Prints a string
void __string_print(__string_const a) {
    if (a == NULL) {
        printf("NULL");
        return;
    }
    printf("\"");
    int cnt = 0;
    for (cnt=0; a[cnt] != 0 && cnt < __MAX_PRINT_SIZE-2; ++cnt)
        if (a[cnt] == '\n') printf("\\n");
        else if (a[cnt] == '\t') printf("\\t");
        else if (a[cnt] == '\\') printf("\\\\");
        else printf("%c", a[cnt]);
    if (cnt == __MAX_PRINT_SIZE-2 && a[cnt] != 0) printf("...");
    printf("\"");
}
