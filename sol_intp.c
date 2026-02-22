/* INSERIRE QUI EVENTUALI ALTRI #include <...> */
/* INSERT HERE MORE #include <...> IF NEEDED */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* INSERIRE QUI EVENTUALI FUNZIONI AUSILIARIE */
/* INSERT HERE AUXILIARY FUNCTIONS IF NEEDED */

/**
 * @brief Converte una stringa in intero (data la base).
 *
 * Calcola il numero intero rappresentato dalla stringa `s` nella base `b` (tra 2 e 36):
 * − saltando gli eventuali spazi bianchi iniziali;
 * − riconoscendo l'eventuale (singolo) carattere del segno (+ o -);
 * − fermandosi al raggiungimento del primo carattere non cifra nella base data (le cifre per la base 36 sono: 0,..,9,A,..,Z);
 * - deve essere presente almeno una cifra nella base data.
 *
 * Restituisce:
 * - 0 se uno degli argomenti non è valido, e in tal caso il valore in salvato in `r` non è significativo;
 * - altrimenti, il numero di caratteri letti dalla stringa, salvando in `r` il risultato.
 *
 * Non si accorge di eventuali overflow numerici (restituendo in questo caso un risultato scorretto).
 *
 * @param s una stringa da convertire.
 * @param b la base (tra 2 e 36).
 * @param r l'indirizzo dell'intero dove memorizzare il risultato.
 * @return  il numero di caratteri letti dalla stringa
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_stoub"
 * NOTA: questa funzione viene testata indipendentemente dal vostro main
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 *
 * <ENGLISH VERSION>
 *
 * @brief Converts a string to an integer (given the base).
 *
 * Computes the integer represented by the string `s` in base `b` (between 2 and 36):
 * - skipping any leading whitespace;
 * - recognizing an optional (single) sign character (+ or -);
 * - stopping at the first character that is not a valid digit in the given base (the digits for base 36 are: 0,..,9,A,..,Z);
 * - at least one digit in the given base must be present.
 *
 * Returns:
 * - 0 if one of the arguments is invalid, and in that case the value stored in `r` is not meaningful;
 * - otherwise, the number of characters read from the string, storing the result in `r`.
 *
 * It does not detect possible numeric overflows (returning an incorrect result in that case).
 *
 * @param s a string to convert.
 * @param b the base (between 2 and 36).
 * @param r the address of the integer where the result is stored.
 * @return  the number of characters read from the string
 *
 * NOTE: this function appears in compilation errors as "student_stoub"
 * NOTE: this function is tested independently of your main
 * IMPORTANT: always try to make your code compile so that you can see the test
 * results, even if that means commenting out part of the code of this function
 */
int student_stoub(char *s, unsigned short b, int *r) {
    /* INSERIRE QUI IL CODICE */
    /* INSERT YOUR CODE HERE */
    if (s==NULL || b<2 || b >36 || r==NULL) return 0;
    int sign = 1;
    int num = 0;
    int ret = 0;
    int i = 0;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') i++;
    if (s[i] == '-') {
        i++;
        sign = -1;
    } else if (s[i] == '+') i++;
    char ld = b > 9 ? '0' + 10 : '0' + b;
    char la = 'A' + b - 10;
    while (s[i] != '\0' && ((s[i] >= '0' && s[i] < ld) || (s[i] >= 'A' && s[i] < la))) {
        int c = s[i]<ld ? s[i]-'0' : 10+s[i]-'A';
        num = (num * b) + c;
        i++;
        ret = 1;
    }
    (*r) = sign*num;
    return ret ? i : 0;
}


/**
 * Invoca la funzione stoub su uno o più casi a scelta, controllando che
 * il suo effetto come risultato e argomenti rispetti la specifica corretta.
 * Può essere sufficiente anche un unico caso, se sufficientemente generale per
 * individuare quali programmi sono corretti e quali no.
 * Se la funzione è corretta, come ultima cosa deve stampare "TEST PASSED\n".
 * Se invece la funzione non risulta corretta, deve stampare "TEST FAILED\n".
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_main"
 * NOTA: il main viene testato indipendentemente dalla vostra funzione stoub
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 *
 * <ENGLISH VERSION>
 *
 * Invokes the stoub function on one or more selected test cases, checking
 * that its effect as result and arguments respects the correct specification.
 * A single test case may be enough, if it sufficiently general to single out
 * which programs are correct and which are not.
 * If the function is correct, as the final step it must print "TEST PASSED\n".
 * If instead the function is not correct, it must print "TEST FAILED\n".
 *
 * NOTE: this function appears in compilation errors as "student_main"
 * NOTE: the main is tested independently of your stoub function
 * IMPORTANT: always try to make your code compile so that you can see the test
 * results, even if that means commenting out part of the code of this function
 */
int student_main() {
    /* INSERIRE QUI IL CODICE */
    /* INSERT YOUR CODE HERE */
    int r;
    _Bool pass = (stoub("  -1C", 16, &r) == 5);
    if (r != -28) pass = 0;
    if (stoub("0", 50, &r) > 0) pass = 0;
    if (stoub("+-0", 10, &r) > 0) pass = 0;

    if (pass)
        printf("TEST PASSED\n");
    else printf("TEST FAILED\n");

    return 0;
}
