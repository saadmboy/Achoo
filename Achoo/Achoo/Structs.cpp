//
//  Structs.cpp
//  Achoo
//
//  Created by Saad K on 4/9/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//
#pragma once

#include <vector>
#include <string>
#include "Utilities.h"

using namespace std;

struct Symptom;
struct Disease;
struct search;

struct Disease{
    string name;
    Disease * disease;//needed for the Tree to compile b/c I'm using templates instead of two separte AVltrees
    vector<Symptom *> symptoms;
    double compare(string s){//needed for the Tree to compile.
        return -1.0;
    }
};

struct Symptom{
    string name;
    Disease *disease;
    double compare(string s){
        double count = 0;
        vector<string> words = Utilities::split(name, ' ');
        for (int i = 0; i < words.size(); i++) {
            if(s == words[i]){
                count++;
            }
        }
        return (double)(count / (double)words.size());
    }
};

//template <class T>
struct Search {
    Disease * disease;
    double searchValue;//search value/percentage
    int numElementInInput;
};


