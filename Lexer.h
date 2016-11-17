#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "Token.h"

#include <iostream>
#include <vector>

using namespace std;

class Lexer{

public:
    Lexer();

    vector<Token> lex(string filename);

    ~Lexer();
};


#endif // LEXER_H_INCLUDED
