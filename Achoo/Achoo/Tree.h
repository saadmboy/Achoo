//
//  Tree.h
//  Achoo
//
//  Created by Saad K on 3/10/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//
#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include "Structs.cpp"
#include "Utilities.h"
using namespace std;

/* AVL node */
template <class T>
class AVLnode {
public:
    T key;
    AVLnode *left, *right, *parent;
    bool visited;
    AVLnode(T k, AVLnode *p){
        left = right = NULL;
        parent= p;
        key = k;
        visited = false;
    }
    
    ~AVLnode() {
        delete left;
        delete right;
    }
};

/* AVL tree */
template <class T>
class AVLtree {
public:
    AVLnode<T> *root;
    AVLtree(){}
    ~AVLtree(){delete root;}
    bool insert(T key);
    void display(AVLnode<T> *, int);
    AVLnode<T> * completeSearch(string&, AVLnode<T> *&);
    vector<Search *> * search(string );
    void print_DOT(FILE* stream);
private:
    AVLnode<T>* rotateLeft (AVLnode<T> *);
    AVLnode<T>* rotateLeftThenRight (AVLnode<T> *);
    AVLnode<T>* rotateRight (AVLnode<T> *);
    AVLnode<T>* rotateRightThenLeft (AVLnode<T> *);
    void rebalance (AVLnode<T> *);
    int height (AVLnode<T> *);
    void innerSearch(string, vector<Search *> *, AVLnode<T> *&, int);
    
    void preOrder(ostream &out, AVLnode<T>* pre);
    string dot();
    void bst_print_dot_null(T key, int nullcount, FILE* stream);
    void bst_print_dot_aux(AVLnode<T>* node, FILE* stream);
};




