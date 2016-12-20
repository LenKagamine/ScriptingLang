#include "Token.h"

Token::Token(){
}

Token::Token(TokenType tt, int val): type(tt), int_value(val){
}

Token::Token(TokenType tt, std::string val): type(tt), str_value(val){
}

Token::~Token(){
}
