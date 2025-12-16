#include <stdio.h>
#include <stdlib.h>

typedef int __int_type;
typedef int __int_const;

// Builds an int from a string
__int_type __int_build(const char* s) {
    return s[0] <= '9' ? s[0] - '0' : s[0] <= 'Z' ? s[0] - 'A' + 10 : s[0] - 'a' + 10;
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

// Builds a random int string
void __int_rand(char *s) {
    s[0] = rand()%4 ? rand()%30+'a' : rand()%10+'0';
    s[1] = 0;
}
