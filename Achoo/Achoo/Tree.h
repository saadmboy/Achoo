//
//  Tree.h
//  Achoo
//
//  Created by Saad K on 3/10/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "Structs.cpp"

using namespace std;
/*
template <class T>
class Tree{
    

public:
    struct TreeNode {
        T data;
        TreeNode *Lchild;
        TreeNode *Rchild;
    };
    TreeNode * Root;
    Tree(){
        Root = NULL;
    }
    void insertNode(T * toAdd);
};*/

//http://www.sanfoundry.com/cpp-program-implement-avl-trees/

template <class T>
struct TreeNode {
    T data;
    TreeNode *Lchild;
    TreeNode *Rchild;
};


template <class T>
class Tree{
    
    
public:
    TreeNode<T> * Root;
    Tree(){
        Root = NULL;
    }
    TreeNode<T> * insertNode(TreeNode<T> *root, T toAdd);
    int height(TreeNode<T> *);
    int diff(TreeNode<T> *);
    TreeNode<T> *rr_rotation(TreeNode<T> *);
    TreeNode<T> *ll_rotation(TreeNode<T> *);
    TreeNode<T> *lr_rotation(TreeNode<T> *);
    TreeNode<T> *rl_rotation(TreeNode<T> *);
    TreeNode<T> * balance(TreeNode<T> *);
    void display(TreeNode<T> *, int);

};








