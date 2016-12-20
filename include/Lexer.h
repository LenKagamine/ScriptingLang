#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "InputStream.h"

class Lexer{
    private:
        InputStream input;
        Token current;

    public:
        Lexer(std::string filename); //file name input

        void skip(); //skip whitespace and comments

        Token readNumber();
        Token readString();
        Token readIden();
        Token readOper();

        bool isPunct(char c);
        bool isOper(char c);

        Token step(); //get next token

        Token peek();
        Token next();
        bool eof();

        virtual ~Lexer();
    protected:
};

#endif // LEXER_H
