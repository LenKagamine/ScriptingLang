#include "ASTNode.h"

ASTNode::ASTNode(){
}

ASTNode::ASTNode(NodeType type, string value){
    this->type = type;
    this->value = value;
}

ASTNode::~ASTNode(){
}
