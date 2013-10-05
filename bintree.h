//
//  bintree.h
//  huffman
//
//  Created by ivan on 05.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef huffman_bintree_c
#define huffman_bintree_c

typedef struct BinTree
{
    double key; // always positive frequency
    int data;
    struct BinTree *left;
    struct BinTree *right;
} BinTree;

int initBT(BinTree *node, int data, double key);
void releaseBT(BinTree *node);

#endif
