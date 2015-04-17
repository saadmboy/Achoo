//
//  Tree.cpp
//  Achoo
//
//  Created by Saad K on 3/10/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include "Tree.h"

using namespace std;


/**
 * @return the height of the tree
 * @param *n = node to get height of
 **/
template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + max(height(n->left), height(n->right));
}

/**
 * Rebalances the given node
 * @return none
 * @param *n = node to balance
**/
template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    
    int balance = height(n->right) - height(n->left);
    
    if (balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }
    
    if (n->parent == NULL)
        root = n;
    else
        rebalance(n->parent);//make sure the parent is balanced, you move up
}

//rotates left
template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;
    
    if (a->right != NULL)
        a->right->parent = a;
    
    b->left = a;
    a->parent = b;
    
    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }
    
    return b;
}

//rotates right
template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;
    
    if (a->left != NULL)
        a->left->parent = a;
    
    b->right = a;
    a->parent = b;
    
    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }
    
    return b;
}
//rotates left then right
template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}
//rotates right then left
template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

/**
 * @param key = the key to insert
 * @return bool if the insert was(n't) successful (false = duplicate)
**/
template <class T>
bool AVLtree<T>::insert(T key) {
    
    transform(key.name.begin(),key.name.end(), key.name.begin(), ::tolower);

    if (root == NULL) {//if root is null, create it
        root = new AVLnode<T>(key, NULL);
    } else {
        AVLnode<T> *n = root, *parent;
        
        while (true) {
            if(key.name == n->key.name)//means this is a duplicate and we should stop (duplicates aren't added, though there won't be any)
                return false;
            
            parent = n;//start with parent = n then go from there
            
            if(strcmp(key.name.c_str(), n->key.name.c_str()) < 0){
                //go left
                n = n->left;
                if (n == NULL) {//if next node isn't there, this is where we add the new node
                    parent->left = new AVLnode<T>(key, parent);
                    rebalance(parent);
                    break;
                }
            }else{
                n = n-> right;
                if (n == NULL) {
                    parent->right = new AVLnode<T>(key, parent);
                    rebalance(parent);
                    break;
                }
            }
        }//end while loop
    }//end 1st else
    return true;
}


template <class T>
void AVLtree<T>::innerSearch(string s, vector<Search *> * toR, AVLnode<T> *& tree, int currentWordInInput){
    transform(s.begin(),s.end(), s.begin(), ::tolower);//lowercase the search
    //inorder traversal
    
    stack<AVLnode<T> *> stack;
    AVLnode<T> *Tmp = root;
    while(1) {
        while(Tmp!=NULL) {
            stack.push(Tmp);
            Tmp = Tmp->left;
        }
        if(stack.empty())
            return;
        Tmp = stack.top();stack.pop();
        
        Search * search;
        search = new Search;
        (*search).disease = Tmp->key.disease;
        (*search).searchValue = Tmp->key.compare(s);
        
       
        
        //http://www.cplusplus.com/reference/vector/vector/back/
        //basically if the user types in 'back pain' and the symptom has back pain in that order, increase the search vlaue
        if(!(*toR).empty()){
            if((*toR).back()->numElementInInput == currentWordInInput - 1)//if the last element inserted
                (*search).searchValue++;
        }
        
        (*search).numElementInInput = currentWordInInput;
        
        
        if((*search).searchValue > 0)
            (*toR).push_back(search);
        else
            delete search;
        
        Tmp = Tmp->right;
    }
    delete Tmp;
}

template <class T>
vector<Search *> * AVLtree<T>::search(string s){
    vector<Search*> * toR;
    
    toR = new vector<Search *>;
    
    vector<string> words = Utilities::split(s, ' ');
    
    
    for (int i = 0; i < words.size(); i++) {
        //cout << words[i] << "\n";
        innerSearch(words[i], toR, root, i);
    }
    
    return toR;
}



/**
 * Recursively searches the tree for the param s
 * @return the node with the key = s
**/
template <class T>
AVLnode<T> * AVLtree<T>::completeSearch(string& s, AVLnode<T> *& tree) {
    transform(s.begin(),s.end(), s.begin(), ::tolower);//lowercase the search
    
    if(tree == NULL)
        return NULL;
    
    if(s < tree->key.name)
        return completeSearch(s, tree->left);
    else if(s > (tree->key.name))
        return completeSearch(s, tree->right);
    else if ((tree->key.name) == (s))
        return tree;
    else
        return NULL;
}


template <class T>
void AVLtree<T>::display(AVLnode<T> *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
            cout<<"Root -> ";
        for (i = 0; i < level && ptr !=root; i++)
            cout<<"        ";
        cout<< ptr->key.name;
        display(ptr->left, level + 1);
    }
}



/**
 * The following functions are used to print the tree to a picture.
 * From: http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
**/

template <class T>
void AVLtree<T>::bst_print_dot_null(T key, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    \"%s\" -> null%d;\n", key.name.c_str(), nullcount);
}
template <class T>
void AVLtree<T>::bst_print_dot_aux(AVLnode<T>* node, FILE* stream)
{
    static int nullcount = 0;
    
    if (node->left)
    {
        fprintf(stream, "    \"%s\" -> \"%s\"\n", node->key.name.c_str(), node->left->key.name.c_str());
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->key, nullcount++, stream);
    
    if (node->right)
    {
        fprintf(stream, "    \"%s\" -> \"%s\";\n", node->key.name.c_str(), node->right->key.name.c_str());
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->key, nullcount++, stream);
}
template <class T>
void AVLtree<T>::print_DOT(FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");
    
    if (!root)
        fprintf(stream, "\n");
    else
        bst_print_dot_aux(root, stream);
    
    fprintf(stream, "}\n");
}

/**
 * The following functions are from http://stackoverflow.com/questions/236129/split-a-string-in-c and basically help split a string with a deliminator
 * Used to read and split the diseases.txt
 **
template <class T>
vector<string> & AVLtree<T>::split(const string &s, char delim, vector<string> &elems){
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
template <class T>
vector<string> AVLtree<T>::split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}*/

//declare classes/structs to be used with AVLTree
template class AVLtree<Symptom>;
template class AVLtree<Disease>;





