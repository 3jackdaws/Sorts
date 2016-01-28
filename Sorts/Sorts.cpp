/*************************************************************
* Author:		Ian Murphy
* Filename:		Sorts.cpp
* Date Created:	1/25ish/2016
* Modifications:	Check github - github.com/3jackdaws
**************************************************************/


#include "Sorts.hpp"

Sorts::Sorts() : m_size(0), m_interations(0), m_outfile(std::ofstream("output.txt")), m_array(nullptr)
{

}

/**********************************************************************
* Purpose: This is a ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      initializes m_size and and m_interations which is spelled wrong
*
************************************************************************/
Sorts::Sorts(int size, int iterations) : m_size(size), m_interations(iterations), m_outfile(std::ofstream("output.txt"))
{
    m_array = new int[size];
    Init();
    Shuffle();
    m_outfile<<"Sorting "<<m_size<<" elements."<<std::endl;
}

/**********************************************************************
* Purpose: This is a dtor.
*
* Precondition:
*     object must exist
*
* Postcondition:
*      deletes the new'd m_array and closes the output file
*
************************************************************************/
Sorts::~Sorts()
{
    m_outfile.close();
    delete [] m_array;
	m_array = nullptr;
	m_size = 0;
	m_interations = 0;
}

/**********************************************************************
* Purpose: This is a copy ctor.
*
* Precondition:
*     passed Sorts object must be an instance
*
* Postcondition:
*      creates an identical copy of the passed sorts object
*
************************************************************************/
Sorts::Sorts(const Sorts & cp)
{
	m_size = cp.m_size;
	m_interations = cp.m_interations;
	m_array = new int[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_array[i] = cp.m_array[i];
	}
	m_vector = cp.m_vector;
	m_myarray = cp.m_myarray;
}

/**********************************************************************
* Purpose: op = override, allows the copying of a Sorts object if both participants are both instances already.
*
* Precondition:
*     both participants are both instances already.
*
* Postcondition:
*      two objects are now equal to each other
*
************************************************************************/
Sorts & Sorts::operator=(const Sorts & rhs)
{
	if (this != &rhs)
	{
		m_size = rhs.m_size;
		m_interations = rhs.m_interations;
		delete[] m_array;
		m_array = new int[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_array[i] = rhs.m_array[i];
		}
		m_vector = rhs.m_vector;
		m_myarray = rhs.m_myarray;
	}
	return *this;
}

/**********************************************************************
* Purpose: Fills m_array with a series of numbers up to the m_size.
*
* Precondition:
*     only obvious stuff.
*
* Postcondition:
*      m_array is filled with a series of numbers that is easy to see if sorted
*
************************************************************************/
void Sorts::Init()
{
    for (int i = 0; i<m_size; i++)
    {
        m_array[i] = i+100;
		if (i < 100 && i>90)
			m_array[i] = 95;
    }
}

/**********************************************************************
* Purpose: Shuffles up the c array and copies the values over to the vector and the Array class.
*
* Precondition:
*     Array must g=have values in it
*
* Postcondition:
*      all three data structutres have the same random data in them
*
************************************************************************/
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

/**********************************************************************
* Purpose: Displays the contents of the passed array
*
* Precondition:
*     array should be of size m_size
*
* Postcondition:
*      the contents of the data structure is printed to the console
*
************************************************************************/
template <typename T>
void Sorts::Display(T & array)
{
    for (int i = 0; i<m_size; i++)
    {
        m_outfile<<array[i]<<std::endl;
    }
}

