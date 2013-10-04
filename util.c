//
//  util.c
//  huffman
//
//  Created by ivan on 25.09.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <string.h>
#include "util.h"

int route(Argument *indicator, int anyOptionsGiven)
{
    int table = 0;
    
    if (anyOptionsGiven)
    {
        table = table;//load table
    }
    
    if (strcmp(indicator[1].self, "a"))
    {
        ;
        //huffman
    }
    else if (strcmp(indicator[1].self, "x"))
    {
        
    }
    else if (strcmp(indicator[1].self, "h"))
    {
        //help
    }
    else
    {
        //error;
    }
    
    return 0;
}