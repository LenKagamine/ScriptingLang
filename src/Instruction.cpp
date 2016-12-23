#include "Instruction.h"

Instruction::Instruction(int oper, std::string val): op(oper), value(val){}

int Instruction::getOperation(){
    return op;
}

std::string Instruction::getName(){
    return OpCode[op];
}

std::string Instruction::getValue(){
    return value;
}
