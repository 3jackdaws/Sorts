//
//  Sorts.cpp
//  Sorts
//
//  Created by Ian Murphy on 1/22/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "Sorts.hpp"
Sorts::Sorts(char * output, int size, int iterations) : m_size(size), m_interations(iterations)
{
    m_outfile = std::ofstream(output);
    m_array = new int[size];
    Init();
    Shuffle();
}

void Sorts::Init()
{
    for (int i = 0; i<m_size; i++)
    {
        m_array[i] = i;
    }
}

void Sorts::Shuffle()
{
    srand(time(nullptr));
    for (int i = 0; i<m_size; i++) {
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

void Sorts::BubbleSort()
{
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        /*   =======   Create array copies ======  */
        int array[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        
        auto begin = std::chrono::high_resolution_clock::now();
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
        auto end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i<m_size; i++)
        {
            for (int ii = 0; ii<m_size - i -1; ii++)
            {
                if(this_vector[ii] > this_vector[ii + 1])
                {
                    int hold = this_vector[ii];
                    this_vector[ii] = this_vector[ii+1];
                    this_vector[ii+1] = hold;
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i<m_size; i++)
        {
            for (int ii = 0; ii<m_size - i -1; ii++)
            {
                if(this_myarray[ii] > this_myarray[ii + 1])
                {
                    int hold = this_myarray[ii];
                    this_myarray[ii] = this_myarray[ii+1];
                    this_myarray[ii+1] = hold;
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
    }   //end for loop
    std::cout<<"-------BRUTEFORCE BUBBLESORT--------"<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

void Sorts::FlaggedBubble()
{
    
    
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        
        /*   =======   Create array copies ======  */
        int array[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        
        auto begin = std::chrono::high_resolution_clock::now();
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

        auto end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        sorted = false;
        for (int i = 0; i<m_size && !sorted; i++)
        {
            sorted = true;
            for (int ii = 0; ii<m_size - i -1; ii++)
            {
                if(this_vector[ii] > this_vector[ii + 1])
                {
                    sorted = false;
                    int hold = this_vector[ii];
                    this_vector[ii] = this_vector[ii+1];
                    this_vector[ii+1] = hold;
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        sorted = false;
        for (int i = 0; i<m_size && !sorted; i++)
        {
            sorted = true;
            for (int ii = 0; ii<m_size - i -1; ii++)
            {
                if(this_myarray[ii] > this_myarray[ii + 1])
                {
                    sorted = false;
                    int hold = this_myarray[ii];
                    this_myarray[ii] = this_myarray[ii+1];
                    this_myarray[ii+1] = hold;
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
    }   //end for loop
    std::cout<<"-------FLAGGED BUBBLESORT--------"<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

void Sorts::StraightSelection()
{
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        
        /*   =======   Create array copies ======  */
        int array[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        
        auto begin = std::chrono::high_resolution_clock::now();
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
        auto end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i<m_size-1; i++)
        {
            int minimum = i;
            for (int ii = minimum+1; ii<m_size; ii++)
            {
                if(this_vector[ii] < this_vector[minimum])
                {
                    minimum = ii;
                }
            }
            if(minimum != i)
            {
                int swap = this_vector[i];
                this_vector[i] = this_vector[minimum];
                this_vector[minimum] = swap;
            }
        }        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i<m_size-1; i++)
        {
            int minimum = i;
            for (int ii = minimum+1; ii<m_size; ii++)
            {
                if(this_myarray[ii] < this_myarray[minimum])
                {
                    minimum = ii;
                }
            }
            if(minimum != i)
            {
                int swap = this_myarray[i];
                this_myarray[i] = this_myarray[minimum];
                this_myarray[minimum] = swap;
            }
        }        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
    }   //end for loop
    std::cout<<"-------STRAIGHT SELECTION SORT--------"<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    
    
}

void Sorts::LinearInsertion()
{
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        
        /*   =======   Create array copies ======  */
        int array[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 1; i<m_size; i++)
        {
            int temp = array[i];
            int j = i;
            for(j=i; j > 0 && array[j-1] > temp; j--)
            {
                array[j] = array[j-1];
            }
            array[j] = temp;
        }

        auto end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for (int i = 1; i<m_size; i++)
        {
            int temp = this_vector[i];
            int j = i;
            for(j=i; j > 0 && this_vector[j-1] > temp; j--)
            {
                this_vector[j] = this_vector[j-1];
            }
            this_vector[j] = temp;
        }
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for (int i = 1; i<m_size; i++)
        {
            int temp = this_myarray[i];
            int j = i;
            for(j=i; j > 0 && this_myarray[j-1] > temp; j--)
            {
                this_myarray[j] = this_myarray[j-1];
            }
            this_myarray[j] = temp;
        }
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
    }   //end for loop
    std::cout<<"-------LINEAR INSERTION SORT--------"<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    
}

void Sorts::ShellSort()
{
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
    int h = 0;
    int i = 0;
    int sorts[20];
    for(i = 0; h<m_size;i++)
    {
        h = 3*h+1;
        sorts[i] = h;
    }

    
    for (int num_iter = 0; num_iter<m_interations; num_iter++)
    {
        
        /*   =======   Create array copies ======  */
        int array[m_size];
        for (int i = 0; i<m_size; i++)
        {
            array[i] = m_array[i];
        }
        std::vector<int> this_vector = m_vector;
        Array<int> this_myarray = m_myarray;
        
        
        auto begin = std::chrono::high_resolution_clock::now();
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

        
        auto end = std::chrono::high_resolution_clock::now();
        carray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for(int ii = i-1; ii>=0; ii--)
        {
            int gap = sorts[ii];
            for (int k = gap; k < m_size; k++)
            {
                int temp = this_vector[k];
                int j;
                for (j = k; j >= gap && this_vector[j - gap] > temp; j -= gap)
                {
                    this_vector[j] = this_vector[j - gap];
                }
                this_vector[j] = temp;
            }
        }
        end = std::chrono::high_resolution_clock::now();
        vector_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        
        
        begin = std::chrono::high_resolution_clock::now();
        for(int ii = i-1; ii>=0; ii--)
        {
            int gap = sorts[ii];
            for (int k = gap; k < m_size; k++)
            {
                int temp = this_myarray[k];
                int j;
                for (j = k; j >= gap && this_myarray[j - gap] > temp; j -= gap)
                {
                    this_myarray[j] = this_myarray[j - gap];
                }
                this_myarray[j] = temp;
            }
        }
        
        end = std::chrono::high_resolution_clock::now();
        myarray_average += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
       
        
        
    }   //end for loop
    
    std::cout<<"-------SHELL SORT--------"<<std::endl;
    std::cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    std::cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    std::cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

void Sorts::HeapSort()
{
    /*   =======   Create array copies ======  */
    int array[m_size];
    for (int i = 0; i<m_size; i++)
    {
        array[i] = m_array[i];
    }
    std::vector<int> this_vector = m_vector;
    Array<int> this_myarray = m_myarray;
    
    
    
    
    
    for (int i = 0; i<m_size; i++)
    {
        std::cout<<array[i]<<std::endl;
    }
}
