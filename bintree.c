//
//  bintree.c
//  huffman
//
//  Created by ivan on 05.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include "bintree.h"
#include <stdlib.h>

void initBT(BinTree *node, int data, double key)
{
    /* Children are set to NULL */
    node->left = node->right = NULL;
    
    /* Applying given args */
    node->data = data; node->key = key;
}

void releaseBT(BinTree *node)
{
    /* I can't free NULL */
    if (!node) { return; }
    
    /* Release children. NULL-childproof */
    releaseBT(node->left);
    releaseBT(node->right);
    
    /* Actually releasing memory */
    free(node);
}

int isLeaf(BinTree *node)
{
    if (node->right || node->left)
    {
        return 0;
    }
    return 1;
}