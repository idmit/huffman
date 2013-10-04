//
//  main.c
//  huffman
//
//  Created by ivan on 25.09.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "util.h"

int main(int argc, const char * argv[])
{
    Argument *indicator = NULL;
    int anyOptGiven    = 0,
        argumentsGiven = 0;
    
    indicator = (Argument *)malloc((argc - 1) * sizeof(Argument));
    argumentsGiven = argc - 1;
    
    anyOptGiven = parseGArgs(argc, argv, indicator);
    
    if (!supportedArgsFormat(indicator, argumentsGiven, anyOptGiven))
    {
        return 1;
    }
    
    route(indicator, anyOptGiven);
    
    return 0;
}

