#include "Generator.h"

#include <iostream>

using namespace std;

Generator::Generator(){
}

void Generator::addInstruction(ByteCode op, string value){
    code.push_back(Instruction(op, value));
}

void Generator::generateNode(shared_ptr<ASTNode> node){
    shared_ptr<ASTNode> root(node);
    if(root){
        NodeType type = root->type;
        string value = root->value;

        switch(type){
            case NODE_DECL:
                addInstruction(VAR, node->left->value);
                generateNode(node->right);
                addInstruction(ASN, node->left->value);
                break;
            case NODE_BINOP:
                generateNode(node->left);
                generateNode(node->right);
                if(value == "+") addInstruction(ADD, value);
                else if(value == "-") addInstruction(SUB, value);
                else if(value == "*") addInstruction(MULT, value);
                else if(value == "/") addInstruction(DIV, value);
                break;
            case NODE_PRINT:
                generateNode(node->exp);
                addInstruction(PRNT, "");
                break;
            case NODE_IF:
                generateNode(node->cond);
                addInstruction(CMP, "");
                generate(node->block);
                addInstruction(END, "");
                break;
            case NODE_IDEN:
            case NODE_INT:
                addInstruction(PUSH, value);
                break;
        }
    }
}

vector<Instruction> Generator::generate(vector<shared_ptr<ASTNode>> tree){
    for(unsigned int i=0;i<tree.size();i++){
        generateNode(tree[i]);
    }
    return code;
}

Generator::~Generator(){
}
