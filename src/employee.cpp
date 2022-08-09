#include "employee.h"
#include <iostream>
using namespace std;

//constructor 1 (set default values similar to 'init' in python)
employee::employee(){
    setFirstName("Name");
    setPhoneNumber("N/A");
}

//construtor 2 (with both arguments)
employee::employee(string s, string p){
    setFirstName(s);
    setPhoneNumber(p);
}

//method to set first name
void employee::setFirstName(string s){
    firstName = s;
}

//method to set phone number
void employee::setPhoneNumber(string p){
    phoneNumber = p;
}

//method to print details
void employee::printDetails(){
    cout << "Name: " << firstName << endl;
    cout << "Phone #: " << phoneNumber << endl;
}

string employee::getName(){
    return firstName;
}
