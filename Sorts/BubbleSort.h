//
//  BubbleSort.h
//  Sorts
//
//  Created by Ian Murphy on 1/20/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef BubbleSort_h
#define BubbleSort_h

template <typename T>
class BubbleSort
{
public:
    BubbleSort(T array[], int size);
private:
    void swap(T array[],int s1, int s2);
};

template <typename T>
BubbleSort<T>::BubbleSort(T array[], int size)
{
    for (int i = 0; i<size; i++)
    {
        for (int ii = 0; ii<size - i -1; ii++)
        {
            if(array[ii] > array[ii + 1])
            {
                swap(array, ii, ii+1);
            }
        }
    }
}

template <typename T>
void BubbleSort<T>::swap(T array[], int s1, int s2)
{
    T hold = array[s1];
    array[s1] = array[s2];
    array[s2] = hold;
}
#endif /* BubbleSort_h */
