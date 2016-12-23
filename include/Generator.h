#ifndef GENERATOR_H
#define GENERATOR_H

#include "ASTNode.h"
#include "Instruction.h"

struct Generator{
    std::vector<Instruction> code;

    Generator();

    void addInstruction(ByteCode op, std::string value);
    std::vector<Instruction> generate(std::vector<Node> tree);
    void generateNode(Node node);

    virtual ~Generator();
};

#endif // GENERATOR_H
