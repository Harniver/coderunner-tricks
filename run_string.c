#define __DATA __CHAR   // The type in list and tree nodes TO REPLACE

#include "tester.h"     // Test library header and setup
#include "list.h"       // List data type header
// If needed, further data types may be implemented in a similar way as in those files

List stringToList(char *s); // Declaration of the function to be implemented TO REPLACE

#include "sol_string.c"
// TO REPLACE the first pattern
//{{ STUDENT_ANSWER | replace({
//    'List stringToList' : 'List student_stringToList', 'goto' : 'goto_disallowed',
//    'int main' : 'int student_main', 'malloc' : 'student_malloc', 'free' : 'student_free',
//    'printf' : 'student_printf', 'fprintf' : 'student_fprintf', 'dprintf' : 'student_dprintf',
//    'vprintf' : 'student_vprintf', 'vfprintf' : 'student_vfprintf', 'vdprintf' : 'student_vdprintf'
//}) }}

#define SEPARATOR       "#<ab@17943918#@>#" // Coderunner separator
#define __DEBUG         0                   // Use 1 while developing the question, then 0 when ready TO REPLACE
#define __FUNCTION      stringToList        // The name of the function to be developed TO REPLACE
typedef List (*__function_type)(char*);     // The type of the function to be developed TO REPLACE


#include <string.h>

// Reference correct solution TO REPLACE
List __reference(char *s) {
    if (s == NULL) return NULL;

    int n = strlen(s);
    List result = NULL;

    for (int i = n-1; i >= 0; i--) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            List tmp  = malloc(sizeof(ListNode));
            tmp->data = s[i] - 'A' + 'a';
            tmp->next = result;
            result = tmp;
        }
    }
    return result;
}

// Reference wrong solutions TO REPLACE
List __wrong1(char *s) {
    return NULL;
}
List __wrong2(char *s) {
    if (s == NULL) return NULL;

    int n = strlen(s);
    List result = NULL;

    for (int i = n-1; i >= 0; i--) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            List tmp  = malloc(sizeof(ListNode));
            tmp->data = s[i];
            tmp->next = result;
            result = tmp;
        }
    }
    return result;
}
List __wrong3(char *s) {
    if (s == NULL) return NULL;
    
    int n = strlen(s);
    List result = NULL;
    
    for (int i = n-1; i >= 0; i--) {
        List tmp  = malloc(sizeof(ListNode));
        tmp->data = ('A' <= s[i] && s[i] <= 'Z') ? s[i] - 'A' + 'a' : s[i];
        tmp->next = result;
        result = tmp;
    }
    return result;
}
__function_type __wrong[] = {__wrong1, __wrong2, __wrong3};


#include "list.c"       // List data type implementation
#include "tester.c"     // Test library implementation BEWARE: must be after data type implementations

// Wraps a call to a student or reference function TO REPLACE to fit the signature
List stringToList(char *s) {
    __WRAP_START;
    List p = NULL;
    SAFE_EXEC(p = __function(s));
    __WRAP_END;
    return p;
}

// Checks behaviour of the student function on a given input TO REPLACE to fit the signature
void __test(const char *a) {
    __TEST_START

    __string_type x = __string_build(a);
    __list_type l = stringToList(x);

    __string_type xr = __string_build(a);
    __list_type lr = __reference(x);

    // checks two values of a given type for equality possibly printing an error message; the last parameter force to print a debug message when no error occurs
    __ASSERT_SAME_AND_FREE(string, "argument", xr, "modified to",  x, 0);
    __ASSERT_SAME_AND_FREE(list,   "expected", lr, "but obtained", l, __print && __DEBUG);

    __TEST_END(string, a)
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
    __test("t%<>gp o@%");
    __test("i_u;-[+}i!");
    __test("5jv67;8868");
    __test("4 iu2s299b");
    __malloc_cnt_min = 1;
    __test("mfUght*GX{");
    __test("V_v@|Ii R`");
    __test(" 1cH-E3b9 ");
    __test("$2(4!P5u~j");
    __test("&&I5@94'@S");
    __test("_989zIU8CG");
    __test("5ly4:9If#5");
    __end_test_suite();
}

void big_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    char *a = malloc(100);
    a[99] = 0;
    for (int i=0; i<100 && __passed; ++i) {
        __list_rand(a, 100); // max length
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
