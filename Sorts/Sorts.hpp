/************************************************************************
* Class: Sorts
*
* Purpose: This class implements several different sorting algorithms and allows for the benchmarking of each
*
* Manager functions:
* 	Sorts(int size, int iterations = 1);
		Constructs a Sort object with data structure size specified 
    ~Sorts();
		Dtor
	Sorts(const Sorts & cp);
		copy ctor
	Sorts & operator = (const Sorts & rhs);
		op =
Public methods:
    void BubbleSort(T & array);
		Takes a data structure with op [] overload and sorts it
    void FlaggedBubble(T &);
		Takes a data structure with op [] overload and sorts it
    void StraightSelection(T&);
		Takes a data structure with op [] overload and sorts it
    void LinearInsertion(T&);
		Takes a data structure with op [] overload and sorts it
    void ShellSort(T&);
		Takes a data structure with op [] overload and sorts it
    void HeapSort(T&);
		Takes a data structure with op [] overload and sorts it
    void MergeSort(T&);
		Takes a data structure with op [] overload and sorts it
    void QuickSort(T&);
		Takes a data structure with op [] overload and sorts it
    
    void BubbleSortBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void FlaggedBubbleBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void StraightSelectionBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void LinearInsertionBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void HeapSortBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void ShellSortBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void MergeSortBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    void QuickSortBench();
		Benchmarks the described method on random data and outputs the time to complete to console and output file
    
    bool SortedCorrectly(T & array);
		Checks to see if the passed data structure is correcly sorted

*************************************************************************/

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
	Sorts(const Sorts & cp);
	Sorts & operator = (const Sorts & rhs);
    
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
