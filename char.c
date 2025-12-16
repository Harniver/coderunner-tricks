#include <stdio.h>
#include <stdlib.h>

typedef char __char_type;
typedef char __char_const;

// Builds a char from a string
__char_type __char_build(const char* s) {
    return s[0];
}

// Frees the memory occupied by a char
void __char_free(__char_type a) {}

// Checks two chars for equality
_Bool __char_diff(__char_const a, __char_const b) {
    return a != b;
}

// Prints a char
void __char_print(__char_const a) {
    printf("%c", a);
}
