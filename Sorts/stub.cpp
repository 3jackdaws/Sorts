/*************************************************************
* Author:		Ian Murphy
* Filename:		stub.cpp
* Date Created:	1/25ish/2016
* Modifications:	Check github
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Lab 2 – Sorting Algorithms
*
* Overview:
*	This program will create a specified size array of random data
	and sort it with eight different sorting algoritms.  It will
	then output the time that the sorting algorithms took to
	complete to the console and the output file

*
* Input:
*	The input consists of the number of elements to be randomly 
	generated and sorted, and the number of times that data should 
	be copied and resorted.
*
* Output:
*	The program will output the time taken by each algorithm and data 
	structure to correctly sort the sepecified number of elements.	
	If told to, the program will run each sort multiple times and average 
	the times.  This makes the benchmark more accurate, but slower.
*
************************************************************/


#include <iostream>
#include "Sorts.hpp"

int main(int argc, char ** argv)
{
    int n, i;
    if(argc == 2)
        n = atoi(argv[1]), i = 1;
    else if(argc == 3)
        n = atoi(argv[1]), i = atoi(argv[2]);
    else
        n = 1000, i = 10;
    std::cout<<"This program has the ability to do several iterations of sorting the same numbers.\n\n"<<
        "Enter arguments in the form: ./Sorts [number of elements] [number of iterations]"<<std::endl;;
    Sorts sort(n, i);
    sort.BubbleSortBench();
    sort.FlaggedBubbleBench();
    sort.StraightSelectionBench();
    sort.LinearInsertionBench();
    sort.ShellSortBench();
    sort.HeapSortBench();
    sort.MergeSortBench();
    sort.QuickSortBench();
    
    
    return 0;
}
