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

/* Allocate and set memory for 256 elements of the heap */
void initBH(void);

/* Add an element with given props to the heap */
void addBH(int data, double key);

/* Add given node to the heap */
void addNodeBH(BinTree *node);

/* Peek data of the element with the smallest key in the heap */
int peekBH(void);

/* Write the element with the smallest key by given address and delete it from the heap  */
int deleteMinBH(BinTree **minimum);

#endif
