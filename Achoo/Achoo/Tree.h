//
//  Tree.h
//  Achoo
//
//  Created by Saad K on 3/10/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Structs.cpp"

using namespace std;

/* AVL node */
template <class T>
class AVLnode {
public:
    T key;
    AVLnode *left, *right, *parent;
    
    AVLnode(T k, AVLnode *p){
        left = right = NULL;
        parent= p;
        key = k;
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
    AVLtree(void);
    ~AVLtree(void);
    bool insert(T key);
    void display(AVLnode<T> *ptr, int level);
    void bst_print_dot_null(T key, int nullcount, FILE* stream);
    void bst_print_dot_aux(AVLnode<T>* node, FILE* stream);
    void print_DOT(FILE* stream);
    AVLnode<T> * search(const std::string& s, AVLnode<T> *& tree);
private:
    AVLnode<T>* rotateLeft (AVLnode<T> *);
    AVLnode<T>* rotateRight (AVLnode<T> *);
    AVLnode<T>* rotateLeftThenRight (AVLnode<T> *);
    AVLnode<T>* rotateRightThenLeft (AVLnode<T> *);
    void rebalance (AVLnode<T> *);
    int height (AVLnode<T> *);
    void preOrder(ostream &out, AVLnode<T>* pre);
    string dot();
};




