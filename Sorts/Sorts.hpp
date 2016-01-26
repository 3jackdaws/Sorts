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

class Sorts
{
public:
    Sorts(char * inputfile, int size, int iterations = 1);
    void BubbleSort();
    void FlaggedBubble();
    void StraightSelection();
    void LinearInsertion();
    void ShellSort();
    void HeapSort();
private:
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
