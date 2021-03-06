#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType{
    TOK_INT, TOK_STR, //variable types
    TOK_IDEN, TOK_VAR, TOK_PRINT, TOK_IF, TOK_FUNC, //identifier
    TOK_COMMA, TOK_SEMI, TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, //punctutation
    TOK_PLUS, TOK_MINUS, TOK_MULT, TOK_DIV, TOK_EQUAL, //operation
    TOK_NULL //end token
};

class Token{
    private:
        TokenType type;
        std::string value;

    public:
        Token();
        Token(TokenType tt, std::string val);

        TokenType getType();
        std::string getValue();

        virtual ~Token(); //is this necessary?
};

#endif // TOKEN_H
