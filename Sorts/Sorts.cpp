//
//  Sorts.cpp
//  Sorts
//
//  Created by Ian Murphy on 1/22/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "Sorts.hpp"
Sorts::Sorts(int size, int iterations) : m_size(size), m_interations(iterations), m_outfile(std::ofstream("outfile.txt"))
{
//    m_outfile = std::ofstream("output.txt");
    m_array = new int[size];
    Init();
    Shuffle();
    m_outfile<<"Sorting "<<m_size<<" elements."<<std::endl;
}

Sorts::~Sorts()
{
    m_outfile.close();
    delete [] m_array;
}

void Sorts::Init()
{
    for (int i = 0; i<m_size; i++)
    {
        m_array[i] = i+100;
    }
}

void Sorts::Shuffle()
{
    srand(time(nullptr));
    for (int i = m_size-1; i>=0; i--) {
        int randn = rand()%m_size;
        int hold = m_array[i];
        m_array[i] = m_array[randn];
        m_array[randn] = hold;
    }
    m_vector = std::vector<int>(m_size);
    for (int i = 0; i<m_size; i++)
    {
        m_vector[i] = m_array[i];
    }
    m_myarray.setLength(m_size);
    for (int i = 0; i<m_size; i++)
    {
        m_myarray[i] = m_array[i];
    }
}

template <typename T>
void Sorts::Display(T & array)
{
    for (int i = 0; i<m_size; i++)
    {
        m_outfile<<array[i]<<std::endl;
    }
}


template <typename T>
void Sorts::BubbleSort(T & array)
{
    for (int i = 0; i<m_size; i++)
    {
        for (int ii = 0; ii<m_size - i -1; ii++)
        {
            if(array[ii] > array[ii + 1])
            {
                int hold = array[ii];
                array[ii] = array[ii+1];
                array[ii+1] = hold;
            }
        }
    }
}


