#include "Parser.h"

#include <iostream>
using namespace std;

Parser::Parser(Lexer lex): lexer(lex){}

void Parser::temp(){
    while(!lexer.eof()){
        Token t = lexer.next();
        if(t.type == TOK_INT) cout << "int  : " << t.value << endl;
        else if(t.type == TOK_STR) cout << "str  : " << t.value << endl;
        else if(t.type == TOK_IDEN) cout << "iden : " << t.value << endl;
        else cout << "other: " << t.value << endl;
    }
}

Node Parser::factor(){
    Token nextToken = lexer.next();
    Node node;
    if(nextToken.type == TOK_INT){
        node = Node(new ASTNode(NODE_INT, nextToken.value));
    }
    else if(nextToken.type == TOK_STR){
        node = Node(new ASTNode(NODE_STR, nextToken.value));
    }
    else{
        node = Node(new ASTNode(NODE_IDEN, nextToken.value));
    }
    return node;
}

Node Parser::term(){
    Node f(factor());
    Token nextToken = lexer.peek();
    while(!lexer.eof() && (nextToken.type == TOK_MULT || nextToken.type == TOK_DIV)){
        lexer.next();

        Node node(new ASTNode(NODE_BINOP, nextToken.value));
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

    while(!lexer.eof() && (nextToken.type == TOK_PLUS || nextToken.type == TOK_MINUS)){
        lexer.next();

        Node node(new ASTNode(NODE_BINOP, nextToken.value));
        node->left = t;
        node->right = term();
        t = node;

        nextToken = lexer.peek();
    }
    return t;
}

std::vector<Node> Parser::args(){
    vector<Node> arglist;
    if(lexer.peek().type == TOK_RPAREN) return arglist; //no arguments

    std::string name = lexer.next().value;
    arglist.push_back(Node(new ASTNode(NODE_ARG, name)));

    while(lexer.peek().type == TOK_COMMA){
        lexer.consume(",");
        name = lexer.next().value;
        arglist.push_back(Node(new ASTNode(NODE_ARG, name)));
    }
    return arglist;
}

Node Parser::stmt(){
    Node node(new ASTNode);
    TokenType type = lexer.peek().type;

    if(type == TOK_VAR){
        lexer.consume("var");
        std::string name = lexer.next().value;
        Node left(new ASTNode(NODE_IDEN, name));
        lexer.consume("=");
        Node right(expr());
        lexer.consume(";");

        node->type = NODE_DECL;
        node->left = left;
        node->right = right;
    }
    else if(type == TOK_IF){
        lexer.consume("if");
        lexer.consume("(");
        Node cond(expr());
        lexer.consume(")");
        lexer.consume("{");
        vector<Node> block(parse());
        lexer.consume("}");

        node->type = NODE_IF;
        node->cond = cond;
        node->block = block;
    }
    else if(type == TOK_PRINT){
        lexer.consume("print");
        Node exp(expr());
        lexer.consume(";");

        node->type = NODE_PRINT;
        node->exp = exp;
    }
    else if(type == TOK_FUNC){
        lexer.consume("function");
        std::string name = lexer.next().value;
        lexer.consume("(");
        vector<Node> param(args());
        lexer.consume(")");
        lexer.consume("{");
        vector<Node> block(parse());
        lexer.consume("}");

        node->type = NODE_FUNC;
        node->value = name;
        node->param = param;
        node->block = block;
    }
    else{
        node = expr(); //should this be an error?
        lexer.consume(";");
    }

    return node;
}

std::vector<Node> Parser::parse(){
    std::vector<Node> stmts;
    while(!lexer.eof() && lexer.peek().type != TOK_RBRACE){
        stmts.push_back(stmt());
    }
    return stmts;
}

void Parser::print(Node node, int depth){
    string nodetype_str[] = {"NODE_INT","NODE_STR","NODE_BINOP","NODE_DECL","NODE_IDEN","NODE_PRINT","NODE_IF","NODE_FUNC","NODE_ARG","NODE_STMTS"};
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
        if(!node->param.empty()){
            cout << tab;
            cout << "param: \n";
            print(node->param, depth+1);
        }
        if(!node->block.empty()){
            cout << tab;
            cout << "block: \n";
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
