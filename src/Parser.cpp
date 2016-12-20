#include "Parser.h"

#include <iostream>
using namespace std;
Parser::Parser(Lexer lex): lexer(lex){}

void Parser::temp(){
    while(!lexer.eof()){
        Token t = lexer.next();
        if(t.type == TOK_INT) cout << "int  : " << t.int_value << endl;
        else if(t.type == TOK_STR) cout << "str  : " << t.str_value << endl;
        else if(t.type == TOK_IDEN) cout << "iden : " << t.str_value << endl;
        else if(t.type == TOK_PUNCT) cout << "punct: " << t.str_value << endl;
        else if(t.type == TOK_OPER) cout << "oper : " << t.str_value << endl;
    }
}

Node Parser::factor(){
    if(lexer.peek().type == TOK_INT){
        int nextToken = lexer.next().int_value;
        Node node(new ASTNode(NODE_INT, to_string(nextToken)));
        return node;
    }
    else{
        string nextToken = lexer.next().str_value;
        Node node(new ASTNode(NODE_IDEN, nextToken));
        return node;
    }
}

Node Parser::term(){
    Node f(factor());
    Token nextToken = lexer.peek();
    while(!lexer.eof() && (nextToken.str_value == "*" || nextToken.str_value == "/")){
        lexer.next();

        Node node(new ASTNode(NODE_BINOP, nextToken.str_value));
        node->left = f;
        node->right = factor();
        f = node;

        nextToken = lexer.peek();
    }
    return f;
}

Node Parser::expr(){
    Node t(term());
    Token nextToken = lexer.peek();

    while(!lexer.eof() && (nextToken.str_value == "+" || nextToken.str_value == "-")){
        lexer.next();

        Node node(new ASTNode(NODE_BINOP, nextToken.str_value));
        node->left = t;
        node->right = term();
        t = node;

        nextToken = lexer.peek();
    }
    return t;
}

Node Parser::stmt(){
    Node node(new ASTNode);
    TokenType type = lexer.peek().type;

    if(type == TOK_IDEN && lexer.peek().str_value == "var"){
        lexer.next();
        std::string name = lexer.next().str_value;
        Node left(new ASTNode(NODE_IDEN, name));
        lexer.next();
        Node right(expr());
        lexer.next();

        node->type = NODE_DECL;
        node->left = left;
        node->right = right;
    }
    else if(type == TOK_IDEN && lexer.peek().str_value == "if"){
        lexer.next();
        Node cond(expr());
        lexer.next();
        vector<Node> block(parse());
        lexer.next();

        node->type = NODE_IF;
        node->cond = cond;
        node->block = block;
    }
    else if(type == TOK_IDEN && lexer.peek().str_value == "print"){
        lexer.next();
        Node exp(expr());
        lexer.next();

        node->type = NODE_PRINT;
        node->exp = exp;
    }
    else{
        node = expr();
        lexer.next();
    }

    return node;
}

std::vector<Node> Parser::parse(){
    std::vector<Node> stmts;
    while(!lexer.eof()){
        stmts.push_back(stmt());
        if(lexer.peek().type == TOK_PUNCT && lexer.peek().str_value == "}") break; // eww
    }
    return stmts;
}

void Parser::print(Node node, int depth){
    string nodetype_str[] = {"NODE_INT","NODE_BINOP","NODE_DECL","NODE_IDEN","NODE_PRINT","NODE_IF","NODE_STMTS"};
    Node root(node);
    if(root){
        string tab;
        for(int i=0;i<depth;i++) tab += "  ";
        cout << nodetype_str[root->type] << ", " << root->value << endl;
        if(node->left){
            cout << tab;
            cout << "left: ";
            print(node->left, depth+1);
        }
        if(node->right){
            cout << tab;
            cout << "right: ";
            print(node->right, depth+1);
        }
        if(node->exp){
            cout << tab;
            cout << "exp: ";
            print(node->exp, depth+1);
        }
        if(node->cond){
            cout << tab;
            cout << "cond: ";
            print(node->cond, depth+1);
        }
        if(!node->block.empty()){
            cout << tab;
            cout << "block: ";
            print(node->block, depth+1);
        }
    }
}

void Parser::print(vector<Node> tree, int depth){
    for(unsigned int i=0;i<tree.size();i++){
        print(tree[i], depth);
    }
}

Parser::~Parser(){
}
