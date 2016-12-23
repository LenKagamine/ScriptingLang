#include "StackData.h"

using namespace std;

inline bool isInteger(const string &s){
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char *p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}

StackData::StackData(){
    ivalue = nullint;
    svalue = nullstr;
}

StackData::StackData(int number){
    ivalue = number;
    svalue = nullstr;
    cout << "   pushed int " << ivalue << endl;
}

StackData::StackData(string str){
    if(isInteger(str)){ //just a string
        ivalue = stoi(str);
        svalue = nullstr;
        cout << "   pushed int " << ivalue << endl;
    }
    else{ //cast string to int
        svalue = str;
        ivalue = nullint;
        cout << "   pushed string " << svalue << endl;
    }
}

bool StackData::isNumber(){
    return ivalue != nullint;
}

bool StackData::isString(){
    return svalue != nullstr;
}

int StackData::getNumber(){
    return ivalue;
}

string StackData::getString(){
    return svalue;
}

StackData::~StackData(){
}
