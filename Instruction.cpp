#include "Instruction.h"

Instruction::Instruction(){
}

Instruction::Instruction(int op, string value){
    this->op = op;
    this->value = value;
}

int Instruction::getOperation(){
    return op;
}

string Instruction::getValue(){
    return value;
}

string Instruction::getName(){
    return OpCode[op];
}

Instruction::~Instruction(){
}
