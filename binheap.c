//
//  binheap.c
//  huffman
//
//  Created by ivan on 04.10.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include "binheap.h"

typedef struct Pair
{
    double key; // always positive frequency
    int data;
} Pair;

static Pair bheap[256]; // ascii codes
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
    Pair temp;
    
    temp                    = bheap[parent(position)];
    bheap[parent(position)] = bheap[position];
    bheap[position]         = temp;
    
    return  parent(position);
}

void addBH(int data, double key)
{
    int position = heapSize;
    
    if (heapSize == 256)
    {
        return;
    }
    
    bheap[position].key  = key;
    bheap[position].data = data;
    
    while (bheap[parent(position)].key > bheap[position].key)
    {
        position = bubbleUp(position);
    }
    
    heapSize++;
}

int peekBH(void)
{
    if (!heapSize) { return -1; }
    
    return bheap[0].data;
}

int minKey(int a, int b, int c)
{
    double minKey = 0;
    int minInd = 0;
    
    minInd = a;
    minKey = bheap[a].key;
    
    if (b < heapSize)
    {
        minInd = bheap[b].key < minKey ? b : minInd;
        minKey = bheap[minInd].key;
    }
    
    if (c < heapSize)
    {
        minInd = bheap[c].key < minKey ? c : minInd;
    }
    
    return minInd;
}

int deleteMinBH(void)
{
    int position = 0, smallest = 0;
    Pair temp, min;
    
    if (!heapSize) { return -1; }
    
    min = bheap[0];
    bheap[0] = bheap[heapSize - 1];
    bheap[heapSize - 1] = min;
    
    heapSize--;
    
    bheap[heapSize].data = bheap[heapSize].key = 0;
    
    smallest = minKey(position, left(position), right(position));
    
    while ((left(position) < heapSize || right(position) < heapSize) && smallest != position)
    {
        temp            = bheap[position];
        bheap[position] = bheap[smallest];
        bheap[smallest] = temp;
        
        position = smallest;
        
        smallest = minKey(position, left(position), right(position));
    }
    
    return min.data;
}
