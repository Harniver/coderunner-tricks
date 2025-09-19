#ifndef __DATA_C
#define __DATA_C
#include "data.h"

#if __DATA == __CHAR
    #define __data_f "%c"
    #define __data_r(x) x
    #define __data_rand() (65 + rand()%26 + 32*(rand()%2))
#endif

#if __DATA == __INT
    #define __data_f "%d"
    #define __data_r(x) (int)(x <= '9' ? x - '0' : x <= 'Z' ? x - 'A' + 10 : x - 'a' + 10)
    #define __data_rand() (rand()%4 ? rand()%30+'a' : rand()%10+'0')
#endif

#endif
