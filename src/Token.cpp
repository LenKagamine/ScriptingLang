#include "Token.h"

#include <iostream>

Token::Token(){}

Token::Token(TokenType tt, std::string val): type(tt), value(val){}

TokenType Token::getType(){
    return type;
}

std::string Token::getValue(){
    return value;
}

Token::~Token(){}
