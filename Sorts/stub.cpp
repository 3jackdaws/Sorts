//
//  stub.cpp
//  Sorts
//
//  Created by Ian Murphy on 1/26/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include <iostream>
#include "Sorts.hpp"

int main(int argc, char ** argv)
{
    int n, i;
    if(argc == 2)
        n = atoi(argv[1]);
    else if(argc == 3)
        n = atoi(argv[1]), i = atoi(argv[2]);
    else
        n = 501, i = 10;
    Sorts sort(n, i);
    sort.BubbleSortBench();
    sort.FlaggedBubbleBench();
    sort.StraightSelectionBench();
    sort.LinearInsertionBench();
    sort.ShellSortBench();
    sort.HeapSortBench();
    return 0;
}
