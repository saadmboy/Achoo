//
//  Tree.cpp
//  Achoo
//
//  Created by Saad K on 3/10/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include "Tree.h"


using namespace std;

/*
template <class T>
void Tree<T>::insertNode(T * toAdd){
    TreeNode *tmp, * newNode;
    newNode = new TreeNode;
    newNode->data = *toAdd;
    newNode->Rchild = newNode->Lchild = NULL;
    
    if(Root == NULL){
        Root = newNode;
        return;
    }else{
        tmp = Root;
        while(tmp != NULL){
            //toAdd < value
            //strcmp("aa", "ab") < 0 = true
            
            if(strcmp(toAdd->name.c_str(), tmp->data.name.c_str()) < 0){
                if(tmp->Lchild){
                    tmp = tmp->Lchild;
                }else{
                    tmp->Lchild = newNode;
                }
                break;
            }else if (strcmp(toAdd->name.c_str(), tmp->data.name.c_str()) > 0){
                if(tmp->Rchild){
                    tmp = tmp->Rchild;
                }else{
                    tmp->Rchild = newNode;
                }
                break;
            }else{
                cout << "Duplicate value found in tree: "<< toAdd->name <<"\n";
                break;
            }
        }
    }
    
    return;
}*/

/*
 * Height of AVL Tree
 *
template <class T>
int Tree<T>::height(TreeNode<T> *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->Lchild);
        int r_height = height (temp->Rchild);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/*
 * Height Difference
 *
template <class T>
int Tree<T>::diff(TreeNode<T> *temp)
{
    int l_height = height (temp->Lchild);
    int r_height = height (temp->Rchild);
    int b_factor= l_height - r_height;
    return b_factor;
}

/*
 * Right- Right Rotation
 *
template <class T>
TreeNode<T> *Tree<T>::rr_rotation(TreeNode<T> *parent)
{
    TreeNode<T> *temp;
    temp = parent->Rchild;
    parent->Rchild = temp->Lchild;
    temp->Lchild = parent;
    return temp;
}
/*
 * Left- Left Rotation
 *
template <class T>
TreeNode<T> *Tree<T>::ll_rotation(TreeNode<T> *parent)
{
    TreeNode<T> *temp;
    temp = parent->Lchild;
    parent->Lchild = temp->Rchild;
    temp->Rchild = parent;
    return temp;
}

/*
 * Left - Right Rotation
 *
template <class T>
TreeNode<T> *Tree<T>::lr_rotation(TreeNode<T> *parent)
{
    TreeNode<T> *temp;
    temp = parent->Lchild;
    parent->Lchild = rr_rotation (temp);
    return ll_rotation (parent);
}

/*
 * Right- Left Rotation
 *
template <class T>
TreeNode<T> *Tree<T>::rl_rotation(TreeNode<T> *parent)
{
    TreeNode<T> *temp;
    temp = parent->Rchild;
    parent->Rchild = ll_rotation (temp);
    return rr_rotation (parent);
}

/*
 * Balancing AVL Tree
 *
template <class T>
TreeNode<T> *Tree<T>::balance(TreeNode<T> *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->Lchild) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->Rchild) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    if (temp->parent != NULL) {
        balance(temp->parent);
    }
    else {
        Root = temp;
    }
    return temp;
}*/
/*

template <class T>
void Tree<T>::display(TreeNode<T> *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->Rchild, level + 1);
        printf("\n");
        if (ptr == Root)
            cout<<"Root -> ";
        for (i = 0; i < level && ptr !=Root; i++)
            cout<<"        ";
        cout<< ptr->data.name;
        display(ptr->Lchild, level + 1);
    }
}
template <class T>
TreeNode<T> * Tree<T>::insertNode(TreeNode<T> *p, T toAdd){

    if (p == NULL) {
        Root = new TreeNode<T>;
        Root->data = toAdd;
        Root->Lchild = NULL;
        Root->Rchild = NULL;
        return Root;
    } else if(strcmp(toAdd.name.c_str(), p->data.name.c_str()) < 0){
        cout <<"< 0: " << toAdd.name << endl;
        p->Lchild = insertNode(p->Lchild, toAdd);
        Root = balance (p);
        cout <<"BALANCED: " << toAdd.name << endl;
    } else if (strcmp(toAdd.name.c_str(), p->data.name.c_str()) > 0){
        cout <<">0: " << toAdd.name << endl;
        p->Rchild = insertNode(p->Rchild, toAdd);
        Root = balance (p);
        cout <<"BALANCED: " << toAdd.name << endl;
    }else{
        cout <<"DUPLICATE: " << toAdd.name << endl;
    }
    
    if (p == NULL) {
        p = new TreeNode<T>;
        p->data = toAdd;
        p->Lchild = NULL;
        p->Rchild = NULL;
        return p;
    }else{
        
        if(strcmp(toAdd.name.c_str(), p->data.name.c_str()) < 0){
            p->Lchild = insertNode(p->Lchild, toAdd);
            if(diff(p) == 2){
                if(strcmp(toAdd.name.c_str(), p->data.name.c_str()) < 0)
                    p = ll_rotation(p);
                else
                    p = lr_rotation(p);
            }
        } else if (strcmp(toAdd.name.c_str(), p->data.name.c_str()) > 0){
            p->Rchild = insertNode(p->Rchild, toAdd);
            if(diff(p) == -2){
                if(strcmp(toAdd.name.c_str(), p->data.name.c_str()) > 0)
                    p = rr_rotation(p);
                else
                    p = rl_rotation(p);
            }
        }else{
            cout <<"DUPLICATE: " << toAdd.name << endl;
        }
        
        
    }
     
     
    return p;
    
}


template <class T>
void Tree<T>::insertNode(T toAdd) {
    if (Root == NULL) {
        Root = new TreeNode<T>(toAdd);
        Root->Lchild = NULL;
        Root->Rchild = NULL;

    }
    else {
        TreeNode<T>
        *n = Root,
        *parent;
        
        while (true) {
            if(toAdd.name == n->data.name)
                return;
            
            parent = n;
            
            bool goLeft = strcmp(toAdd.name.c_str(), n->data.name.c_str()) < 0;
            n = goLeft ? n->Lchild : n->Rchild;
            
            if (n == NULL) {
                if (goLeft) {
                    parent->Lchild = new TreeNode<T>(toAdd);
                    parent->Lchild->parent = parent;
                }
                else {
                    parent->Rchild = new TreeNode<T>(toAdd);
                    parent->Rchild->parent = parent;
                }
                balance(parent);
                break;
            }
        }
    }
    
    return;
}

template <class T>
void Tree<T>::rebalance(TreeNode<T> *n) {
    setBalance(n);
    
    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }
    
    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        Root = n;
    }
}


template <class T>
void Tree<T>::inorder(TreeNode<T> *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->Lchild);
    cout <<tree->data.name<<"  ";
    inorder (tree->Rchild);
}
*/




/* AVL class definition */
template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);
    
    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }
    
    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

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
    
    setBalance(a);
    setBalance(b);
    return b;
}

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
    
    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLtree<T>::printBalance(AVLnode<T> *n) {
    if (n != NULL) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <class T>
AVLtree<T>::AVLtree(void) : root(NULL) {}

template <class T>
AVLtree<T>::~AVLtree(void) {
    delete root;
}

template <class T>
bool AVLtree<T>::insert(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
        *n = root,
        *parent;
        
        while (true) {
            if(key.name == n->key.name)
                return false;
            
            parent = n;
            
            bool goLeft = strcmp(key.name.c_str(), n->key.name.c_str()) < 0;
            n = goLeft ? n->left : n->right;
            
            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }
                
                rebalance(parent);
                break;
            }
        }
    }
    
    return true;
}

template <class T>
AVLnode<T> * AVLtree<T>::search(const std::string& s, AVLnode<T> *& tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    else if(s < tree->key.name)
    {
        return search(s, tree->left);
    }
    else if(tree->key.name < s)
    {
        return search(s, tree->right);
    }
    else
    {
        return tree;
    }
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

/*FROM: http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz*/

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


template class AVLtree<Symptom>;
template class AVLtree<Disease>;






