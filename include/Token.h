#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType{
    TOK_INT, TOK_STR, TOK_IDEN, TOK_PUNCT, TOK_OPER, TOK_NULL
};

struct Token{
    TokenType type;
    int int_value; // put in union?
    std::string str_value;

    Token();

    Token(TokenType tt, int val);

    Token(TokenType tt, std::string val);

    virtual ~Token();
};

#endif // TOKEN_H
