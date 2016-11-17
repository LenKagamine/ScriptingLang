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

            if(c == '+') tokens.push_back(Token(TOK_PLUS, "+"));
            else if(c == '-') tokens.push_back(Token(TOK_MINUS, "-"));
            else if(c == '*') tokens.push_back(Token(TOK_MULT, "*"));
            else if(c == '/'){
                if(i+1 < line.length() && line[i+1] == '/'){
                    //remove line comments
                    while(i < line.length() && line[i] != '\n') i++;
                }
                else tokens.push_back(Token(TOK_DIV, "/"));
            }

            else if(c == '=') tokens.push_back(Token(TOK_EQUAL, "="));
            else if(c == ';') tokens.push_back(Token(TOK_SEMI, ";"));
            else if(isalpha(c)){
                string identifier(1, c);
                while(i+1 < line.length() && isalnum(line[i+1])) identifier += line[++i];

                if(identifier == "var"){
                    tokens.push_back(Token(TOK_VAR, identifier));
                }
                else if(identifier == "if"){
                    tokens.push_back(Token(TOK_IF, identifier));
                }
                else if(identifier == "then"){
                    tokens.push_back(Token(TOK_THEN, identifier));
                }
                else if(identifier == "end"){
                    tokens.push_back(Token(TOK_END, identifier));
                }
                else if(identifier == "print") tokens.push_back(Token(TOK_PRINT, identifier));
                else tokens.push_back(Token(TOK_IDEN, identifier));
            }

            else if(isdigit(c)){
                string number(1, c);
                while(i+1 < line.length() && isdigit(line[i+1])) number += line[++i];
                tokens.push_back(Token(TOK_INT, number));
            }

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
