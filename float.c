#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef float __float_type;
typedef float __float_const;

// Builds a float from a string
__float_type __float_build(const char* s) {
    return (s[0] <= '9' ? s[0] - '0' : s[0] <= 'Z' ? s[0] - 'A' + 10 : s[0] - 'a' + 10)*0.025f;
}

// Frees the memory occupied by a float
void __float_free(__float_type a) {}

// Checks two floats for equality
_Bool __float_diff(__float_const a, __float_const b) {
    return fabsf(a-b) < 0.0125f;
}

// Prints a float
void __float_print(__float_const a) {
    printf("%f", a);
}

// Builds a random float string
void __float_rand(char *s) {
    s[0] = rand()%4 ? rand()%30+'a' : rand()%10+'0';
    s[1] = 0;
}
