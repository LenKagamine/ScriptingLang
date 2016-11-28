#include "Parser.h"

#include <iostream>

using namespace std;

Parser::Parser(){
}

Token Parser::top(){
    return tokens[0];
}

Token Parser::pop(){
    Token t = top();
    tokens.erase(tokens.begin());
    return t;
}

/* <factor> := <iden>
             | <int>
*/
Node Parser::factor(){
    string nextToken = pop().getValue();
    Node node(new ASTNode(NODE_INT, nextToken));
    return node;
}

/* <term> := <factor> * <term>
           | <factor> / <term>
           | <factor>
*/
Node Parser::term(){
    Node f(factor());
    Token nextToken = top();
    while(!tokens.empty() && (nextToken.getValue() == "*" || nextToken.getValue() == "/")){
        pop();

        Node node(new ASTNode(NODE_BINOP, nextToken.getValue()));
        node->left = f;
        node->right = factor();
        f = node;

        nextToken = top();
    }
    return f;
}

/* <expr> := <term> + <expr>
           | <term> - <expr>
           | <term>
*/
Node Parser::expr(){
    Node t(term());
    Token nextToken = top();

    while(!tokens.empty() && (nextToken.getValue() == "+" || nextToken.getValue() == "-")){
        pop(); //"+" or "-"

        Node node(new ASTNode(NODE_BINOP, nextToken.getValue()));
        node->left = t;
        node->right = term();
        t = node;

        nextToken = top();
    }
    return t;
}

Node Parser::stmt(){
    Node node(new ASTNode);
    TokenType type = top().getType();

    if(type == TOK_VAR){ // declaration: var <iden> = <expr> ;
        pop(); //var
        string name = pop().getValue();
        Node left(new ASTNode(NODE_IDEN, name));
        pop(); //=
        Node right(expr());
        pop(); //;

        node->type = NODE_DECL;
        node->left = left;
        node->right = right;
    }
    else if(type == TOK_IDEN){ // assignment: <iden> = <expr> ;
        string name = pop().getValue();
        Node left(new ASTNode(NODE_IDEN, name));
        pop(); //=
        Node right(expr());
        pop(); //;

        node->type = NODE_DECL; //change to assignment node
        node->left = left;
        node->right = right;
    }
    else if(type == TOK_IF){ // if statement: if <expr> then <stmt>+ end
        pop(); //if
        Node cond(expr()); //condition
        pop(); //then
        vector<Node> block(stmts()); //statement block
        pop(); //end

        node->type = NODE_IF;
        node->cond = cond;
        node->block = block;
    }
    else if(type == TOK_PRINT){
        pop(); //print
        Node exp(expr());
        pop(); //;

        node->type = NODE_PRINT;
        node->exp = exp;
    }
    else{ // expression
        node = expr();
        pop();
    }
    return node;
}

vector<Node> Parser::stmts(){
    vector<Node> t;
    while(this->tokens.size() > 0){
        if(top().getType() == TOK_END) break;
        else t.push_back(stmt());
    }
    return t;
}

vector<Node> Parser::load(vector<Token> tokens){
    this->tokens = tokens;
    tree = stmts();
    return tree;
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
