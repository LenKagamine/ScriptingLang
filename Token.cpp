#include "Token.h"

using namespace std;

Token::Token(){
}

Token::Token(TokenType t, string v){
    type = t;
    value = v;
}

TokenType Token::getType(){
    return type;
}

string Token::getValue(){
    return value;
}

Token::~Token(){
}