/**********************************************************************
* Purpose: Implements the bubble sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
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

/**********************************************************************
* Purpose: Times the execution of the bubble sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::BubbleSortBench()
{
    m_outfile<<"\n-------BRUTEFORCE BUBBLESORT--------\n";
    cout<<"\n-------BRUTEFORCE BUBBLESORT--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;

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
    
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Implements the flagged bubble sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
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

/**********************************************************************
* Purpose: Times the execution of the flagged bubble sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::FlaggedBubbleBench()
{
    m_outfile<<"\n-------FLAGGED BUBBLESORT--------\n";
    cout<<"\n-------FLAGGED BUBBLESORT--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
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
    
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Implements the straight selection sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
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

/**********************************************************************
* Purpose: Times the execution of the straight selection sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::StraightSelectionBench()
{
    m_outfile<<"\n-------STRAIGHT SELECTION--------\n";
    cout<<"\n-------STRAIGHT SELECTION--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
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
    
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Implements the linear insertion sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
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

/**********************************************************************
* Purpose: Times the execution of the linear insertion sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::LinearInsertionBench()
{
    m_outfile<<"\n-------LINEAR INSERTION--------\n";
    cout<<"\n-------LINEAR INSERTION--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
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
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Implements the shell sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
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

/**********************************************************************
* Purpose: Times the execution of the shell sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::ShellSortBench()
{
    m_outfile<<"\n-------SHELL SORT--------\n";
    cout<<"\n-------SHELL SORT--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
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
    
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Implements the heap sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
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

/**********************************************************************
* Purpose: Correctly sorts the heap for the Heap sort algoritm
*
* Precondition:
*     i is the beginning of the array and size is the end of the array
*
* Postcondition:
*      correctly heaps the data so that it can be extracted
*
************************************************************************/
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


/**********************************************************************
* Purpose: Initially builds the heap for the heap sort algorithm
*
* Precondition:
*     array is of size m_size
*
* Postcondition:
*      array is now correctly heapified
*
************************************************************************/
template <typename T>
void Sorts::BuildHeap(T & array)
{
    for (int i = m_size/2; i>=0; i--)
    {
        Heapify(array, i, m_size);
    }
    
}

/**********************************************************************
* Purpose: Times the execution of the heap sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::HeapSortBench()
{
    m_outfile<<"\n-------HEAP SORT--------\n";
    cout<<"\n-------HEAP SORT--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
    
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
    
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Times the execution of the merge sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::MergeSortBench()
{
    m_outfile<<"\n-------MERGE SORT--------\n";
    cout<<"\n-------MERGE SORT--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
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
    
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Implements the merge sort alogrithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
template <typename T>
void Sorts::MergeSort(T & array)
{
    int * temp = new int[m_size];
    
    MergeSort(array, temp, 0, m_size);
    
    delete [] temp;
    
}

/**********************************************************************
* Purpose: Recursively called to split arrays into sub-arrays
*
* Precondition:
*     right and left define the bounds of the sub array
*
* Postcondition:
*      splits the array into two sub arrays if the array is larger than 2
*
************************************************************************/
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

/**********************************************************************
* Purpose: Used in the merge sort algorith to merge two arrays together, sorted
*
* Precondition:
*     Passed data structure should be of size re-left
*
* Postcondition:
*      merges the two sub-arrays together so that they are correctly sorted
*
************************************************************************/
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

/**********************************************************************
* Purpose: Times the execution of quick sort method on all three internal data structures
*
* Precondition:
*     All internal data structures have data in them
*
* Postcondition:
*      the time of execution is printed to console and written to the output file
*
************************************************************************/
void Sorts::QuickSortBench()
{
    m_outfile<<"\n-------QUICK SORT--------\n";
    cout<<"\n-------QUICK SORT--------\n";
    double carray_average = 0;
    double vector_average = 0;
    double myarray_average = 0;
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
   
    m_outfile<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us ";
    m_outfile<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    m_outfile<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
    
    cout<<"C Array average for "<<m_interations<<" iteration(s): "<<(carray_average/m_interations)/1000<< " us ";
    cout<<"\nVector average for "<<m_interations<<" iteration(s): "<<(vector_average/m_interations)/1000<< " us";
    cout<<"\nmyarray average for "<<m_interations<<" iteration(s): "<<(myarray_average/m_interations)/1000<< " us"<<std::endl;
}

/**********************************************************************
* Purpose: Used to correctly call the quicksort algorithm
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      the passed data structure contains elements sorted in ascending order
*
************************************************************************/
template <typename T>
void Sorts::QuickSort(T & array)
{
    QuickSort(array, 0, m_size-1);
}

/**********************************************************************
* Purpose: Implements the quick sort alogrithm
*
* Precondition:
*     Passed data structure should have aat least hi-lo elements
*
* Postcondition:
*      the dat structure from lo to hi is sorted correctly
*
************************************************************************/
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

/**********************************************************************
* Purpose: Checks to see if the data structure has elements sorted correctly
*
* Precondition:
*     Passed data structure should have m_size elements
*
* Postcondition:
*      returns true if sorted correctly, otherwise returns false
*
************************************************************************/
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




