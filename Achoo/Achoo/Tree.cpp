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
 */
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
 */
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
 */
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
 */
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
 */
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
 */
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
 */
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
    return temp;
}


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
        p->Lchild = insertNode(p->Lchild, toAdd);
        Root = balance (p);
    } else if (strcmp(toAdd.name.c_str(), p->data.name.c_str()) > 0){
        p->Rchild = insertNode(p->Rchild, toAdd);
        Root = balance (p);
    }
    return p;
    
}


template class Tree<Symptom>;
template class Tree<Disease>;






