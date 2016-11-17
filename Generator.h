#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "Instruction.h"
#include "ASTNode.h"

#include <vector>

class Generator{

public:
    vector<Instruction> code;

    Generator();

    void addInstruction(ByteCode op, string value);

    vector<Instruction> generate(vector<shared_ptr<ASTNode>> tree);
    void generateNode(shared_ptr<ASTNode> node);

    ~Generator();
};

#endif // GENERATOR_H_INCLUDED
