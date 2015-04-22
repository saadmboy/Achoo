//
//  VectorContainer.h
//  Achoo
//
//  Created by Saad K on 4/22/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#ifndef __Achoo__VectorContainer__
#define __Achoo__VectorContainer__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "Structs.cpp"

template <class T>
class VectorContainer{
public:
    VectorContainer(){
        innerVector = new vector<T>;
    }
    ~VectorContainer(){
        delete innerVector;
    }
    bool insert(T );
    vector<T> * innerVector;//this vector can contain Search, Disease and Symptom objects
    VectorContainer<Search *> * initialSearchVector(VectorContainer<Disease *> *, string);
    VectorContainer<Search *> * searchSearchVector(VectorContainer<Search *> *, string);
    int size();
    T completeSearch(string);
    T get(int );
};

#endif /* defined(__Achoo__VectorContainer__) */
