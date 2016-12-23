#include "Generator.h"

Generator::Generator(){}

void Generator::addInstruction(ByteCode op, std::string value){
    code.push_back(Instruction(op, value));
}

void Generator::generateNode(Node node){
    Node root(node);
    if(root){
        NodeType type = root->type;
        std::string value = root->value;

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
            case NODE_STR:
                addInstruction(PUSH, value);
                break;
            case NODE_FUNC: //implement functions
            case NODE_ARG:
                break;
        }
    }
}

std::vector<Instruction> Generator::generate(std::vector<Node> tree){
    for(unsigned int i=0;i<tree.size();i++){
        generateNode(tree[i]);
    }
    return code;
}

Generator::~Generator(){}
