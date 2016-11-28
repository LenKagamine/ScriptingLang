#include "Lexer.h"

#include <fstream>
#include <cctype>

using namespace std;

Lexer::Lexer(){
}

vector<Token> Lexer::lex(string filename){
    //check filename is correct file extension

    ifstream input;
    input.open(filename.c_str());
    if(!input){
        cout << "Unable to load " << filename << "." << endl;
        return {};
    }

    vector<Token> tokens;

    string line;
    while(!input.eof()){
        getline(input, line);
        for(int i=0;i<line.length();i++){
            char c = line[i];

            // Arithmetic binops
            if(c == '+') tokens.push_back(Token(TOK_PLUS, "+"));
            else if(c == '-') tokens.push_back(Token(TOK_MINUS, "-"));
            else if(c == '*') tokens.push_back(Token(TOK_MULT, "*"));
            else if(c == '/'){
                // Line comments
                if(i+1 < line.length() && line[i+1] == '/'){
                    while(i < line.length() && line[i] != '\n') i++;
                }
                // Division
                else tokens.push_back(Token(TOK_DIV, "/"));
            }

            else if(c == '=') tokens.push_back(Token(TOK_EQUAL, "="));
            else if(c == ';') tokens.push_back(Token(TOK_SEMI, ";"));

            // Identifiers
            else if(isalpha(c)){
                string identifier(1, c);
                while(i+1 < line.length() && isalnum(line[i+1])) identifier += line[++i];

                TokenType tt;

                if(identifier == "var")         tt = TOK_VAR;
                else if(identifier == "if")     tt = TOK_IF;
                else if(identifier == "then")   tt = TOK_THEN;
                else if(identifier == "end")    tt = TOK_END;
                else if(identifier == "print")  tt = TOK_PRINT;

                // Other identifier
                else tt = TOK_IDEN;

                tokens.push_back(Token(tt, identifier));
            }

            // Integers
            else if(isdigit(c)){
                string number(1, c);
                while(i+1 < line.length() && isdigit(line[i+1])) number += line[++i];
                tokens.push_back(Token(TOK_INT, number));
            }

            // Unknown token
            else if(!isspace(c)){
                tokens.push_back(Token(TOK_NULL, string(1, c)));
            }
        }
    }

    input.close();

    return tokens;
}


Lexer::~Lexer(){
}
