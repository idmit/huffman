//
//  util.c
//  huffman
//
//  Created by ivan on 25.09.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include "bintree.h"
#include "binheap.h"
#include "bincode.h"
#include "util.h"

/* Read  file with chars probabilities and add those pairs to the heap on success */
static int readTable(char *tableName);

/* Build huffman codes (tree actually) based on information from the heap */
static int buildHuffCodes(BinCode *codes, BinTree **huffTree);

/* Build huffman codes based on tree */
static void _getCodesFromTree(BinTree *tree, BinCode *codes, long path, int length);

/* Wrapper for recursive function with few unnecessary arguments removed */
static void getCodesFromTree(BinTree *tree, BinCode *codes);

/* Test if given arguments are supported by the command */
static int supportedArgsFormat(Argument *indicator, int argsGiven, int anyOptGiven, int command);

int route(Argument *indicator, int argumentsGiven, int anyOptionsGiven)
{
    /* Name of file with probabilities for different chars */
    char *tableName = NULL;
    
    /* Huffman binary tree built with information from <tableName> */
    BinTree *huffTree = NULL;
    
    /* Chars codes built by <huffTree> */
    BinCode codes[256];
    
    /* I can't work with NULL */
    if (!indicator)
    {
        return 0;
    }
    
    if (anyOptionsGiven)
    {
        /* Setting string given under -t program option for a table name */
        tableName = (char *)indicator[1].subArg;
    }
    
    /* If file with given name doesn't exist and default table was corrupted */
    /* Or file with given name holds corrupted table */
    if (!readTable(tableName))
    {
        return 0;
    }

    huffTree = malloc(sizeof(BinTree));
    initBT(huffTree, -1, 0);
    
    /* Choose what to do */
    if (!strcmp(indicator[0].self, "a"))
    {
        if (supportedArgsFormat(indicator, argumentsGiven, anyOptionsGiven, 'a'))
        {
            /* Build huffTree (all probabilities are in the binary heap) and then generate codes based on the tree */
            buildHuffCodes(codes, &huffTree);
            /* Write all the codes corresponding to text in given input to output*/
            archiveWithCodes(codes, indicator[anyOptionsGiven ? 2 : 1].self, indicator[anyOptionsGiven ? 3 : 2].self);
        }
    }
    else if (!strcmp(indicator[0].self, "x"))
    {
        if (supportedArgsFormat(indicator, argumentsGiven, anyOptionsGiven, 'x'))
        {
            /* Build huffTree (all probabilities are in the binary heap) and then generate codes based on the tree */
            buildHuffCodes(codes, &huffTree);
            /* Rebuild all the text corresponding to codes in given input to output */
            extractWithTree(huffTree, indicator[anyOptionsGiven ? 2 : 1].self, indicator[anyOptionsGiven ? 3 : 2].self);
        }
    }
    else if (!strcmp(indicator[0].self, "h"))
    {
        /* Print out usage instructions */
        if (supportedArgsFormat(indicator, argumentsGiven, anyOptionsGiven, 'h'))
        {
            printf("%s", "Usage:\n" //
                   "a [-t customTable] <input> <output> -- archive <input> file into <output> file.\n" //
                   "x [-t customTable] <input> <output> -- extract <input> file into <output> file.\n" //
                   "h -- help and usage.\n");
        }
    }
    else
    {
        /* Print out help guide */
        printf("%s", "See <h> for usage.\n");
    }
    
    /* Release all the memory */
    releaseBT(huffTree);
    
    return 1;
}

