#ifndef __MAX_PRINT_SIZE
#define __MAX_PRINT_SIZE  64      // maximum size of a student print that is captured
#endif

#include "int.c"
#include "string.c"

#undef malloc
#undef free

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#define __STRINGIFY(x)      #x
#define __TOSTRING(x)       __STRINGIFY(x)
#define __STUDENTIFY(x)     student_ ## x
#define __TOSTUDENT(x)      __STUDENTIFY(x)
#define __STUDENT_FUNCTION  __TOSTUDENT(__FUNCTION)

#ifndef __MALLOC_EXTRA
#define __MALLOC_EXTRA    16      // extra bytes around memory chunks that are checked for out-of-bounds access
#endif

#ifndef __MALLOC_SIZE_MAX
#define __MALLOC_SIZE_MAX 1024    // maximum size that can be allocated in a test
#endif

#ifndef __MALLOC_CNT_MAX
#define __MALLOC_CNT_MAX  1024    // maximum number of malloc allowed in a test
#endif

const char* __function_name = __TOSTRING(__FUNCTION);   // the name of the function to be implemented
__function_type __function = __STUDENT_FUNCTION;        // a pointer to the student function to be executed

char __last_print[__MAX_PRINT_SIZE];        // buffer capturing printfs of the student
int __print = 1;                            // the level of detail printed for a test (1: all, 0: all of first fail, -1: input of first fail)
int __passed = 1;                           // whether tests are passed so far

char* __malloc_addr[__MALLOC_CNT_MAX];      // all pointers that are being allocated
int __malloc_size[__MALLOC_CNT_MAX];        // size of the corresponding memory chunk
int __malloc_size_max = __MALLOC_SIZE_MAX;  // maximum size that can be allocated in a test (modifyable)
int __malloc_cnt_max = __MALLOC_CNT_MAX;    // maximum number of malloc allowed in a test (modifyable)
int __malloc_cnt_min = 0;                   // minimum number of malloc allowed in a test (modifyable)
int __malloc_cnt = 0, __free_cnt = 0;       // counters of malloc and free called
int __student_malloc_cnt = 0;               // counter of student mallocs
int __call_counter = 0;                     // counter of calls to student function
int __recursion_depth = 0;                  // depth of recursion in student function
int __try_depth = 0;                        // depth of nested try-catch of errors
int __signal = -1;                          // signal code in case of errors
jmp_buf __env[16];                          // jump information to catch errors


// Prints output from the student
int student_vprintf(const char *restrict format, va_list ap) {
    int r = vsnprintf(__last_print, sizeof(__last_print), format, ap);
    if (__print >= 0) {
        printf(">> ");
        __string_print(__last_print);
        printf("\n");
    }
    return r;
}


// Computes a reasonably unguessable number from two indices
char __secret(size_t i, size_t j) {
    size_t acc = 150;
    acc += (175*i)%256 + (253*i*(i+1)/2)%256;
    acc += (29*j)%256 + (129*j*(j+1)/2)%256;
    acc = (acc + 207*i*j)%256;
    return (char)acc;
}

// Malloc wrapper: if the size or __malloc_cnt are not small enough returns NULL, else allocate more memory filling it with the secret
void* student_malloc(size_t size) {
    if (size > __malloc_size_max || __malloc_cnt == __malloc_cnt_max) return NULL;
    __malloc_size[__malloc_cnt] = size + 2*__MALLOC_EXTRA;
    __malloc_addr[__malloc_cnt] = malloc(__malloc_size[__malloc_cnt]);
    for (int j=0; j<__malloc_size[__malloc_cnt]; ++j)
        __malloc_addr[__malloc_cnt][j] = __secret(__malloc_cnt, j);
    return __malloc_addr[__malloc_cnt++] + __MALLOC_EXTRA;
}

// Free wrapper: checks that the pointer was allocated before and that the secret was untouched, then frees
void student_free(void* ptr) {
    char* addr = (char*)ptr;
    addr -= __MALLOC_EXTRA;
    for (int i=0; i<__malloc_cnt; ++i)
        if (__malloc_addr[i] == addr) {
            for (int j=0; j<__MALLOC_EXTRA; ++j) {
                int k = __malloc_size[i]-1-j;
                if (__malloc_addr[i][j] != __secret(i, j) ||  __malloc_addr[i][k] != __secret(i, k)) {
                    printf("ERROR: access outside of bounds of allocated memory\n");
                    __passed = 0;
                    break;
                }
            }
            __malloc_addr[i] = NULL;
            free(addr);
            ++__free_cnt;
            return;
        }
    printf("ERROR: free of an unallocated pointer (maybe a double-free error)\n");
    ++__free_cnt;
    __passed = 0;
}

// Checks that all allocated memory has been freed after a test and the minimum number of mallocs has been met, then resets for next test
void __check_free() {
    if (__student_malloc_cnt < __malloc_cnt_min) {
        if (__call_counter > 0)
            printf("ERROR: %d malloc called by student function, below a minimum of %d\n", __student_malloc_cnt, __malloc_cnt_min);
        __passed = 0;
    }
    if (__malloc_cnt != __free_cnt) {
        printf("ERROR: %d malloc called and %d free called overall\n", __malloc_cnt, __free_cnt);
        __passed = 0;
    }
    __malloc_cnt = 0;
    __free_cnt = 0;
}

// Sets captured signals to a given function
void __set_signals(void (*func)(int)) {
    signal(SIGSEGV, func);
    signal(SIGFPE,  func);
}

// Handler ignoring errors
void __handle_error(int signum) {
    __try_depth--;
    if (__try_depth == 0) __set_signals(SIG_DFL);
    __passed = 0;
    __signal = signum;
    longjmp(__env[__try_depth], 1);
}

