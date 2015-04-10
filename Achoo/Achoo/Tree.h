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

using namespace std;

struct TreeNode {
    string data;
    TreeNode *Lchild;
    TreeNode *Rchild;
};

class Tree{
public:
    TreeNode * Root;
    Tree(){
        Root = NULL;
    }
    TreeNode* insertNode(string s);
};