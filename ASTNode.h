#ifndef ASTNODE_H_INCLUDED
#define ASTNODE_H_INCLUDED

#include <vector>
#include <memory>
#include <string>

using namespace std;

enum NodeType{
    NODE_INT,
    NODE_BINOP,
    NODE_DECL,
    NODE_IDEN,
    NODE_PRINT,

    NODE_IF,
    NODE_STMTS
};

class ASTNode{

public:
    NodeType type;
    string value;

    //decl, assign, binop
    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;

    //if, while
    shared_ptr<ASTNode> cond;
    vector<shared_ptr<ASTNode>> block;

    //print
    shared_ptr<ASTNode> exp;

    ASTNode();
    ASTNode(NodeType type, string value);

    ~ASTNode();
};

#endif // ASTNODE_H_INCLUDED
