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

void printBinaryCode(FILE *stream, BinCode code)
{
    int i          = 0;
    long one = 1;
    
    one = one << (code.length - 1);
    
    for (i = 0; i < code.length; i++)
    {
        if (code.self & one) { printf("1"); } else { printf("0"); }
        code.self <<= 1;
    }
}

void archiveWithCodes(BinCode *codes, const char *inputName, const char *outputName)
{
    FILE *input = NULL, *output = NULL;
    int sym = 0, fit = 0, i = 0, bitsOfUL= sizeof(unsigned long) * 8;
    unsigned long bitsWritten = 0;
    BinCode code = {0}, buff = {0}, leftOver = {0};
    
    if (!(input = fopen(inputName, "r")))
    {
        return;
    }
    if (!(output = fopen(outputName, "w")))
    {
        return;
    }
    
    while ((sym = getc(input)) != EOF)
    {
        code = codes[sym];
        if (leftOver.length)
        {
            buff = leftOver;
            leftOver.self = leftOver.length = 0;
        }
        if (buff.length + code.length <= bitsOfUL)
        {
            buff.self = buff.self << code.length;
            buff.self = buff.self | code.self;
            buff.length += code.length;
        }
        else
        {
            fit = bitsOfUL - buff.length;
            buff.self = buff.self << fit;
            i = fit;
            buff.self = buff.self | (code.self >> (code.length - fit));
            buff.length += fit;
            fwrite(&buff.self, sizeof(unsigned long), 1, output);
            bitsWritten += bitsOfUL;
            buff.self = buff.length = 0;
            leftOver.length = code.length - fit;
            leftOver.self = (code.self << (bitsOfUL - code.length + fit)) >> (bitsOfUL - code.length + fit);
        }
    }
    if (buff.length)
    {
        buff.self <<= (bitsOfUL - buff.length);
        fwrite(&buff.self, sizeof(unsigned long), 1, output);
        bitsWritten += buff.length;
    }
    if (leftOver.length)
    {
        leftOver.self <<= (bitsOfUL - leftOver.length);
        buff = leftOver;
        fwrite(&buff.self, sizeof(unsigned long), 1, output);
        bitsWritten += leftOver.length;
    }
    fwrite(&bitsWritten, sizeof(unsigned long), 1, output);

    
    fclose(input);
    fclose(output);
}

void extractWithTree(BinTree *huffTree, const char *inputName, const char *outputName)
{
    FILE *input = NULL, *output = NULL;
    int bitsOfUL= sizeof(unsigned long) * 8;
    int i = 0;
    unsigned long bitsWritten = 0, bitsReaded = 0, mask = 0, buff = 0;
    BinTree *node = NULL;
    
    node = huffTree;
    
    if (!(input = fopen(inputName, "r")))
    {
        return;
    }
    if (!(output = fopen(outputName, "w")))
    {
        return;
    }
    
    fseek(input, - sizeof(unsigned long), SEEK_END);
    fread(&bitsWritten, sizeof(unsigned long), 1, input);
    rewind(input);
    
    mask = 1L << (bitsOfUL - 1);
    while (bitsReaded != bitsWritten)
    {
        fread(&buff, sizeof(unsigned long), 1, input);
        for (i = 0; i < bitsOfUL; i++)
        {
            node = !!(buff & mask) ? node->right : node->left;

            if (isLeaf(node))
            {
                putc(node->data, output);
                node = huffTree;
            }
            bitsReaded += 1;
            if (bitsReaded == bitsWritten)
            {
                break;
            }
            buff <<= 1;
        }
    }
    
    
    fclose(input);
    fclose(output);
}

