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


using namespace std;

struct Symptom;
struct Disease;
struct search;

struct Disease{
    string name;
    vector<Symptom *> symptoms;
};

struct Symptom{
    string name;
    Disease *disease;
};

struct search {
    Symptom * symptom;
    Disease disease;
    double value;
};