#ifndef __LIST_H
#define __LIST_H
#include "data.h"

typedef struct listNode ListNode, *List;

struct listNode {
    __data_t data;
    List next;
};

#endif
