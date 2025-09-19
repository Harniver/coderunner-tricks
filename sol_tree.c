#include "list.h"
#include "tree.h"

/* INSERIRE QUI EVENTUALI ALTRI #include <...> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  INSERIRE QUI EVENTUALI FUNZIONI AUSILIARIE (CON UN COMMENTO SIGNIFICATIVO IN TESTA) */

void list_free(List l) {
    if (l == NULL) return;
    list_free(l->next);
    free(l);
}

void tree_free(Tree t) {
    if (t == NULL) return;
    tree_free(t->left);
    tree_free(t->right);
    free(t);
}

/**
 * Dato un albero binario t, restituire una nuova lista p (senza modificare t)
 * che contenga il percorso entro t che parte dalla radice, e procede a sinistra
 * se il valore in un nodo è dispari, e a destra altrimenti.
 *
 * Gli alberi sono rappresentati tramite parentesi, con "-" per indicare un figlio mancante.
 * Non considera l'eventualità che la malloc fallisca.
 *
 * ESEMPI (rappresentando le liste senza separare i caratteri, per compattezza):
 * (1) dato t={}, restituisce l=[]
 * (2) dato t={-1-}, restituisce l=[1]
 * (3) dato t={[-3-]1-[-4-]}, restituisce l=[1,3]
 * (4) dato t={[-3-]2-[-4-]}, restituisce l=[1,4]
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_parityPath"
 * NOTA: questa funzione viene testata indipendentemente dal vostro main
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 */
List student_parityPath(Tree t) {
    if (t == NULL) return NULL;
    List l = malloc(sizeof(ListNode));
    l->data = t->data;
    if (t->data % 2)
        l->next = parityPath(t->left);
    else
        l->next = parityPath(t->right);
    return l;
}

/**
 * Invoca la funzione parityPath su alcuni casi a scelta per testarne la correttezza.
 * Se la funzione parityPath è corretta, come ultima cosa deve stampare "TEST PASSED\n".
 * Se invece la funzione non risulta corretta, deve stampare "TEST FAILED\n".
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_main"
 * NOTA: il main viene testato indipendentemente dalla vostra funzione parityPath
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 */
int student_main() {
    _Bool pass = 1;
    List l;
    Tree t = NULL;

    l = parityPath(t);
    if (l != NULL) pass = 0;
    list_free(l);

    t = malloc(sizeof(TreeNode));
    t->data = 1;
    t->left = NULL;
    t->right = NULL;
    l = parityPath(t);
    if (l == NULL) pass = 0;
    else {
        if (l->data != 1) pass = 0;
        if (l->next != NULL) pass = 0;
    }
    list_free(l);

    t->left = malloc(sizeof(TreeNode));
    t->left->data = 2;
    t->left->left = NULL;
    t->left->right = malloc(sizeof(TreeNode));
    t->left->right->data = 3;
    t->left->right->left = NULL;
    t->left->right->right = NULL;
    l = parityPath(t);
    if (l == NULL) pass = 0;
    else {
        if (l->data != 1) pass = 0;
        if (l->next == NULL) pass = 0;
        else {
            if (l->next->data != 2) pass = 0;
            if (l->next->next == NULL) pass = 0;
            else {
                if (l->next->next->data != 3) pass = 0;
                if (l->next->next->next != NULL) pass = 0;
            }
        }
    }
    list_free(l);

    tree_free(t);
    if (pass)
        student_printf("TEST PASSED\n");
    else student_printf("TEST FAILED\n");
    return 0;
}
