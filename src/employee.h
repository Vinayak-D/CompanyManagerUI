#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std;
#pragma once

class employee {
public:
    //constructors
    employee();
    employee(string s, string p);
    //methods
    void setFirstName(string s);
    void setPhoneNumber(string p);
    void printDetails();
    string getName();

private:
    string firstName;
    string phoneNumber;
};

#endif
