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
/*
template <class T>
struct TreeNode {
    T data;
    int balance;
    TreeNode *Lchild;
    TreeNode *Rchild;
    TreeNode *parent;
    TreeNode(T d){
        balancde = 0;
        data = d;
        Rchild = Lchild = parent = NULL;
    }
    ~TreeNode(){
        delete Lchild;
        delete Rchild;
    }
};


template <class T>
class Tree{
    
    
public:
    TreeNode<T> * Root;
    Tree(){
        Root = NULL;
    }
    void insertNode(T);
    //TreeNode<T> * insertNode(TreeNode<T> *, T);
    int height(TreeNode<T> *);
    int diff(TreeNode<T> *);
    TreeNode<T> *rr_rotation(TreeNode<T> *);
    TreeNode<T> *ll_rotation(TreeNode<T> *);
    TreeNode<T> *lr_rotation(TreeNode<T> *);
    TreeNode<T> *rl_rotation(TreeNode<T> *);
    TreeNode<T> * balance(TreeNode<T> *);
    void display(TreeNode<T> *, int);
    void inorder(TreeNode<T> *);
    void rebalance(TreeNode<T> *);
    void setBalance(TreeNode<T> *n );

};


*/



/* AVL node */
template <class T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode *left, *right, *parent;
    
    AVLnode(T k, AVLnode *p) : key(k), balance(0), parent(p),
    left(NULL), right(NULL) {}
    
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
    
    AVLnode<T>* rotateLeft          ( AVLnode<T> *a );
    AVLnode<T>* rotateRight         ( AVLnode<T> *a );
    AVLnode<T>* rotateLeftThenRight ( AVLnode<T> *n );
    AVLnode<T>* rotateRightThenLeft ( AVLnode<T> *n );
    void rebalance                  ( AVLnode<T> *n );
    int height                      ( AVLnode<T> *n );
    void setBalance                 ( AVLnode<T> *n );
    void printBalance               ( AVLnode<T> *n );
    void clearNode                  ( AVLnode<T> *n );
    void preOrder(ostream &out, AVLnode<T>* pre);
    string dot();
};




