#include <stdio.h>
#include "list.h"
#include "data.c"

typedef List __list_type;
typedef const ListNode* __list_const;

// Frees the memory occupied by a List
void __list_free(__list_type a) {
    while (a != NULL) {
        List tmp = a;
        a = a->next;
        free(tmp);
    }
}

// Checks two Lists for equality
_Bool __list_diff(__list_const a, __list_const b) {
    if (a == NULL && b == NULL) return 0;
    if (a == NULL || b == NULL) return 1;
    if (a->data != b->data) return 1;
    return __list_diff(a->next, b->next);
}

// Prints a List
void __list_print(__list_const a) {
    printf("[");
    int cnt = 0;
    while (a != NULL && cnt < 10) {
        if (cnt > 0) printf(",");
        printf(__data_f, a->data);
        a = a->next;
        cnt++;
    }
    if (a != NULL && cnt == 10) printf("...");
    printf("]");
}

// Builds a List from a string
__list_type __list_build(const char* s) {
    if (s == NULL) return NULL;
    List l = NULL;
    List *p = &l;
    while (*s != 0) {
        List n = malloc(sizeof(ListNode));
        n->data = __data_r(*s);
        n->next = NULL;
        *p = n;
        p = &(n->next);
        ++s;
    }
    return l;
}

// Builds a random List string
void __list_rand(char *s, int max_len) {
    for (int i=0; i<max_len-1; ++i) s[i] = __data_rand();
    s[max_len-1] = 0;
}
