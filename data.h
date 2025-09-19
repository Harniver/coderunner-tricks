#ifndef __DATA_H
#define __DATA_H

#define __CHAR 0
#define __INT  1

#if __DATA == __CHAR
    #define __data_t char
#endif

#if __DATA == __INT
    #define __data_t int
#endif

#endif
