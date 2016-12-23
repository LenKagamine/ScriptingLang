#ifndef STACKDATA_H_INCLUDED
#define STACKDATA_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;

class StackData{
    int nullint = -123456789; //random null value
    string nullstr = "NULL";

    int ivalue;
    string svalue;

public:
    StackData();
    StackData(int number);
    StackData(string str);

    bool isNumber();
    bool isString();

    int getNumber();
    string getString();

    ~StackData();
};

#endif // STACKDATA_H_INCLUDED
