#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>

using namespace std;

enum TokenType{
    TOK_VAR, TOK_EQUAL, TOK_IDEN,               //declaration
    TOK_SEMI,
    TOK_IF, TOK_THEN, TOK_END,                  //if
    TOK_PLUS, TOK_MINUS, TOK_MULT, TOK_DIV,     //binops
    TOK_PRINT,
    TOK_INT, TOK_NULL                           //static types
};

class Token{
    TokenType type;
    string value;

public:
    Token();
    Token(TokenType t, string v);

    TokenType getType();
    string getValue();

    ~Token();
};

#endif // TOKEN_H_INCLUDED
