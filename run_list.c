#define __DATA __CHAR   // The type in list and tree nodes

#include "tester.h"     // Test library header and setup
#include "list.h"       // List data type header

List antiPrefix(List l, List r); // Declaration of the function to be implemented

#include "sol_list.c"
//{{ STUDENT_ANSWER | replace({
//    'List antiPrefix' : 'List student_antiPrefix', 'goto' : 'goto_disallowed',
//    'int main' : 'int student_main', 'malloc' : 'student_malloc', 'free' : 'student_free',
//    'printf' : 'student_printf', 'fprintf' : 'student_fprintf', 'dprintf' : 'student_dprintf',
//    'vprintf' : 'student_vprintf', 'vfprintf' : 'student_vfprintf', 'vdprintf' : 'student_vdprintf'
//}) }}

#define SEPARATOR       "#<ab@17943918#@>#" // Coderunner separator
#define __DEBUG         0                   // Use 1 while developing the question, then 0 when ready
#define __FUNCTION      antiPrefix          // The name of the function to be developed
typedef List (*__function_type)(List,List); // The type of the function to be developed


// Reference correct solution
List __reference(List l, List r) {
    List p = NULL, e = NULL;

    while (l != NULL) {
        if (r != NULL) {
            if (l->data == r->data) break;
            r = r->next;
        }
        List t = malloc(sizeof(ListNode));
        t->data = l->data;
        t->next = NULL;
        if (e == NULL)
            p = e = t;
        else {
            e->next = t;
            e = t;
        }
        l = l->next;
    }
    return p;
}

// Reference wrong solutions
List __wrong1(List l, List r) {
    return NULL;
}
// Reference wrong solutions
List __wrong2(List l, List r) {
    if (l == NULL) return NULL;
    List copy = malloc(sizeof(ListNode));
    List head = copy;
    head->data = l->data;
    head->next = NULL;
    l = l->next;
    while (l != NULL) {
        head->next = malloc(sizeof(ListNode));
        head = head->next;
        head->data = l->data;
        head->next = NULL;
        l = l->next;
    }
    return copy;
}
__function_type __wrong[] = {__wrong1, __wrong2};


#include "list.c"       // List data type implementation
#include "tester.c"     // Test library implementation BEWARE: must be after data type implementations

// Wraps a call to a student or reference function (adjust to fit the signature)
List antiPrefix(List l, List r) {
    __WRAP_START;
    List p = NULL;
    SAFE_EXEC(p = __function(l, r));
    __WRAP_END;
    return p;
}

// Checks behaviour of the student function on a given input
void __test(const char* s, const char *t) {
    __TEST_START

    List x = __list_build(s);
    List y = __list_build(t);
    List p = antiPrefix(x, y);

    List xr = __list_build(s);
    List yr = __list_build(t);
    List pr = __reference(xr, yr);

    __ASSERT_SAME_AND_FREE(list, "argument", xr, "modified to",  x, 0);
    __ASSERT_SAME_AND_FREE(list, "argument", yr, "modified to",  y, 0);
    __ASSERT_SAME_AND_FREE(list, "expected", pr, "but obtained", p, __print && __DEBUG);

    __TEST_END(list, s, list, t)
}

// TEST GROUPS

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

void samples() {
    __print = 1;
    __malloc_cnt_min = 0;
    __test("", "");
    __test("", "pippo");
    __test("pippo", "pippo");
    __malloc_cnt_min = 2;
    __test("pippo", "");
    __test("superpippo", "pluto");
    __test("pluto", "superpippo");
    __test("superpippo", "pippo");
    __test("pippo", "superpippo");
    __end_test_suite();
}

void small_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    __test("", "");
    __test("", "iKuooYi");
    __test("4iu2s299b", "4iu2s299b");
    __malloc_cnt_min = 2;
    __test("tUgpXow", "");
    __test("5jv678868", "jv678");
    __test("jv678", "5jv678868");
    __test("mfxUghtt", "cPsU7jrtp8");
    __test("cPsU7jrtp8", "mfxUghtt");
    __end_test_suite();
}

void big_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    char *a = malloc(100*sizeof(char));
    char *b = malloc(100*sizeof(char));
    for (int i=0; i<100 && __passed; ++i) {
        __list_rand(a, 100); // max length
        __list_rand(b, 100); // max length
        __test(a, b);
    }
    free(a);
    free(b);
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
