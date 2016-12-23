#ifndef VMACHINE_H_INCLUDED
#define VMACHINE_H_INCLUDED

#include "Instruction.h"
#include "StackData.h"

#include <vector>
#include <stack>
#include <unordered_map>

class VMachine{
    private:
        std::stack<StackData> VM_stack;       //stack of values
        std::unordered_map<std::string, StackData> VM_table; //hash table for variables

    public:
        VMachine();

        void execute(std::vector<Instruction> insts);

        ~VMachine();
};

#endif // VMACHINE_H_INCLUDED
