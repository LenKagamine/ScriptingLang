#ifndef VMACHINE_H_INCLUDED
#define VMACHINE_H_INCLUDED

#include "Instruction.h"
#include "StackData.h"

#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class VMachine{
    stack<StackData> VM_stack;       //stack of values
    unordered_map<string, StackData> VM_table; //hash table for variables

public:
    VMachine();

    void execute(vector<Instruction> insts);

    ~VMachine();
};

#endif // VMACHINE_H_INCLUDED
