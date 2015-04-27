//
//  Structs.cpp
//  Achoo
//
//  Created by Saad K on 4/9/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//
#pragma once
#ifndef __Achoo__Structs__
#define __Achoo__Structs__

#include <vector>
#include <string>
#include "Utilities.h"

using namespace std;

struct Symptom;
struct Disease;
struct Search;
struct isSearch1MoreThanSearch2;


struct Disease {
    ~Disease(){
        for(int i = 0; i < symptoms.size(); i++)
            delete symptoms[i];
        delete disease;
    }
    string name;
    Disease * disease;//needed for the Tree to compile b/c I'm using templates instead of two separte AVltrees
    vector<Symptom *> symptoms;
    double compare(string s, int numberOfWordsInInput){//needed for the Tree to compile.
        return -1.0;
    }
};

struct Symptom {
    string name;
    Disease *disease;
    //compares the symptom with the symptom provided by the user
    //@return weighted average of words of string / total words provided by user
    double compare(string s, int numberOfWordsInInput){
        //s is one word
        double count = 0;
        vector<string> words = Utilities::split(name, ' ');
        for (int i = 0; i < words.size(); i++) {
            if(s == words[i]){
                count++;
            }
        }
        //count = number of words in the 
        return (double)(count / (double)numberOfWordsInInput);
    }
};

struct Search {
    Disease * disease;
    double searchValue;//search value/percentage
    int numElementInInput;
    string name;
};

//http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
//added pointers b/c array returned by Tree.search is a pointer array.
struct isSearch1MoreThanSearch2
{
    inline bool operator() (const Search *struct1 , const Search * struct2 )
    {
        return (struct1->searchValue > struct2->searchValue);
    }
};



#endif