void Sorts::BubbleSortBench()
{
    m_outfile<<"\n-------BRUTEFORCE BUBBLESORT--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        BubbleSort(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        BubbleSort(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        BubbleSort(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}


template <typename T>
void Sorts::FlaggedBubble(T & array)
{
    bool sorted = false;
    for (int i = 0; i<m_size && !sorted; i++)
    {
        sorted = true;
        for (int ii = 0; ii<m_size - i -1; ii++)
        {
            if(array[ii] > array[ii + 1])
            {
                sorted = false;
                int hold = array[ii];
                array[ii] = array[ii+1];
                array[ii+1] = hold;
            }
        }
    }
}

void Sorts::FlaggedBubbleBench()
{
    m_outfile<<"\n-------FLAGGED BUBBLESORT--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        FlaggedBubble(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        FlaggedBubble(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        FlaggedBubble(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}


template <typename T>
void Sorts::StraightSelection(T & array)
{
    for (int i = 0; i<m_size-1; i++)
    {
        int minimum = i;
        for (int ii = minimum+1; ii<m_size; ii++)
        {
            if(array[ii] < array[minimum])
            {
                minimum = ii;
            }
        }
        if(minimum != i)
        {
            int swap = array[i];
            array[i] = array[minimum];
            array[minimum] = swap;
        }
    }
    
}

void Sorts::StraightSelectionBench()
{
    m_outfile<<"\n-------STRAIGHT SELECTION--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        StraightSelection(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        StraightSelection(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        StraightSelection(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

template <typename T>
void Sorts::LinearInsertion(T & array)
{
    for (int i = 0; i<m_size-1; i++)
    {
        int minimum = i;
        for (int ii = minimum+1; ii<m_size; ii++)
        {
            if(array[ii] < array[minimum])
            {
                minimum = ii;
            }
        }
        if(minimum != i)
        {
            int swap = array[i];
            array[i] = array[minimum];
            array[minimum] = swap;
        }
    }
    
}


void Sorts::LinearInsertionBench()
{
    m_outfile<<"\n-------LINEAR INSERTION--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        LinearInsertion(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        LinearInsertion(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        LinearInsertion(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}


template <typename T>
void Sorts::ShellSort(T & array)
{
    int h = 0;
    int i = 0;
    int sorts[100];
    for(i = 0; h<m_size;i++)
    {
        h = 3*h+1;
        sorts[i] = h;
    }
    for(int ii = i-1; ii>=0; ii--)
    {
        int gap = sorts[ii];
        for (int k = gap; k < m_size; k++)
        {
            int temp = array[k];
            int j;
            for (j = k; j >= gap && array[j - gap] > temp; j -= gap)
            {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void Sorts::ShellSortBench()
{
    m_outfile<<"\n-------SHELL SORT--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        ShellSort(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        ShellSort(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        ShellSort(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

template <typename T>
void Sorts::HeapSort(T & array)
{
    BuildHeap(array);
    for (int i = m_size-1; i>=0; i--)
    {
        int swap = array[0];
        array[0] = array[i];
        array[i] = swap;
        Heapify(array, 0, i);
    }
}


template <typename T>
void Sorts::Heapify(T & array, int i, int size)
{
    int left = 2*i;
    int right = 2*i+1;
    int max;
    if (left < size && array[left] > array[i])
        max = left;
    else
    {
        max = i;
    }
    if (right < size && array[right] > array[max])
        max = right;
        
    if (max != i)
    {
        int swap = array[i];
        array[i] = array[max];
        array[max] = swap;
        Heapify(array, max, size);
    }
        
}



template <typename T>
void Sorts::BuildHeap(T & array)
{
    for (int i = m_size/2; i>=0; i--)
    {
        Heapify(array, i, m_size);
    }
    
}


void Sorts::HeapSortBench()
{
    m_outfile<<"\n-------HEAP SORT--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        HeapSort(array);
        time_point end = std::chrono::high_resolution_clock::now();
        //Display(array);
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        HeapSort(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        HeapSort(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

void Sorts::MergeSortBench()
{
    m_outfile<<"\n-------MERGE SORT--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        MergeSort(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        MergeSort(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        MergeSort(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

template <typename T>
void Sorts::MergeSort(T & array)
{
    int * temp = new int[m_size];
    
    MergeSort(array, temp, 0, m_size);
    
    delete [] temp;
    
}

template <typename T>
void Sorts::MergeSort(T & array, int * temp, int left, int right)
{

    if(right-left < 2)
    {
        
    }
    else
    {
        int mid = (left + right) /2;
        MergeSort(array, temp, left, mid);
        MergeSort(array, temp, mid, right);
        Merge(array, temp, left, mid, right);
    }
}

template <typename T>
void Sorts::Merge(T & array, int * temp, int left, int right, int re)
{
    int beg = left;
    int mid = right;

    for (int i = left; i<re; i++)
    {
        if (beg<right && (mid >= re || array[beg] <= array[mid]))
        {
            temp[i] = array[beg];
            beg++;
        }
        else
        {
            temp[i] = array[mid];
            mid++;
        }
    }
    for(int i = left; i < re; i++)
        array[i] = temp[i];
}

void Sorts::QuickSortBench()
{
    m_outfile<<"\n-------QUICK SORT--------";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
    bool csc, vsc, msc;                 //used to check if arrays are sorted correctly
    bool all_correct = true;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int * array = new int[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        time_point begin = std::chrono::high_resolution_clock::now();
        QuickSort(array);
        time_point end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        QuickSort(this_vector);
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        QuickSort(this_myarray);
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        v_at_500 = this_vector[500];
        c_at_500 = array[500];
        m_at_500 = this_myarray[500];
        csc = SortedCorrectly(array);
        vsc = SortedCorrectly(array);
        msc = SortedCorrectly(array);
        if(csc && vsc && msc)
            m_outfile<<".";
        else{
            m_outfile<<"!";
            all_correct = false;
        }
        delete [] array;
    }   //end for loop
    if(all_correct)
        m_outfile<<"\nAll sorts completed correctly!\n";
    else
        m_outfile<<"Sort errors detected.\n";
    m_outfile<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us ";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

template <typename T>
void Sorts::QuickSort(T & array)
{
    QuickSort(array, 0, m_size-1);
}

template <typename T>
void Sorts::QuickSort(T &array, int lo, int hi)
{
    if(lo < hi)
    {
        int pivot = array[hi];
        int i = lo;
        for(int j = lo; j<hi; j++)
        {
           if(array[j] <= pivot)
           {
               int hold = array[i];
               array[i] = array[j];
               array[j] = hold;
               i++;
           }
        }
        int hold = array[hi];
        array[hi] = array[i];
        array[i] = hold;
        
        QuickSort(array, lo, i-1);
        QuickSort(array, i+1, hi);
        
    }
    
}

template <typename T>
bool Sorts::SortedCorrectly(T & array)
{
    bool sorted_correctly = true;
    int largest = array[0];
    for (int i = 0; i<m_size && sorted_correctly; i++)
    {
        if(array[i] < largest)
        {
            sorted_correctly = false;
        }
        else
        {
            largest = array[i];
        }
    }
    return sorted_correctly;
}




