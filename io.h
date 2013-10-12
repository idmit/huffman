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
#include "bintree.h"
#include "bincode.h"

typedef struct Argument
{
    int isOption;
    const char *self;
    const char *subArg;
}   Argument;

int parseGArgs(int argc, const char *argv[], Argument *indicator);
int supportedArgsFormat(Argument *indicator, int argsGiven, int anyOptGiven);

int tryReadHex(char *string, int *wasHex, char **endOfHex);
void writeHex(FILE *stream, unsigned long num);
void printBinaryCode(FILE *stream, BinCode code);
void extractWithTree(BinTree *huffTree, const char *inputName, const char *outputName);

void archiveWithCodes(BinCode *codes, const char *inputName, const char *outputName);

#endif
