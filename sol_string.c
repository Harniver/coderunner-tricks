#include "list.h"

/* INSERIRE QUI EVENTUALI ALTRI #include <...> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  INSERIRE QUI EVENTUALI FUNZIONI AUSILIARIE (CON UN COMMENTO SIGNIFICATIVO IN TESTA) */

List cons(char head, List tail) {
    List l = malloc(sizeof(ListNode));
    l->data = head;
    l->next = tail;
    return l;
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
 * Data una stringa s, restituisce una lista di caratteri che contiene tutti
 * e soli i caratteri alfabetici maiuscoli (A - Z) trasformati in minuscoli
 * (a - z) della stringa s nell'ordine in cui occorrono in s.
 *
 * Non considera l'eventualità che la malloc fallisca.
 * Se s == NULL, restituisce NULL.
 *
 * ESEMPI (rappresentando le liste senza separare i caratteri, per compattezza):
 * (1) data s == NULL  restituisce NULL
 * (2) data s == "" restituisce NULL
 * (3) data s == "A" restituisce [a]
 * (4) data s == "AZbCuu12R" restituisce [a,z,c,r]
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_stringToList"
 * NOTA: questa funzione viene testata indipendentemente dal vostro main
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 */
List student_stringToList(char *s) {
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


/**
 * Invoca la funzione stringToList su alcuni casi a scelta per testarne la correttezza.
 * Se la funzione stringToList è corretta, come ultima cosa deve stampare "TEST PASSED\n".
 * Se invece la funzione non risulta corretta, deve stampare "TEST FAILED\n".
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_main"
 * NOTA: il main viene testato indipendentemente dalla vostra funzione stringToList
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 */
int student_main() {
    char *str = "Coordination@DisCoTec-2025";
    List lst = stringToList(str);
    List exp = cons('c', cons('d', cons('c', cons('t', NULL))));

    _Bool pass = 1;
    if (list_diff(lst, exp)) pass = 0;
    list_free(lst);
    list_free(exp);

    if (pass)
        student_printf("TEST PASSED\n");
    else student_printf("TEST FAILED\n");

    return 0;
}
