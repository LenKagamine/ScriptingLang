#include "Lexer.h"
#include "Parser.h"
#include "Generator.h"
#include "VMachine.h"

using namespace std;

const bool debug = true; // debug output except for vm

int main(){

    Lexer lexer;
    vector<Token> tokens = lexer.lex("test.txt");

    if(debug){
        cout << "******* tokens ********\n";
        for(Token t: tokens){
            cout << t.getValue() << " ";
            if(t.getValue() == ";") cout << endl;
        }
        cout << endl;
    }


    Parser parser;
    vector<shared_ptr<ASTNode>> tree = parser.load(tokens);

    if(debug){
        cout << "******* ast ********\n";
        parser.print(tree, 1);
    }

    Generator gen;
    vector<Instruction> code = gen.generate(tree);

    if(debug){
        cout << "******* code ********\n";
        for(Instruction i: code) cout << i.getName() << " " << i.getValue() << endl;
        cout << endl << endl;
    }

    VMachine vm;
    vm.execute(code);
    return 0;
}
