#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "InputStream.h"

#include <stdexcept>

class Lexer{
    private:
        InputStream input;
        Token current;

        void skip(); //skip whitespace and comments

        Token readNumber();
        Token readString();
        Token readIden();
        Token readPunct();
        Token readOper();

        bool isPunct(char c);
        bool isOper(char c);

        Token step(); //get next token

    public:
        Lexer(std::string filename); //file name input

        Token peek();
        Token next();
        void consume(std::string tok);
        bool eof();

        virtual ~Lexer();
    protected:
};

struct LexerException: public std::runtime_error{
    explicit LexerException(const std::string& str): std::runtime_error("Lexer: " + str){}
    virtual ~LexerException() throw(){}
};

#endif // LEXER_H
