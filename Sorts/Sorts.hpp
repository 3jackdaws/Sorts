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
using std::cout;
#include <vector>
#include <fstream>
#include "Array.h"
#include <chrono>
using time_point = std::chrono::steady_clock::time_point;



class Sorts
{
public:
    Sorts(int size, int iterations = 1);
    ~Sorts();
    
    template <typename T>
    void BubbleSort(T & array);

    template <typename T>
    void FlaggedBubble(T &);
    
    template <typename T>
    void StraightSelection(T&);

    template <typename T>
    void LinearInsertion(T&);
    
    template <typename T>
    void ShellSort(T&);
    
    template <typename T>
    void HeapSort(T&);
    
    template <typename T>
    void MergeSort(T&);
    
    template <typename T>
    void QuickSort(T&);

    
    void BubbleSortBench();
    void FlaggedBubbleBench();
    void StraightSelectionBench();
    void LinearInsertionBench();
    void HeapSortBench();
    void ShellSortBench();
    void MergeSortBench();
    void QuickSortBench();
    
    template <typename T>
    bool SortedCorrectly(T & array);
private:
    template <typename T>
    void BuildHeap(T&);
    template <typename T>
    void Heapify(T&, int, int);
    
    template <typename T>
    void QuickSort(T&, int, int);
    
    template <typename T>
    void MergeSort(T & array, int * temp, int left, int right);
    
    template <typename T>
    void Merge(T & array, int * temp, int left, int right, int right_end);
    
    template <typename T>
    void Display(T & array);
    
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
