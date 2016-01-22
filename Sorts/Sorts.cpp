//
//  Sorts.cpp
//  Sorts
//
//  Created by Ian Murphy on 1/22/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include "Sorts.hpp"
Sorts::Sorts(char * output, int size) : m_size(size)
{
    m_outfile = std::ofstream(output);
    m_array = new int[size];
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
    Display(1);
    for (int i = 0; i<m_size; i++)
    {
        for (int ii = 0; ii<m_size - i -1; ii++)
        {
            if(m_array[ii] > m_array[ii + 1])
            {
                int hold = m_array[ii];
                m_array[ii] = m_array[ii+1];
                m_array[ii+1] = hold;
            }
        }
    }
}