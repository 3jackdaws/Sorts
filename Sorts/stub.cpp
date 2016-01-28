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
        n = atoi(argv[1]), i = 10;
    else if(argc == 3)
        n = atoi(argv[1]), i = atoi(argv[2]);
    else
        n = 501, i = 10;
    std::cout<<"By default, this program does 10 iterations of a sorting algorith and averages the times.  If you put in a lot of elements, you might want to specify a fewer amount of iterations.\n\n"<<
        "Enter arguments in the form: ./Sorts [number of elements] [number of iterations]"<<std::endl;;
    if(n>500)
    {
        Sorts sort(n, i);
        sort.BubbleSortBench();
        sort.FlaggedBubbleBench();
        sort.StraightSelectionBench();
        sort.LinearInsertionBench();
        sort.ShellSortBench();
        sort.HeapSortBench();
        
        sort.MergeSortBench();
        sort.QuickSortBench();
    }
    else
    {
        std::cout<<"You must enter more than 500 elements."<<std::endl;
    }
    
    return 0;
}
