#include <iostream>
#include "company.h"
#include "treeNode.h"
#include <queue>
using namespace std;

//constructor
company::company():root(NULL){
    setName("Company");
}

//constructor 2
company::company(string s):root(NULL){
    setName(s);
}

//method to set name
void company::setName(string s){
    name = s;
}

//method to set root node (run first)
void company::setLeader(string s, string p){
    if (root==NULL){
        root = new treeNode(s, p);
    }
    else{
        root->editEmpDetails(s, p);
    }
}

//method to return the root
treeNode* company::returnLeader(){
    return root;
}

//method to add children to any parent node
void company::addChildren(treeNode* node, vector<string> s, vector<string> p){
    vector<treeNode*> _children = node->returnChildren();
    for (unsigned int i = 0; i < s.size(); i++){
        treeNode* newNode = new treeNode(s[i],p[i]);
        _children.push_back(newNode);
        newNode->setParent(node);
    }
    node->setChildren(_children);
}

//method to return all employees in a string
string company::returnEmployees(treeNode* node, vector<bool> flag, int depth, bool isLast){
    // Condition when node is None
    if (node == NULL){
        return allEmployees;
    }
    // Loop to print the depths of the current node
    for (int i = 1; i < depth; ++i) {
        // Condition when the depth is exploring
        if (flag[i] == true) {
            allEmployees += "               ";
        }
        // Otherwise print the blank spaces
        else {
            allEmployees += "               ";
        }
    }
    // Condition when the current node is the root node
    if (depth == 0){
        allEmployees += node->returnEmp() + "\n";
    }
    // Condition when the node is the last node of the exploring depth
    else if (isLast) {
        allEmployees +=  "+----------" + node->returnEmp() + "\n";
        // No more childrens turn it to the non-exploring depth
        flag[depth] = false;
    }
    else {
        allEmployees += "+----------" + node->returnEmp() + "\n";
    }
    unsigned int it = 0;
    vector <treeNode*> _children = node->returnChildren();
    for (unsigned int i = 0; i < _children.size(); ++i, ++it){
        // Recursive call for the children nodes
        returnEmployees(_children[i], flag, depth + 1, it == (node->returnChildren().size()));
        flag[depth] = true;
    }
    return allEmployees;
}

//method to return name
string company::getName(){
    return name;
}

//method to find and return node using employee name
treeNode* company::findNode(treeNode* node, string e){
    if (node->returnEmp() == e){
        foundNode = node;
        return foundNode;
    }
    else{
        for (unsigned int i = 0; i < node->returnChildren().size(); i++){
            findNode(node->returnChildren()[i], e);
        }
        return foundNode;
    }
}

//method to return found node
treeNode* company::returnFoundNode(){
    return foundNode;
}

//method to reset the found node
void company::resetFoundNode(){
    foundNode = nullptr;
}

//function to delete a node from a tree based on specific conditions
treeNode* company::deleteNode(treeNode* root, treeNode* foundNode, string promoteSetting){
    //the searchedNode (foundNode) and its parent
    treeNode* searchedNode = foundNode;
    treeNode* parent = searchedNode->returnParent();
    //if it is a leaf node, just delete it
    if (searchedNode->returnChildren().size() == 0){
        vector<treeNode*> _children = parent->returnChildren();
        for (unsigned int i = 0; i < _children.size(); i++){
            if (_children[i] == searchedNode){
                _children.erase(_children.begin() + i);
                parent->setChildren(_children);
            }
        }
    }
    //if it has 1 child only, promote that 1 child
    else if (searchedNode->returnChildren().size() == 1){
        treeNode* oneChild = searchedNode->returnChildren()[0];
        vector<treeNode*> _children = parent->returnChildren();
        for (unsigned int i = 0; i < _children.size(); i++){
            if (_children[i] == searchedNode){
                _children.at(i) = oneChild;
                parent->setChildren(_children);
            }
        }
        oneChild->setParent(parent);
    }
    //if it has more than 1 child, and want to promote all children (append them at the end)
    else if (searchedNode->returnChildren().size() > 1 && promoteSetting == "all"){
        vector<treeNode*> allChildren = searchedNode->returnChildren();
        vector<treeNode*> _children = parent->returnChildren();
        for (unsigned int i = 0; i < _children.size(); i++){
            if (_children[i] == searchedNode){
               _children.erase(_children.begin() + i);
            }
        }
        for (unsigned int i = 0; i < allChildren.size(); i++){
            allChildren[i]->setParent(parent);
            _children.push_back(allChildren[i]);
        }
        parent->setChildren(_children);
    }
    //if it has more than 1 child, and want to only promote a specific child
    else {
        vector<treeNode*> allChildren = searchedNode->returnChildren();
        treeNode* nodeToPromote = allChildren[0];
        int InsertPos = 0;
        for (unsigned int i = 0; i < allChildren.size(); i++){
            if (allChildren[i]->returnEmp() == promoteSetting){
                nodeToPromote = allChildren[i];
                nodeToPromote->setParent(parent);
            }
        }
        vector<treeNode*> _children = parent->returnChildren();
        for (unsigned int i = 0; i < _children.size(); i++){
            if (_children[i] == searchedNode){
                InsertPos = i;
                _children.erase(_children.begin() + i);
            }
        }
        //push back other children to the node to promote, then attach that node
        vector<treeNode*> nTPchildren = nodeToPromote->returnChildren();
        for (unsigned int i = 0 ; i < allChildren.size(); i++){
            if (allChildren[i]->returnEmp() != promoteSetting){
                nTPchildren.push_back(allChildren[i]);
                allChildren[i]->setParent(nodeToPromote);
            }
            nodeToPromote->setChildren(nTPchildren);
        }
        _children.insert(_children.begin() + InsertPos, nodeToPromote);
        parent->setChildren(_children);
    }
    //return root
    return root;
}

//function to change a parent of a node
treeNode* company::changeParent(treeNode* root, treeNode* foundNode, string newBoss){
    treeNode* nBoss = findNode(root, newBoss);
    if (nBoss == nullptr){
        return root;
    }
    else if (nBoss->returnEmp() == newBoss){
        //remove node from old parent
        treeNode* parent = foundNode->returnParent();
        vector <treeNode*> _children = parent->returnChildren();
        for (unsigned int i = 0; i < _children.size(); i++){
            if (_children[i] == foundNode){
                _children.erase(_children.begin() + i);
            }
        }
        parent->setChildren(_children);
        //attach it to new parent
        vector _pchildren = nBoss->returnChildren();
        _pchildren.push_back(foundNode);
        nBoss->setChildren(_pchildren);
        //set parent as the new boss
        foundNode->setParent(nBoss);
    }
    return root;
}

//function to reset employee string
void company::resetEmployeeString(){
    allEmployees.clear();
}
