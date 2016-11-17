#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "Token.h"
#include "ASTNode.h"

#include <vector>
#include <memory>

typedef shared_ptr<ASTNode> Node;

class Parser{
public:
    vector<Node> tree;
    vector<Token> tokens;

    Parser();

    vector<shared_ptr<ASTNode>> load(vector<Token> tokens);

    vector<Node> stmts();
    shared_ptr<ASTNode> stmt();
    shared_ptr<ASTNode> expr();
    shared_ptr<ASTNode> term();
    shared_ptr<ASTNode> factor();

    Token top();
    Token pop();

    void print(vector<Node> tree, int depth);
    void print(Node node, int depth);

    ~Parser();
};


#endif // PARSER_H_INCLUDED
