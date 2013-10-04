//
//  io.h
//  huffman
//
//  Created by ivan on 25.09.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef huffman_io_c
#define huffman_io_c

#include <stdio.h>

typedef struct Argument
{
    int isOption;
    const char *self;
    const char *subArg;
}   Argument;

int parseGArgs(int argc, const char *argv[], Argument *indicator);

unsigned long tryReadHex(char *string, int *wasHex);
void writeHex(FILE *stream, unsigned long num);

#endif
