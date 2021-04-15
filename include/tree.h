#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <cmath>

#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#include "customErrorClass.h"

using namespace std;

struct S_NODE{
    int value;
    S_NODE *left;
    S_NODE *right;
    S_NODE *parent;
    int lheight;
    int rheight;
};

class C_Tree{
    public:
        C_Tree();
        ~C_Tree();
        void insertValue(int);
        void print(bool=true);
        void deleteNode(int);
        void deleteTree();
        S_NODE* findNode(int);
        int getTreeHeight();
        int getHeight(S_NODE*);
        void readFile(char*);

        void debug(bool=false);
    private:
        S_NODE *p_root;

        void p_insertValue(S_NODE*, int);
        S_NODE* p_createNode(S_NODE*, int);
        void p_createTree(int);
        
        void p_updateHeights(S_NODE*, S_NODE*, bool=true);
        int p_balance(S_NODE*);
        void p_case1(S_NODE*);
        void p_case2(S_NODE*);
        void p_case3(S_NODE*);
        void p_case4(S_NODE*);
        
        void p_printInOrder(S_NODE*);
        void p_formattedPrint(S_NODE*, int=0);
        
        void p_deleteNode(S_NODE*, int);
        void p_deleteTree(S_NODE*);
        
        int p_getHeight(S_NODE*);
        bool p_stop();
        void p_readFile(char*);
        
        S_NODE* p_findNode(S_NODE*, int);
        S_NODE* p_findSuccessor(S_NODE*);
        S_NODE* p_findPredecessor(S_NODE*);

        void p_rotateLeft(S_NODE*);
        void p_rotateLeft(S_NODE*, S_NODE*, S_NODE*);
        void p_rotateRight(S_NODE*);
        void p_rotateRight(S_NODE*, S_NODE*, S_NODE*);
};

#endif