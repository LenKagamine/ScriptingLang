#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "ASTNode.h"

class Parser
{
    private:
        Lexer lexer;

    public:
        Parser(Lexer lex);
        void temp();

        Node stmt();
        Node expr();
        Node term();
        Node factor();
        std::vector<Node> parse();

        void print(std::vector<Node> tree, int depth);
        void print(Node node, int depth);

        virtual ~Parser();

    protected:
};

#endif // PARSER_H
