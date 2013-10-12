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

/* Argument string to the program */

typedef struct Argument
{
    int isOption;
    const char *self;
    const char *subArg;
}   Argument;

/* Parse program arguments and write all the information by given address */
int parseGArgs(int argc, const char *argv[], Argument *indicator);

/* Test if given arguments are supported by the program */
int supportedArgsFormat(Argument *indicator, int argsGiven, int anyOptGiven);

/* Try to read hex from string. On success set wasHex and write hex's end by given address */
int tryReadHex(char *string, int *wasHex, char **endOfHex);

/* Write hex to the stream */
void writeHex(FILE *stream, unsigned long num);

/* Print binary code to the stream */
void printBinaryCode(FILE *stream, BinCode code);

/* Decode input file using given huffman tree and write result to output */
void extractWithTree(BinTree *huffTree, const char *inputName, const char *outputName);

/* Encode input file with given codes for chars and write result to output */
void archiveWithCodes(BinCode *codes, const char *inputName, const char *outputName);

#endif
