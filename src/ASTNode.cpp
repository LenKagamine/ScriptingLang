#include "ASTNode.h"

ASTNode::ASTNode(){
}

ASTNode::ASTNode(NodeType type, std::string value){
    this->type = type;
    this->value = value;
}

ASTNode::ASTNode(std::vector<Node> stmts): type(NODE_STMTS), block(stmts){
}

ASTNode::~ASTNode(){
}