static int readTable(char *tablename)
{
    int wasHex  = 0,
        wasChar = 0,
        sym     = 0,
        defaultTable = 0,
        totalLines = 0;
    double freq = 0,
           probabiltyForUnmentioned = 0,
           freqs[256] = {0},
           sumFreq = 0;
    char *line     = NULL,
         *endOfHex = NULL;
    FILE *table = NULL;
    
    for (int i = 0; i < 256; i++)
    {
        freqs[i] = -1;
    }
    
    /* If table name isn't provided take default table instead */
    if (!tablename)
    {
        defaultTable = 1;
        tablename = (char *)malloc(50 * sizeof(char));
        strcpy(tablename, "/Users/ivan/ftable.txt");
    }
    
    table = fopen(tablename, "r");
    
    /* If there is no table file - die */
    if (!table)
    {
        return 0;
    }
    
    /* I think 20 chars are enough to hold a line with one char actual char and a double number */
    line = (char *)malloc(20 * sizeof(char));
    
    /* Initialize binary heap for building huffman tree */
    initBH();
    
    /* For every line in the file */
    while (fscanf(table, "%[^\n]\n", line) != EOF)
    {
        sym = tryReadHex(line, &wasHex, &endOfHex);
        if (!wasHex)
        {
            sym = tryReadChar(line, &wasChar);
            if (wasChar)
            {
                /* Char is (surprisingly) one char in length */
                endOfHex = line + 1;
            }
            else
            {
                /* We expected a char or a hex there - die */
                return 0;
            }
        }
        
        /* Read from where we stopped */
        freq = strtod(endOfHex, NULL);
        
        /* If there already was a line declaring <sym> probability - die. It isn't  supported. */
        if (freqs[sym] != -1)
        {
            return 0;
        }
        
        /* If it's a first line declaring <sym> probability, record it */
        freqs[sym] = freq;
        
        /* And add it to the summary of declared probabilities */
        sumFreq += freq;
        
        /* Add <sym> and its probsbility to the heap */
        addBH(sym, freq);
        
        totalLines += 1;
    }
    
    /* If some char wasn't declared in the file, then its probability is calculated like following */
    if (totalLines < 256)
    {
        if (sumFreq >= 1)
        {
            probabiltyForUnmentioned = 0.00001;
        }
        freq = (1 - sumFreq + probabiltyForUnmentioned) / (256 - totalLines);
        for (sym = 0; sym < 256; sym++)
        {
            if (freqs[sym] == -1)
            {
                addBH(sym, freq);
            }
        }
    }
    
    /* Free up all resources. Note that there is an initiated binary heap, so some memory is still occupied */
    free(line);
    fclose(table);
    if (defaultTable) { free(tablename); }
    
    return 1;
}

int supportedArgsFormat(Argument *indicator, int argsGiven, int anyOptGiven, int command)
{
    switch (command)
    {
        case 'a':
        case 'x':
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
            
            break;
        case 'h':
            if (argsGiven != 1)
            {
                return 0;
            }
            break;
        default:
            break;
    }
    
    return 1;
}

static void _getCodesFromTree(BinTree *tree, BinCode *codes, long path, int length)
{
    /*
     Choose left child and your path will be continued with 0.
     Choose right child and your path will be continued with 1.
     Every leaf will eventually have <path> representing an actual path from root to it.
     */
    if (tree->left)
    {
        _getCodesFromTree(tree->left, codes, path << 1, length + 1);
    }
    if (tree->right)
    {
        _getCodesFromTree(tree->right, codes, (path << 1) + 1, length + 1);
    }
    if (!tree->left && !tree->right)
    {
        /* Set code for symbol, which is data current leaf */
        codes[tree->data].self = path;
        codes[tree->data].length = length;
    }
}

static void getCodesFromTree(BinTree *tree, BinCode *codes)
{
    _getCodesFromTree(tree, codes, 0L, 0);
}

static int buildHuffCodes(BinCode codes[256], BinTree **huffTree)
{
    int i = 0;
    BinTree *min1     = NULL,
            *min2     = NULL,
            *combined = NULL;
    
    /*
     For every pair of min elements deleted from binary heap, there is another element (new one) back on the heap.
     So for 256 elements on the heap, I can do this 255 times, lefting on the heap only one desired element.
     */
    for (i = 0; i < 256 - 1; i++)
    {
        if (!deleteMinBH(&min1))
        {
            /* I should be able to do this within 255 iterations, so otherwise - die */
            return 0;
        }
        if (!deleteMinBH(&min2))
        {
            /* I should be able to do this within 255 iterations, so otherwise - die */
            return 0;
        }
        
        /* Create a new element, which becomes parent to both mins */
        combined = malloc(sizeof(BinTree));
        initBT(combined, -1, min1->key + min2->key);
        combined->left = min1; combined->right = min2;
        
        /* Add it to the heap */
        addNodeBH(combined);
    }
    
    /* 
     Delete the final desired element.
     It is parent for every element from the heap, so all allocated memory is linked to it.
     To free up resources, just release this tree.
     */
    deleteMinBH(huffTree);
    
    /* Build codes based on huffman tree */
    getCodesFromTree(*huffTree, codes);
    
    /* Print out built codes for debugging purposes */
    for (i = 0; i < 256; i++)
    {
        printf("%c ", i);
        printBinaryCode(stdout, codes[i]);
        printf("\n");
    }
    
    return 1;
}