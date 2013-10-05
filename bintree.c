//
//  bintree.c
//  huffman
//
//  Created by ivan on 05.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include "bintree.h"
#include <stdlib.h>

int initBT(BinTree *node, int data, double key)
{
    node->left = node->right = NULL;
    node->data = data; node->key = key;
    
    return 1;
}

void releaseBT(BinTree *node)
{
    if (!node)
    {
        return;
    }
    if (!node->left && !node->right)
    {
        free(node);
        return;
    }
    releaseBT(node->right);
    releaseBT(node->left);
}