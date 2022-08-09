#ifndef TREENODE_H
#define TREENODE_H
#include "employee.h"
#include <vector>
using namespace std;

#pragma once

class treeNode{
public:
    //constructor 
    treeNode(string s, string p);
    //methods
    string returnEmp();
    void editEmpDetails(string s, string p);
    vector <treeNode*> returnChildren();
    treeNode* returnParent();
    void setChildren(vector <treeNode*> _children);
    void setParent(treeNode* _parent);

private:
    employee emp;
    vector <treeNode*> children;
    treeNode* parent;
};

#endif