// Macro protecting code from segmentation faults
#define SAFE_EXEC_NAME(CODE, NAME)                                              \
    if (__try_depth == 16) {                                                    \
        CODE;                                                                   \
    } else if (setjmp(__env[__try_depth]) == 0) {                               \
        if (__try_depth == 0) __set_signals(&__handle_error);                   \
        __try_depth++;                                                          \
        CODE;                                                                   \
        __try_depth--;                                                          \
        if (__try_depth == 0) __set_signals(SIG_DFL);                           \
    } else {                                                                    \
        if (__signal == SIGSEGV)                                                \
            printf("ERROR: segmentation fault in student_%s\n", NAME);          \
        else                                                                    \
            printf("ERROR: floating-point exception in student_%s\n", NAME);    \
    }

// Special case for student function
#define SAFE_EXEC(CODE) SAFE_EXEC_NAME(CODE, __function_name)

// Starts the wrap of a call to the student function
#define __WRAP_START                            \
    if (__recursion_depth == 0)                 \
        __student_malloc_cnt = __malloc_cnt;    \
    ++__call_counter;                           \
    ++__recursion_depth;
// Ends the wrap of a call to the student function
#define __WRAP_END              \
    --__recursion_depth;        \
    if (__recursion_depth == 0) \
        __student_malloc_cnt = __malloc_cnt - __student_malloc_cnt;

// Asserts that two values are the same
#define __ASSERT_SAME_AND_FREE(type, pre, x, post, y, force_print)  \
    if (__ ## type ## _diff(x, y)) {                                \
        if (__print == 1 || __passed == 1) {                        \
            printf("ERROR: "pre" ");                                \
            __ ## type ## _print(x);                                \
            printf(" "post" ");                                     \
            __ ## type ## _print(y);                                \
            printf("\n");                                           \
        }                                                           \
        __passed = 0;                                               \
    } else if (force_print) {                                       \
        printf("DEBUG: "pre" ");                                    \
        __ ## type ## _print(x);                                    \
        printf("\n");                                               \
    }                                                               \
    __ ## type ## _free(x);                                         \
    __ ## type ## _free(y);

// Resets for the start of a testcase
#define __TEST_START                                    \
    __call_counter = 0;                                 \
    if (__passed == 0) {                                \
        if (__print == 1) printf("TESTCASE SKIPPED\n"); \
        return;                                         \
    }

// Builds then prints a type
#define __TPRINT(type, v) {                             \
    __ ## type ## _type TT = __ ## type ## _build(v);   \
    __ ## type ## _print(TT);                           \
    __ ## type ## _free(TT);                            \
}

// Printing a variable sequence of arguments
#define __TCOMMA                        printf(", ");
#define __TMAP0(X)
#define __TMAP1(A,B)                    __TPRINT(A,B)
#define __TMAP2(A,B,C,D)                __TMAP1(A,B) __TCOMMA __TMAP1(C,D)
#define __TMAP3(A,B,C,D,E,F)            __TMAP1(A,B) __TCOMMA __TMAP2(C,D,E,F)
#define __TMAP4(A,B,C,D,E,F,G,H)        __TMAP1(A,B) __TCOMMA __TMAP2(C,D,E,F,G,H)
#define __TMAPX(A,B,C,D,E,F,G,H,X,...)  X
#define __TPARGS(...)                   __TMAPX(__VA_ARGS__, __TMAP4, ARG_ERR, __TMAP3, ARG_ERR, __TMAP2, ARG_ERR, __TMAP1, __TMAP0)(__VA_ARGS__)

// Checks malloc/free then print testcase result at the end of a testcase
#define __TEST_END_NAME(name, ...)                  \
    __check_free();                                 \
    if (__passed == 0 || __print == 1) {            \
        printf("TESTCASE %s(", name);               \
        __TPARGS(__VA_ARGS__);                      \
        if (__passed) printf(") OK\n");             \
        else printf(") FAILED\n");                  \
    }
#define __TEST_END(...) __TEST_END_NAME(__function_name, __VA_ARGS__)

// Prints test suite result and reset success status
void __end_test_suite() {
    if (__passed) printf("TEST PASSED\n");
    else printf("TEST FAILED\n");
    __passed = 1;
}

// Tests that main function calls once the function and performs a minimum number of mallocs (legacy)
void __test_main(const char* func_name, int malloc_min_func, int malloc_min_tot) {
    __call_counter = 0;
    __malloc_cnt_min = malloc_min_func;
    int malloc_main_min = malloc_min_tot;
    SAFE_EXEC_NAME(student_main(), "main");
    printf("\n");
    if (__call_counter != 1) {
        printf("ERROR: %s called %d times\n", func_name, __call_counter);
        __passed = 0;
    }
    if (__malloc_cnt < malloc_main_min) {
        if (__call_counter == 1)
            printf("ERROR: %d malloc called overall, below a minimum of %d\n", __malloc_cnt, malloc_main_min);
        __passed = 0;
    }
    __check_free();
    if (__passed) printf("EXECUTION COMPLETE\n");
    else printf("EXECUTION FAILED\n");
    __passed = 1;
}

// Tests that the student tests obtain a certain result on a certain function
void __meta_test(__function_type f, const char* name, const char* expected) {
    __TEST_START
    __function = f;
    SAFE_EXEC_NAME(student_main(), "main");
    __function = __STUDENT_FUNCTION;
    __check_free();
    if (strcmp(expected, __last_print) != 0) {
        printf("ERROR: expected ");
        __string_print(expected);
        printf(" but obtained ");
        __string_print(__last_print);
        printf("\n");
        __passed = 0;
    }
    __TEST_END_NAME(name,-)
}
