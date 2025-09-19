#define __DATA __INT    // The type in list and tree nodes

#include "tester.h"     // Test library header and setup
#include "list.h"       // List data type header
#include "tree.h"       // Tree data type header

List parityPath(Tree t); // Declaration of the function to be implemented

#include "sol_tree.c"
//{{ STUDENT_ANSWER | replace({
//    'List parityPath' : 'List student_parityPath', 'goto' : 'goto_disallowed',
//    'int main' : 'int student_main', 'malloc' : 'student_malloc', 'free' : 'student_free',
//    'printf' : 'student_printf', 'fprintf' : 'student_fprintf', 'dprintf' : 'student_dprintf',
//    'vprintf' : 'student_vprintf', 'vfprintf' : 'student_vfprintf', 'vdprintf' : 'student_vdprintf'
//}) }}

#define SEPARATOR       "#<ab@17943918#@>#" // Coderunner separator
#define __DEBUG         0                   // Use 1 while developing the question, then 0 when ready
#define __FUNCTION      parityPath          // The name of the function to be developed
typedef List (*__function_type)(Tree);      // The type of the function to be developed


// Reference correct solution
List __reference(Tree t) {
    if (t == NULL) return NULL;
    List l = malloc(sizeof(ListNode));
    l->data = t->data;
    if (t->data % 2)
        l->next = __reference(t->left);
    else
        l->next = __reference(t->right);
    return l;
}

// Reference wrong solutions
List __wrong1(Tree t) {
    return NULL;
}
List __wrong2(Tree t) {
    if (t == NULL) return NULL;
    List l = malloc(sizeof(ListNode));
    l->data = t->data;
    l->next = __wrong2(t->left);
    return l;
}
List __wrong3(Tree t) {
    if (t == NULL) return NULL;
    List l = malloc(sizeof(ListNode));
    l->data = t->data;
    l->next = __wrong2(t->right);
    return l;
}
__function_type __wrong[] = {__wrong1, __wrong2, __wrong3};


#include "list.c"       // List data type implementation
#include "tree.c"       // Tree data type implementation
#include "tester.c"     // Test library implementation BEWARE: must be after data type implementations

// Wraps a call to a student or reference function (adjust to fit the signature)
List parityPath(Tree t) {
    __WRAP_START;
    List l = NULL;
    SAFE_EXEC(l = __function(t));
    __WRAP_END;
    return l;
}

// Checks behaviour of the student function on a given input
void __test(const char* s) {
    __TEST_START

    Tree t = __tree_build(s);
    List l = parityPath(t);

    Tree tr = __tree_build(s);
    List lr = __reference(t);

    __ASSERT_SAME_AND_FREE(tree, "argument", tr, "modified to",  t, 0);
    __ASSERT_SAME_AND_FREE(list, "expected", lr, "but obtained", l, __print && __DEBUG);

    __TEST_END(tree, s)
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
    __test("*");
    __malloc_cnt_min = 1;
    __test("(*1*)");
    __malloc_cnt_min = 2;
    __test("((*3*)1(*4*))");
    __test("((*3*)2(*4*))");
    __end_test_suite();
}

void small_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    __test("*");
    __malloc_cnt_min = 1;
    __test("(*b*)");
    __test("(*d(*a*))");
    __malloc_cnt_min = 2;
    __test("((*c*)f*)");
    __test("(((*b*)e*)h(*e*))");
    __test("(((*b*)e*)g(*e*))");
    __malloc_cnt_min = 3;
    __test("((*a(*d*))j(*e*))");
    __end_test_suite();
}

void big_tests() {
    __print = __DEBUG;
    __malloc_cnt_min = 0;
    char *a = malloc(100*sizeof(char));
    for (int i=0; i<100 && __passed; ++i) {
        __tree_rand(a, 100, 0.6); // max length + probability of child
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
