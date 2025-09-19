#include <stdio.h>
#include <stdlib.h>

typedef int __int_type;
typedef int __int_const;

// Builds a string from a int
__int_type __int_build(const char* s) {
    return atoi(s);
}

// Frees the memory occupied by a int
void __int_free(__int_type a) {}

// Checks two ints for equality
_Bool __int_diff(__int_const a, __int_const b) {
    return a != b;
}

// Prints a int
void __int_print(__int_const a) {
    printf("%d", a);
}
