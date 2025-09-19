#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "data.c"

typedef Tree __tree_type;
typedef const TreeNode* __tree_const;

// Frees the memory occupied by a Tree
void __tree_free(__tree_type a) {
    if (a != NULL) {
        __tree_free(a->left);
        __tree_free(a->right);
        free(a);
    }
}

// Checks two Trees for equality
_Bool __tree_diff(__tree_const a, __tree_const b) {
    if (a == NULL && b == NULL) return 0;
    if (a == NULL || b == NULL) return 1;
    if (a->data != b->data) return 1;
    if (__tree_diff(a->left, b->left)) return 1;
    return __tree_diff(a->right, b->right);
}

// Depth while printing a tree
int __print_depth = 0;
const char* __open_depth  = "{[(<";
const char* __close_depth = "}])>";

// Prints a Tree
void __tree_print(__tree_const a) {
    if (a == NULL) {
        printf("-");
        return;
    }
    if (__print_depth == 4) {
        printf("...");
        return;
    }
    printf("%c", __open_depth[__print_depth]);
    __print_depth++;
    __tree_print(a->left);
    if (a->data != (__data_t)-1)
        printf(__data_f, a->data);
    else printf("?");
    __tree_print(a->right);
    __print_depth--;
    printf("%c", __close_depth[__print_depth]);
}

// Builds a Tree from a string (recursive)
__tree_type __tree_build_rec(const char* s, int* pos, int* exp) {
    if (s[*pos] == '-' || s[*pos] == '*') {
        (*pos)++;
        return NULL;
    }
    Tree t = malloc(sizeof(TreeNode));
    t->left = NULL;
    t->data = (__data_t)-1;
    t->right = NULL;
    if (!(s[*pos] == '{' || s[*pos] == '[' || s[*pos] == '(' || s[*pos] == '<')) {
        *exp = 1;
        return t;
    }
    (*pos)++;
    t->left = __tree_build_rec(s, pos, exp);
    if (*exp == 1) return t;
    t->data = __data_r(s[*pos]);
    (*pos)++;
    t->right = __tree_build_rec(s, pos, exp);
    if (*exp == 1) return t;
    if (!(s[*pos] == '}' || s[*pos] == ']' || s[*pos] == ')' || s[*pos] == '>')) {
        *exp = -1;
        return t;
    }
    (*pos)++;
    return t;
}

// Builds a Tree from a string
__tree_type __tree_build(const char* s) {
    if (s == NULL) return NULL;
    int pos = 0;
    int exp = 0;
    __tree_type t = __tree_build_rec(s, &pos, &exp);
    if (exp != 0) {
        printf("CODERUNNER: IMPOSSIBILE PARSARE ALBERO\n");
        printf("> mi aspettavo una parentesi %s in posizione %d\n", exp > 0 ? "aperta" : "chiusa", pos);
        for (int i=0; s[i]; ++i) {
            if (i == pos) printf(" !?! ");
            printf("%c", s[i]);
        }
        printf("\n");
        printf("> risultato (parziale) del parsing:\n");
        __tree_print(t);
        printf("\n");
    }
    return t;
}

// Builds a random Tree string
void __tree_rand_rec(char* s, int max_len, float prob_child, int* pos) {
    if (*pos+5 > max_len || rand() > prob_child*RAND_MAX) {
        s[*pos] = '-';
        (*pos)++;
        return;
    }
    s[*pos] = '(';
    (*pos)++;
    __tree_rand_rec(s, max_len-3, prob_child, pos);
    s[*pos] = __data_rand();
    (*pos)++;
    __tree_rand_rec(s, max_len-1, prob_child, pos);
    s[*pos] = ')';
    (*pos)++;
}
void __tree_rand(char *s, int max_len, float prob_child) {
    int pos = 0;
    __tree_rand_rec(s, max_len-1, prob_child, &pos);
    s[pos] = 0;
}
