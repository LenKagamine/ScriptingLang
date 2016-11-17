#include "VMachine.h"

using namespace std;

VMachine::VMachine(){
}

void VMachine::execute(vector<Instruction> insts){
    int ip = 0; //instruction pointer
    while(ip < insts.size()){
        cout << insts[ip].getName() << " " << insts[ip].getValue() << endl;
        switch(insts[ip].getOperation()){
        case NOP:
            break;

        case VAR:{
            VM_table[insts[ip].getValue()] = StackData();
            cout << "   new variable: " << insts[ip].getValue() << endl;
            break;
        }
        case ASN:{
            StackData value = VM_stack.top();
            VM_stack.pop();
            VM_table[insts[ip].getValue()] = value;
            cout << "   assign " << value.getNumber() << " to " << insts[ip].getValue() << endl;
            break;
        }
        case PRNT:{
            StackData var = VM_stack.top();
            VM_stack.pop();
            if(var.isNumber()) cout << var.getNumber() << endl;
            else if(var.isString()) cout << var.getString() << endl;
            break;
        }
        case PUSH:{
            string str = insts[ip].getValue();
            char* p;
            int value = strtol(str.c_str(), &p, 10);
            if(*p){ //just a string
                VM_stack.push(VM_table[insts[ip].getValue()]);
            }
            else{ //cast string to int
                VM_stack.push(insts[ip].getValue());
            }
            break;
        }
        case CMP:{
            StackData cond = VM_stack.top();
            VM_stack.pop();
            cout << ((cond.getNumber() == 0)?"false":"true") << endl;
            if(cond.getNumber() == 0){
                while(ip < insts.size() && insts[ip].getOperation() != END) ip++;
            }
            break;
        }
        case ADD:{
            StackData rhs = VM_stack.top();
            VM_stack.pop();
            StackData lhs = VM_stack.top();
            VM_stack.pop();

            if(lhs.isNumber() && rhs.isNumber())
                VM_stack.push(StackData(lhs.getNumber() + rhs.getNumber()));
            break;
        }
        case SUB:{
            StackData rhs = VM_stack.top();
            VM_stack.pop();
            StackData lhs = VM_stack.top();
            VM_stack.pop();

            if(lhs.isNumber() && rhs.isNumber())
                VM_stack.push(StackData(lhs.getNumber() - rhs.getNumber()));
            break;
        }
        case MULT:{
            StackData rhs = VM_stack.top();
            VM_stack.pop();
            StackData lhs = VM_stack.top();
            VM_stack.pop();

            if(lhs.isNumber() && rhs.isNumber())
                VM_stack.push(StackData(lhs.getNumber() * rhs.getNumber()));
            break;
        }
        case DIV:{
            StackData rhs = VM_stack.top();
            VM_stack.pop();
            StackData lhs = VM_stack.top();
            VM_stack.pop();

            if(lhs.isNumber() && rhs.isNumber())
                VM_stack.push(StackData(lhs.getNumber() / rhs.getNumber()));
            break;
        }
        }
        ip++;
    }
}

VMachine::~VMachine(){
}
