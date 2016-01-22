//
//  Sorts.hpp
//  Sorts
//
//  Created by Ian Murphy on 1/22/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef Sorts_hpp
#define Sorts_hpp

#include <stdio.h>
#include <vector>
#include <fstream>

class Sorts
{
public:
    Sorts(char * inputfile, int size);
    void BubbleSort();
private:
    void Display(int array);
    void Shuffle();
    void Init();
    int m_size;
    
    int * m_array;
    std::vector<int> m_vector;
    std::ofstream m_outfile;
};

#endif /* Sorts_hpp */
