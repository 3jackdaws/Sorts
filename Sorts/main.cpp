//
//  main.cpp
//  Sorts
//
//  Created by Ian Murphy on 1/20/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <chrono>
#include "Sorts.hpp"


int main(int argc, const char * argv[])
{
    Sorts sort("output.txt", 100, 1000);
//    sort.BubbleSort();
//    sort.FlaggedBubble();
//    sort.StraightSelection();
//    sort.LinearInsertion();
//    sort.ShellSort();
    sort.HeapSort();
    
   
    return 0;
}
