#include "Token.h"

#include <iostream>

Token::Token(){}

Token::Token(TokenType tt, std::string val): type(tt), value(val){}

Token::~Token(){}
