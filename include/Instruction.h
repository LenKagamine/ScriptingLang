#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

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
    private:
        std::string OpCode[12] = {"nop", "variable", "assign", "print", "push", "add", "subtract", "multiply", "divide", "if", "cmp", "end"};

        int op;         //operation
        std::string value;   //value

    public:
        Instruction(int op, std::string value);

        int getOperation();
        std::string getName();
        std::string getValue();
};

#endif // INSTRUCTION_H
