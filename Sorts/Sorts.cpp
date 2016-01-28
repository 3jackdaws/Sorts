//
//  Sorts.cpp
//  Sorts
//
//  Created by Ian Murphy on 1/22/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "Sorts.hpp"
Sorts::Sorts(int size, int iterations) : m_size(size), m_interations(iterations)
{
    m_outfile = std::ofstream("output.txt");
    m_array = new int[size];
    Init();
    Shuffle();
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

void Sorts::Display(int array)
{
    switch (array)
    {
        case 1:
            m_outfile<<"c_array"<<std::endl;
            for (int i = 0; i<m_size; i++)
            {
                m_outfile<<m_array[i]<<", ";
            }
            break;
        case 2:
            m_outfile<<"Vector"<<std::endl;
            for (int i = 0; i<m_size; i++)
            {
                m_outfile<<m_vector[i]<<", ";
            }
            break;
        default:
            break;
    }
        m_outfile<<std::endl;
    
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
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------BRUTEFORCE BUBBLESORT--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
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
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------FLAGGED BUBBLESORT--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
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
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------STRAIGHT SELECTION--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
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
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------LINEAR INSERTION--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
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
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------SHELL SORT--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
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
        Heapify(array, 0, i-1);
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
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------HEAP SORT--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

void Sorts::MergeSortBench()
{
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    int v_at_500, c_at_500, m_at_500;
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
    }   //end for loop
    std::cout<<"\n-------MERGE SORT--------"<<"[500] = "<<c_at_500<<" "<< v_at_500 <<" "<<m_at_500<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

template <typename T>
void Sorts::MergeSort(T & array)
{
    int * temp = new int[m_size];
    
    MergeSort(array, temp, 0, m_size);
    
    
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
    int * array = new int[m_size];
    for (int i = 0; i<m_size; i++)
    {
        array[i] = m_array[i];
    }
    QuickSort(array);
    for (int i = 0; i<m_size; i++)
    {
        std::cout<<array[i]<<std::endl;
    }

    
}

template <typename T>
void Sorts::QuickSort(T & array)
{
    QuickSort(array, 1, m_size);
}

template <typename T>
void Sorts::QuickSort(T &array, int lo, int hi)
{
    if(lo < hi)
    {
        int pivot = array[hi];
        int i = lo;
        for(int j = lo; j<hi-1; j++)
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





