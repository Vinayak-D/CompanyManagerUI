#include "treeNode.h"
#include "employee.h"
#include <iostream>
using namespace std;

//constructor
treeNode::treeNode(string s, string p):emp(s,p){

}

//method to print employee details
string treeNode::returnEmp(){
    return emp.getName();
}

//method to edit employee details
void treeNode::editEmpDetails(string s, string p){
    emp.setFirstName(s);
    emp.setPhoneNumber(p);
}

//method to return vector of children
vector <treeNode*> treeNode::returnChildren(){
    return children;
}

//method to retun parent
treeNode* treeNode::returnParent(){
    return parent;
}

//method to set the children of the node
void treeNode::setChildren(vector <treeNode*> _children){
    children = _children;
}

//method to set the parent of the node
void treeNode::setParent(treeNode* _parent){
    parent = _parent;
}
