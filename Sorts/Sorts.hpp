//
//  Sorts.hpp
//  Sorts
//
//  Created by Ian Murphy on 1/22/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef Sorts_hpp
#define Sorts_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include "Array.h"
#include <chrono>
using time_point = std::chrono::steady_clock::time_point;


template <typename T, int S>
class carray_wrapper
{
public:
    carray_wrapper(T arr[])
    {
        for(int i = 0; i<S; i++)
        {
            _array[i] = arr[i];
        }
    }
    T & operator [] (int index)
    {
        return _array[index];
    }
private:
    T _array[S];
};


class Sorts
{
public:
    Sorts(const char * inputfile, int size, int iterations = 1);
    
    template <typename T>
    void BubbleSortC(T array);
    template <typename T>
    void BubbleSort(T & array);
    
    template <typename T>
    void FlaggedBubbleC(T);
    template <typename T>
    void FlaggedBubble(T &);
    
    template <typename T>
    void StraightSelectionC(T);
    template <typename T>
    void StraightSelection(T&);
    
    template <typename T>
    void LinearInsertionC(T);
    template <typename T>
    void LinearInsertion(T&);
    
    template <typename T>
    void ShellSortC(T);
    template <typename T>
    void ShellSort(T&);
    
    template <typename T>
    void HeapSortC(T);
    template <typename T>
    void HeapSort(T&);

    
    void BubbleSortBench();
    void FlaggedBubbleBench();
    void StraightSelectionBench();
    void LinearInsertionBench();
    void HeapSortBench();
    void ShellSortBench();
    
    bool SortedCorrectly();
private:
    template <typename T>
    void BuildHeap(T);
    
    template <typename T>
    void Heapify(T, int, int);
    
    void Display(int array);
    void Shuffle();
    void Init();
    
    int m_size;
    int m_interations;
    
   
    int * m_array;
    std::vector<int> m_vector;
    Array<int> m_myarray;
    
    std::ofstream m_outfile;
};

#endif /* Sorts_hpp */
