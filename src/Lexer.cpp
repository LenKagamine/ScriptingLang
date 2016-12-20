#include "Lexer.h"

#include <fstream>
#include <cctype>

Lexer::Lexer(std::string filename){ //make file extension check maybe
    input = InputStream(filename);
    current = step();
}

void Lexer::skip(){
    while(!input.eof() && (input.peek() == ' ' || input.peek() == '\n' || input.peek() == '\r' || input.peek() == '\t' ||
                           input.peek() == '#')){
        if(input.peek() == '#'){ // line comment
            do{
                input.ignore();
            } while(input.peek() != '\n' && input.peek() != '\n');
        }
        else{
            input.ignore();
        }
    }
}

Token Lexer::readNumber(){
    std::string value;
    char peek = input.peek();
    while(!input.eof() && isdigit(peek)){
        value += input.get();
        peek = input.peek();
    }
    return Token(TOK_INT, std::stoi(value));
}

Token Lexer::readString(){
    std::string value;
    input.ignore(); // "
    while(!input.eof() && input.peek() != '"'){
        value += input.get();
    }
    input.ignore(); // "
    return Token(TOK_STR, value);
}

Token Lexer::readIden(){
    std::string value;
    while(!input.eof() && isalpha(input.peek())){
        value += input.get();
    }
    return Token(TOK_IDEN, value);
}

bool Lexer::isPunct(char c){
    std::string punctList = ",;(){}[]";
    return punctList.find_first_of(c) != std::string::npos;
}

bool Lexer::isOper(char c){
    std::string operList = "+-*/%=&|<>!";
    return operList.find_first_of(c) != std::string::npos;
}

Token Lexer::readOper(){
    std::string value;
    while(!input.eof() && isOper(input.peek())){
        value += input.get();
    }
    return Token(TOK_OPER, value);
}

Token Lexer::step(){
    skip();

    if(input.eof()) return Token(TOK_NULL, 0);

    char peek = input.peek();

    if(peek == '"') return readString();
    if(isdigit(peek)) return readNumber();
    if(isalpha(peek)) return readIden();
    if(isPunct(peek)) return Token(TOK_PUNCT, std::string(1, input.get()));
    if(isOper(peek)) return readOper();

    throw "Unknown character: " + peek;
}

Token Lexer::peek(){
    return current;
}

Token Lexer::next(){
    Token tok = current;
    current = step();
    return tok;
}

bool Lexer::eof(){
    Token tok = peek();
    return tok.type == TOK_NULL;
}


Lexer::~Lexer(){
}
