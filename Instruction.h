#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <string>

using namespace std;

enum ByteCode{ //bytecode instructions (Add more with more instructions)
    NOP,    //no operation
    VAR,    //variable declaration
    ASN,    //assign
    PRNT,    //print
    PUSH,   //push value

    ADD,    //addition
    SUB,    //subtraction
    MULT,   //multiplication
    DIV,    //division

    IF,
    CMP,
    END
};

class Instruction{
    string OpCode[12] = {"nop", "variable", "assign", "print", "push", "add", "subtract", "multiply", "divide", "if", "cmp", "end"};

    int op;      //operation
    string value;   //value

public:
    Instruction();
    Instruction(int op, string value);

    int getOperation();
    string getValue();

    string getName();

    ~Instruction();
};

#endif // INSTRUCTION_H_INCLUDED
