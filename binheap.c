//
//  binheap.c
//  huffman
//
//  Created by ivan on 04.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdlib.h>
#include "binheap.h"

static BinTree *bheap[256];
static int heapSize = 0;

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int bubbleUp(int position)
{
    BinTree *temp;
    
    temp                    = bheap[parent(position)];
    bheap[parent(position)] = bheap[position];
    bheap[position]         = temp;
    
    return  parent(position);
}

void initBH(void)
{
    int i = 0;
    
    for (i = 0; i < 256; i++)
    {
        bheap[i] = (BinTree *)malloc(sizeof(BinTree));
        initBT(bheap[i], 0, 0);
    }
}

void addBH(int data, double key)
{
    int position = heapSize;
    
    if (heapSize == 256)
    {
        return;
    }
    
    initBT(bheap[position], data, key);
    
    while (bheap[parent(position)]->key > bheap[position]->key)
    {
        position = bubbleUp(position);
    }
    
    heapSize++;
}

void addNodeBH(BinTree *node)
{
    int position = heapSize;
    
    if (heapSize == 256)
    {
        return;
    }
    
    bheap[position] = node;
    
    while (bheap[parent(position)]->key > bheap[position]->key)
    {
        position = bubbleUp(position);
    }
    
    heapSize++;
}

int peekBH(void)
{
    if (!heapSize) { return -1; }
    
    return bheap[0]->data;
}

int minKey(int a, int b, int c)
{
    double minKey = 0;
    int minInd = 0;
    
    minInd = a;
    minKey = bheap[a]->key;
    
    if (b < heapSize)
    {
        minInd = bheap[b]->key < minKey ? b : minInd;
        minKey = bheap[minInd]->key;
    }
    
    if (c < heapSize)
    {
        minInd = bheap[c]->key < minKey ? c : minInd;
    }
    
    return minInd;
}

int deleteMinBH(BinTree **minimum)
{
    int position = 0, smallest = 0;
    BinTree *temp, *min;
    
    if (!heapSize) { return 0; }
    
    min = bheap[0];
    bheap[0] = bheap[heapSize - 1];
    bheap[heapSize - 1] = min;
    
    heapSize--;
    
    bheap[heapSize] = NULL;
    
    if (!heapSize) { *minimum = min; return 1; }
    
    smallest = minKey(position, left(position), right(position));
    
    while ((left(position) < heapSize || right(position) < heapSize) && smallest != position)
    {
        temp            = bheap[position];
        bheap[position] = bheap[smallest];
        bheap[smallest] = temp;
        
        position = smallest;
        
        smallest = minKey(position, left(position), right(position));
    }
    
    *minimum = min;
    
    return 1;
}
