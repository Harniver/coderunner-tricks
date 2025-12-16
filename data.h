#ifndef __DATA_H
#define __DATA_H

#define __CHAR  0
#define __INT   1
#define __FLOAT 2

#if __DATA == __CHAR
    #define __data_t char
#endif

#if __DATA == __INT
    #define __data_t int
#endif

#if __DATA == __FLOAT
    #define __data_t float
#endif

#endif
