//
//  Utilities.cpp
//  Achoo
//
//  Created by Saad K on 4/17/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//
#pragma once
#include "Utilities.h"

using namespace std;

/**
 * The following functions are from http://stackoverflow.com/questions/236129/split-a-string-in-c and basically help split a string with a deliminator
 * Used to read and split the diseases.txt
 **/
vector<string> &Utilities::split(const string &s, char delim, vector<string> &elems){
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
vector<string> Utilities::split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}









