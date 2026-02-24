#include "tester.h"     // Test library header and setup
// If needed, further data types may be implemented in a similar way as in those files

int stoub(char *s, unsigned short b, int *r); // Declaration of the function to be implemented TO REPLACE

#include "sol_intp.c"
// TO REPLACE the first pattern
//{{ STUDENT_ANSWER | replace({
//    'int stoub' : 'int student_stoub', 'goto' : 'goto_disallowed',
//    'int main' : 'int student_main', 'malloc' : 'student_malloc', 'free' : 'student_free',
//    'printf' : 'student_printf', 'fprintf' : 'student_fprintf', 'dprintf' : 'student_dprintf',
//    'vprintf' : 'student_vprintf', 'vfprintf' : 'student_vfprintf', 'vdprintf' : 'student_vdprintf',
//    'puts' : 'student_puts', 'fputs' : 'student_fputs'
//}) }}

#define SEPARATOR       "#<ab@17943918#@>#" // Coderunner separator
#define __DEBUG         1                   // Use 1 while developing the question, then 0 when ready TO REPLACE
#define __FUNCTION      stoub               // The name of the function to be developed TO REPLACE
typedef int (*__function_type)(char*, unsigned short, int*);    // The type of the function to be developed TO REPLACE


#include <string.h>

// Reference correct solution TO REPLACE
int __reference(char *s, unsigned short b, int *r) {
    if (s==NULL || b<2 || b >36 || r==NULL) return 0;
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') i++;
    if (s[i] == '-') {
        i++;
        sign = -1;
    } else if (s[i] == '+') i++;
    char ld = b > 9 ? '0' + 10 : '0' + b;
    char la = 'A' + b - 10;
    while ((s[i] >= '0' && s[i] < ld) || (s[i] >= 'A' && s[i] < la)) {
        int c = s[i]<ld ? s[i]-'0' : 10+s[i]-'A';
        num = (num * b) + c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}

// Reference wrong solutions TO REPLACE
int __wrong1(char *s, unsigned short b, int *r) {
    *r = 0;
    return 1;
}
int __wrong2(char *s, unsigned short b, int *r) {
    return 1;
}
int __wrong3(char *s, unsigned short b, int *r) {
    return 0;
}
int __wrong4(char *s, unsigned short b, int *r) {
    // doesn't handle corner cases
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') i++;
    if (s[i] == '-') {
        i++;
        sign = -1;
    } else if (s[i] == '+') i++;
    char ld = b > 9 ? '0' + 10 : '0' + b;
    char la = 'A' + b - 10;
    while ((s[i] >= '0' && s[i] < ld) || (s[i] >= 'A' && s[i] < la)) {
        int c = s[i]<ld ? s[i]-'0' : 10+s[i]-'A';
        num = (num * b) + c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}
int __wrong5(char *s, unsigned short b, int *r) {
    // doesn't handle whitespace
    if (s==NULL || b<2 || b >36 || r==NULL) return 0;
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    if (s[i] == '-') {
        i++;
        sign = -1;
    } else if (s[i] == '+') i++;
    char ld = b > 9 ? '0' + 10 : '0' + b;
    char la = 'A' + b - 10;
    while ((s[i] >= '0' && s[i] < ld) || (s[i] >= 'A' && s[i] < la)) {
        int c = s[i]<ld ? s[i]-'0' : 10+s[i]-'A';
        num = (num * b) + c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}
int __wrong6(char *s, unsigned short b, int *r) {
    // doesn't handle sign
    if (s==NULL || b<2 || b >36 || r==NULL) return 0;
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') i++;
    char ld = b > 9 ? '0' + 10 : '0' + b;
    char la = 'A' + b - 10;
    while ((s[i] >= '0' && s[i] < ld) || (s[i] >= 'A' && s[i] < la)) {
        int c = s[i]<ld ? s[i]-'0' : 10+s[i]-'A';
        num = (num * b) + c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}
int __wrong7(char *s, unsigned short b, int *r) {
    // doesn't handle letters
    if (s==NULL || b<2 || b >36 || r==NULL) return 0;
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') i++;
    if (s[i] == '-') {
        i++;
        sign = -1;
    } else if (s[i] == '+') i++;
    char ld = '0' + b;
    while (s[i] >= '0' && s[i] < ld) {
        int c = s[i]-'0';
        num = (num * b) + c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}
int __wrong8(char *s, unsigned short b, int *r) {
    // doesn't handle multiple digits
    if (s==NULL || b<2 || b >36 || r==NULL) return 0;
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') i++;
    if (s[i] == '-') {
        i++;
        sign = -1;
    } else if (s[i] == '+') i++;
    char ld = b > 9 ? '0' + 10 : '0' + b;
    char la = 'A' + b - 10;
    while ((s[i] >= '0' && s[i] < ld) || (s[i] >= 'A' && s[i] < la)) {
        int c = s[i]<ld ? s[i]-'0' : 10+s[i]-'A';
        num += c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}
__function_type __wrong[] = {__wrong1, __wrong2, __wrong3, __wrong4, __wrong5, __wrong6, __wrong7, __wrong8};


#include "tester.c"     // Test library implementation BEWARE: must be after data type implementations

// Wraps a call to a student or reference function TO REPLACE to fit the signature
int stoub(char *s, unsigned short b, int *r) {
    __WRAP_START;
    int p;
    SAFE_EXEC(p = __function(s, b, r));
    __WRAP_END;
    return p;
}

// Checks behaviour of the student function on a given input TO REPLACE to fit the signature
void __test(const char *a, unsigned short b, int *p) {
    __TEST_START

    __string_type xr = __string_build(a);
    int zr = __reference(xr, b, p);
    int yr = p ? *p : 0;
    if (p) *p = 1073741824;

    __string_type x = __string_build(a);
    int z = stoub(x, b, p);
    int y = p ? *p : 0;

    // checks two values of a given type for equality possibly printing an error message; the last parameter force to print a debug message when no error occurs
    __ASSERT_SAME_AND_FREE(string, "argument", xr, "modified to",  x, 0);
    if (zr != 0) {
        __ASSERT_SAME_AND_FREE(int, "expected result", yr, "but obtained", y, __print && __DEBUG);
    }
    __ASSERT_SAME_AND_FREE(int, "expected return code", zr, "but obtained", z, __print && __DEBUG);

    char *s = malloc(2);
    s[1] = 0;
    s[0] = b < 10 ? '0'+b : 'a'+b-10;
    __TEST_END(string, a, int, s)
    free(s);
}

// TEST GROUPS

// __meta_test tests the tests developed in the main function on a given function
// this test usually doesn't need to be replaced
void test_main() {
    __print = __DEBUG ? 1 : -1;
    __malloc_cnt_min = 0;
    __meta_test(__reference, "reference", "TEST PASSED\n");
    char* s = malloc(7);
    strcpy(s, "wrong1");
    for (int i=0; i<sizeof(__wrong)/sizeof(__wrong[0]); ++i) {
        s[5] = '1'+i;
        __meta_test(__wrong[i], s, "TEST FAILED\n");
    }
    free(s);
    __end_test_suite();
}

// TO REPLACE this and the following tests
void small_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    int r;
    __test(NULL, 10, &r);
    __test("0", 1, &r);
    __test("0", 40, &r);
    __test("0", 10, NULL);
    __test("7", 10, &r);
    __test("7", 2, &r);
    __test(" 7", 10, &r);
    __test(" 7", 2, &r);
    __test(" \n 7", 10, &r);
    __test(" \n 7", 2, &r);
    __test(" \n \t\t\n 7", 10, &r);
    __test(" \n \t\t\n 7", 2, &r);
    __test(" \n \t\t\n +7", 10, &r);
    __test(" \n \t\t\n +7", 2, &r);
    __test(" \n \t\t\n -7", 10, &r);
    __test(" \n \t\t\n -7", 2, &r);
    __test(" \n \t\t\n ++7", 10, &r);
    __test(" \n \t\t\n +-7", 10, &r);
    __test(" \n \t\t\n -+7", 10, &r);
    __test(" \n \t\t\n --7", 10, &r);
    __test("+", 6, &r);
    __test("-", 2, &r);
    __end_test_suite();
}

void big_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    int r;
    __test("374", 10, &r);
    __test("  +374", 10, &r);
    __test("\n-374", 10, &r);
    __test("374", 7, &r);
    __test("D2Aa", 18, &r);
    __test("FCBZ", 31, &r);
    __end_test_suite();
}

int main() {
    srand(42);
    test_main();
    printf("%s\n", SEPARATOR);
    small_tests();
    printf("%s\n", SEPARATOR);
    big_tests();
    return 0;
}
