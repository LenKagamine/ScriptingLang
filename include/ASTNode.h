#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

enum NodeType{
    NODE_INT,
    NODE_BINOP,
    NODE_DECL,
    NODE_IDEN,
    NODE_PRINT,

    NODE_IF,
    NODE_STMTS
};

class ASTNode;

typedef std::shared_ptr<ASTNode> Node;

class ASTNode{
    public:
        NodeType type;
        std::string value;

        //decl, assign, binop
        Node left;
        Node right;

        //if, while
        Node cond;
        std::vector<Node> block;

        //print
        Node exp;

        ASTNode();
        ASTNode(NodeType type, std::string value);
        ASTNode(std::vector<Node> stmts);

        ~ASTNode();
};

#endif // AST_H
