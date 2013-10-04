//
//  io.c
//  huffman
//
//  Created by ivan on 25.09.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include "io.h"

int parseGArgs(int argc, const char *argv[], Argument *indicator)
{
    int i           = 0,
        anyOptGiven = 0;
    
    for (i = 0; i < argc - 1; i++)
    {
        if (argv[i + 1][0] == '-') // i + 1 here ignores first argument (app name)
        {
            indicator[i].isOption = 1;
            indicator[i].self     = argv[i + 1] + 1; // + 1 here ignores '-' in option
            indicator[i].subArg  = argv[i + 2];
            i++; // ignores subarg in next iteration
            anyOptGiven = 1;
        }
        else
        {
            indicator[i].isOption = 0;
            indicator[i].self     = argv[i + 1];
            indicator[i].subArg  = 0;
        }
    }
    
    return anyOptGiven;
}