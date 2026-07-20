#ifndef __DATA_C
#define __DATA_C
#include "data.h"

#if __DATA == __CHAR
    #define __data_f "%c"
    #define __data_r(x) x
    #define __data_rand() (48 + rand()%75)
#endif

#if __DATA == __INT
    #define __data_f "%d"
    #define __data_r(x) (int)(x <= '9' ? x - '0' : x <= 'Z' ? x - 'A' + 10 : x - 'a' + 10)
    #define __data_rand() (rand()%4 ? rand()%30+'a' : rand()%10+'0')
#endif

#if __DATA == __FLOAT
    #define __data_f "%f"
    #define __data_r(x) (x <= '9' ? x - '0' : x <= 'Z' ? x - 'A' + 10 : x - 'a' + 10)*0.025f
    #define __data_rand() (rand()%4 ? rand()%30+'a' : rand()%10+'0')
#endif

#endif
