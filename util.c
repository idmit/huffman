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
#include "util.h"

int archive(void);

int route(Argument *indicator, int anyOptionsGiven)
{
    char *tablename = 0;
    
    tablename = NULL;
    
    if (anyOptionsGiven)
    {
        tablename = (char *)indicator[1].subArg;
    }
    
    readTable(tablename);
    
    if (strcmp(indicator[0].self, "a"))
    {
        //huffman
    }
    else if (strcmp(indicator[0].self, "x"))
    {
        
    }
    else if (strcmp(indicator[0].self, "h"))
    {
        //help
    }
    else
    {
        //error;
    }
    
    return 0;
}

int readTable(char *tablename)
{
    int wasHex = 0,
        sym    = 0,
        defaultTable = 0;
    double freq = 0;
    char *line     = NULL,
         *endOfHex = NULL;
    FILE *table = NULL;
    
    if (!tablename)
    {
        defaultTable = 1;
        tablename = (char *)malloc(50 * sizeof(char));
        strcpy(tablename, "/Users/ivan/ftable.txt");
    }
    
    table = fopen(tablename, "r");
    
    line = (char *)malloc(20 * sizeof(char));
    
    initBH();
    
    while (fscanf(table, "%[^\n]\n", line) != EOF)
    {
        sym = tryReadHex(line, &wasHex, &endOfHex);
        freq = strtod(endOfHex, NULL);
        addBH(sym, freq);
    }
    
    free(line);
    fclose(table);
    if (defaultTable) { free(tablename); }
    
    return 1;
}

int archive(void)
{
    int i = 0;
    BinTree *min1     = NULL,
            *min2     = NULL,
            *combined = NULL,
            *code     = NULL;
    
    for (i = 0; i < 255; i++)
    {
        if (!deleteMinBH(&min1))
        {
            return 0;
        }
        if (!deleteMinBH(&min2))
        {
            return 0;
        }
        
        combined = malloc(sizeof(BinTree));
        initBT(combined, -1, min1->key + min2->key);
        combined->left = min1; combined->right = min2;
        
        addNodeBH(combined);
    }
    
    deleteMinBH(&code);
    
    return 1;
}