#ifndef COMPANY_H
#define COMPANY_H
#include "treeNode.h"
#include <vector>

#pragma once

class company{
public:
    //constructors
    company();
    company(string s);
    //methods
    void setName(string s);
    void setLeader(string s, string p);
    treeNode* returnLeader();
    void addChildren(treeNode* node, vector<string> s, vector<string> p);
    string returnEmployees(treeNode* node, vector<bool> flag, int depth, bool isLast);
    string getName();
    treeNode* findNode(treeNode* node, string e);
    treeNode* returnFoundNode();
    void resetFoundNode();
    treeNode* deleteNode(treeNode* root, treeNode* foundNode, string promoteSetting);
    treeNode* changeParent(treeNode* root, treeNode* foundNode, string newBoss);
    void resetEmployeeString();

private:
    string name;
    string allEmployees;
    treeNode* root;
    treeNode* foundNode;
};

#endif
