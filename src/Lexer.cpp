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
    return Token(TOK_INT, value);
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
    if(value == "var") return Token(TOK_VAR, value);
    if(value == "if") return Token(TOK_IF, value);
    if(value == "print") return Token(TOK_PRINT, value);
    if(value == "function") return Token(TOK_FUNC, value);
    return Token(TOK_IDEN, value);
}

bool Lexer::isPunct(char c){
    std::string punctList = ",;(){}";
    return punctList.find_first_of(c) != std::string::npos;
}

Token Lexer::readPunct(){
    std::string value(1, input.get()); //puncutation is one character

    if(value == ",") return Token(TOK_COMMA, value);
    if(value == ";") return Token(TOK_SEMI, value);
    if(value == "(") return Token(TOK_LPAREN, value);
    if(value == ")") return Token(TOK_RPAREN, value);
    if(value == "{") return Token(TOK_LBRACE, value);
    if(value == "}") return Token(TOK_RBRACE, value);

    throw LexerException("Unknown punctuation: " + value);
}

bool Lexer::isOper(char c){
    std::string operList = "+-*/=";
    return operList.find_first_of(c) != std::string::npos;
}

Token Lexer::readOper(){
    std::string value;
    while(!input.eof() && isOper(input.peek())){
        value += input.get();
    }
    if(value == "+") return Token(TOK_PLUS, value);
    if(value == "-") return Token(TOK_MINUS, value);
    if(value == "*") return Token(TOK_MULT, value);
    if(value == "/") return Token(TOK_DIV, value);
    if(value == "=") return Token(TOK_EQUAL, value);

    throw LexerException("Unknown operation: " + value);
}

Token Lexer::step(){
    skip();

    if(input.eof()) return Token(TOK_NULL, ""); //null token

    char peek = input.peek();

    if(peek == '"') return readString();
    if(isdigit(peek)) return readNumber();
    if(isalpha(peek)) return readIden();
    if(isPunct(peek)) return readPunct();
    if(isOper(peek)) return readOper();

    throw LexerException("Unknown character: " + peek);
}

Token Lexer::peek(){
    return current;
}

Token Lexer::next(){ //should next have a check like consume?
    Token tok = current;
    current = step();
    return tok;
}

void Lexer::consume(std::string tok){
    if(tok != current.getValue()) throw LexerException("consume expected '" + tok + "', got '" + current.getValue() + "'");
    current = step();
}

bool Lexer::eof(){
    Token tok = peek();
    return tok.getType() == TOK_NULL;
}


Lexer::~Lexer(){}
