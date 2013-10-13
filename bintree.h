//
//  bintree.h
//  huffman
//
//  Created by ivan on 05.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef huffman_bintree_c
#define huffman_bintree_c

/* Char code and its non negative frequency */

typedef struct BinTree
{
    double key;
    int data;
    struct BinTree *left;
    struct BinTree *right;
} BinTree;

/* Initialize BinTree with given args and set children to NULL */
void initBT(BinTree *node, int data, double key);

/* Test if given node is a leaf */
int isLeaf(BinTree *node);

/* Recursively release memory occupied by node and its children */
void releaseBT(BinTree *node);

#endif
