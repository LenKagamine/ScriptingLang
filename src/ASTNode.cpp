#include "ASTNode.h"

ASTNode::ASTNode(){
}

ASTNode::ASTNode(NodeType type, std::string value){
    this->type = type;
    this->value = value;
}

ASTNode::~ASTNode(){
}
