//
//  binheap.h
//  huffman
//
//  Created by ivan on 04.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef huffman_binheap_c
#define huffman_binheap_c

#include "bintree.h"

void initBH(void);
void addBH(int data, double key);
void addNodeBH(BinTree *node);
int peekBH(void);
int deleteMinBH(BinTree **minimum);

#endif
