//
//  io.c
//  huffman
//
//  Created by ivan on 25.09.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include "io.h"

int parseGArgs(int argc, const char *argv[], Argument *indicator)
{
    int i           = 0,
        j = 0,
        anyOptGiven = 0;
    
    for (i = j = 0; i < argc - 1; i++, j++)
    {
        if (argv[i + 1][0] == '-') // i + 1 here ignores first argument (app name)
        {
            indicator[j].isOption = 1;
            indicator[j].self     = argv[i + 1] + 1; // + 1 here ignores '-' in option
            indicator[j].subArg   = argv[i + 2];
            i++; // ignores subarg in next iteration
            anyOptGiven = 1;
        }
        else
        {
            indicator[j].isOption = 0;
            indicator[j].self     = argv[i + 1];
            indicator[j].subArg   = 0;
        }
    }
    
    return anyOptGiven;
}

int supportedArgsFormat(Argument *indicator, int argsGiven, int anyOptGiven)
{
    if (anyOptGiven)
    {
        if (argsGiven != 5 || indicator[0].isOption || !indicator[1].isOption || !indicator[1].subArg || indicator[2].isOption || indicator[3].isOption)
        {
            return 0;
        }
    }
    else
    {
        if (argsGiven != 3 || indicator[0].isOption || indicator[1].isOption || indicator[2].isOption)
        {
            return 0;
        }
    }
    
    return 1;
}

int tryReadHex(char *string, int *wasHex, char **endOfHex)
{
    unsigned long num  = 0;
    char *numberItself = NULL,
         hexBegin[]    = "\\x";
    
    *wasHex = 0;
    
    if (strcmp(string, hexBegin))
    {
        numberItself = string + 2;
        num = strtoul(numberItself, endOfHex, 16);
        if (*endOfHex != numberItself) { *wasHex = 1; }
    }
    
    return (int)num;
}

void writeHex(FILE *stream, unsigned long num)
{
    fprintf(stream, "\\x%x", (unsigned int)num);
}

void printBinary(FILE *stream, long num)
{
    int i          = 0,
    printedOne = 0;
    
    if (!num)
    {
        fprintf(stream, "0");
        return;
    }
    
    for (i = 0; i < 7; i++)
    {
        if (num & 64L) { printf("1"); printedOne = 1; } else { if (printedOne) { printf("0"); } }
        num <<= 1;
    }
}