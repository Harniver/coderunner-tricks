#ifndef __ID_LIST_H
#define __ID_LIST_H

#include "data.h"

typedef struct listNode ListNode, *List;

struct listNode {
    int id;
    __data_t data;
    List next;
};

#endif
