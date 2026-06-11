#define __DATA __INT   // The type in list and tree nodes TO REPLACE

#include "tester.h"     // Test library header and setup
#include "list.h"       // List data type header
// If needed, further data types may be implemented in a similar way as in those files

List arrayToList(int *s, int n); // Declaration of the function to be implemented TO REPLACE

#include "sol_array.c"
// TO REPLACE the first pattern
//{{ STUDENT_ANSWER | replace({
//    'List arrayToList' : 'List student_arrayToList', 'goto' : 'goto_disallowed',
//    'int main' : 'int student_main', 'malloc' : 'student_malloc', 'free' : 'student_free',
//    'printf' : 'student_printf', 'fprintf' : 'student_fprintf', 'dprintf' : 'student_dprintf',
//    'vprintf' : 'student_vprintf', 'vfprintf' : 'student_vfprintf', 'vdprintf' : 'student_vdprintf',
//    'puts' : 'student_puts', 'fputs' : 'student_fputs'
//}) }}

#define SEPARATOR       "#<ab@17943918#@>#" // Coderunner separator
#define __DEBUG         0                   // Use 1 while developing the question, then 0 when ready TO REPLACE
#define __FUNCTION      arrayToList         // The name of the function to be developed TO REPLACE
typedef List (*__function_type)(int*,int);  // The type of the function to be developed TO REPLACE


#include <string.h>

// Reference correct solution TO REPLACE
List __reference(int *s, int n) {
    if (s == NULL) return NULL;

    List result = NULL;

    for (int i = n-1; i >= 0; i--) {
        List tmp  = malloc(sizeof(ListNode));
        tmp->data = s[i];
        tmp->next = result;
        result = tmp;
    }
    return result;
}

// Reference wrong solutions TO REPLACE
List __wrong1(int *s, int n) {
    return NULL;
}
__function_type __wrong[] = {__wrong1};


#include "list.c"       // List data type implementation
#include "array.c"       // array data type implementation
#include "tester.c"     // Test library implementation BEWARE: must be after data type implementations

// Wraps a call to a student or reference function TO REPLACE to fit the signature
List arrayToList(int *s, int n) {
    __WRAP_START;
    List p = NULL;
    SAFE_EXEC(p = __function(s, n));
    __WRAP_END;
    return p;
}

// Checks behaviour of the student function on a given input TO REPLACE to fit the signature
void __test(const char *a) {
    __TEST_START

    __array_type x = __array_build(a);
    __list_type l = arrayToList(x, __array_len);

    __array_type xr = __array_build(a);
    __list_type lr = __reference(x, __array_len);

    // checks two values of a given type for equality possibly printing an error message; the last parameter force to print a debug message when no error occurs
    __ASSERT_SAME_AND_FREE(array, "argument", xr, "modified to",  x, 0);
    __ASSERT_SAME_AND_FREE(list,  "expected", lr, "but obtained", l, __print && __DEBUG);

    __TEST_END(array, a)
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
    __end_test_suite();
}

// TO REPLACE this and the following tests
void samples() {
    __print = 1;
    __malloc_cnt_min = 0;
    __test(NULL);
    __malloc_cnt_min = 0;
    __test("");
    __malloc_cnt_min = 1;
    __test("A");
    __test("AZbCuu12R");
    __end_test_suite();
}

void small_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    __test("5jv67e8868");
    __test("4Aiu2s299b");
    __malloc_cnt_min = 1;
    __test("mfUghtiGX0");
    __test("5989zIU8CG");
    __end_test_suite();
}

void big_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    char *a = malloc(100);
    for (int i=0; i<100 && __passed; ++i) {
        __array_rand(a, 100); // max length
        __test(a);
    }
    free(a);
    __end_test_suite();
}

int main() {
    srand(42);
    test_main();
    printf("%s\n", SEPARATOR);
    samples();
    printf("%s\n", SEPARATOR);
    small_tests();
    printf("%s\n", SEPARATOR);
    big_tests();
    return 0;
}
