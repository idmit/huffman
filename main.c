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

int main(int argc, const char * argv[])
{
    Argument *indicator = NULL;
    
    indicator = (Argument *)malloc((argc - 1) * sizeof(int));
    
    printf("%d", parseGArgs(argc, argv, indicator));
    return 0;
}

