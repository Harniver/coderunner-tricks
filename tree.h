#ifndef __TREE_H
#define __TREE_H
#include "data.h"

typedef struct treeNode TreeNode, *Tree;

struct treeNode {
    Tree left;
    __data_t data;
    Tree right;
};

#endif
