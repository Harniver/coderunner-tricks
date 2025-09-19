#include "list.h"

/* INSERIRE QUI EVENTUALI ALTRI #include <...> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  INSERIRE QUI EVENTUALI FUNZIONI AUSILIARIE (CON UN COMMENTO SIGNIFICATIVO IN TESTA) */

List buildList(char const* s) {
    List t = NULL;
    List *e = &t;
    for (int i=0; s[i] != 0; ++i) {
        (*e) = malloc(sizeof(ListNode));
        (*e)->data = s[i];
        (*e)->next = NULL;
        e = &((*e)->next);
    }
    return t;
}

void list_free(List l) {
    if (l == NULL) return;
    list_free(l->next);
    free(l);
}

_Bool list_diff(List a, List b) {
    if (a == NULL && b == NULL) return 0;
    if (a == NULL || b == NULL) return 1;
    if (a->data != b->data) return 1;
    return list_diff(a->next, b->next);
}

/**
 * Date due liste di caratteri l ed r, restituire una nuova lista p (senza
 * modificare le liste l ed r) che contenga il più lungo prefisso di l per
 * cui nessun suo carattere ha un carattere uguale nella posizione
 * corrispondente di r.
 *
 * Non considera l'eventualità che la malloc fallisca.
 *
 * ESEMPI (rappresentando le liste senza separare i caratteri, per compattezza):
 * (1) date l=[] e s=[], restituisce p=[]
 * (2) date l=[] e s=[p,i,p,p,o], restituisce p=[]
 * (3) date l=[p,i,p,p,o] e s=[], restituisce p=[p,i,p,p,o]
 * (4) date l=[p,i,p,p,o] e s=[p,i,p,p,o], restituisce p=[]
 * (5) date l=[s,u,p,e,r,p,i,p,p,o] e s=[p,l,u,t,o], restituisce p=[s,u,p,e,r,p,i,p,p,o]
 * (6) date l=[p,l,u,t,o] e s=[s,u,p,e,r,p,i,p,p,o], restituisce p=[p,l,u,t,o]
 * (7) date l=[s,u,p,e,r,p,i,p,p,o] e s=[p,i,p,p,o], restituisce p=[s,u], perché la p seguente è in comune
 * (8) date l=[p,i,p,p,o] e s=[s,u,p,e,r,p,i,p,p,o], restituisce p=[p,i], perché la p seguente è in comune
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_antiPrefix"
 * NOTA: questa funzione viene testata indipendentemente dal vostro main
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 */
List student_antiPrefix(List l, List r) {
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


/**
 * Invoca la funzione antiPrefix su alcuni casi a scelta per testarne la correttezza.
 * Se la funzione antiPrefix è corretta, come ultima cosa deve stampare "TEST PASSED\n".
 * Se invece la funzione non risulta corretta, deve stampare "TEST FAILED\n".
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_main"
 * NOTA: il main viene testato indipendentemente dalla vostra funzione antiPrefix
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 */
int student_main() {
    _Bool pass = 1;
    List l,r,p,e;

    l = buildList("CIAO");
    r = buildList("QUA");
    p = antiPrefix(l, r);
    e = buildList("CI");
    if (list_diff(p, e)) pass = 0;
    list_free(l);
    list_free(r);
    list_free(p);
    list_free(e);

    if (pass)
        student_printf("TEST PASSED\n");
    else student_printf("TEST FAILED\n");
    return 0;
}
