#include "include/Parser.h"
#include "include/Generator.h"
#include "include/VMachine.h"

#include <iostream>

using namespace std;
int main(){
    try{
        Parser parser(Lexer("script.txt"));
        vector<Node> ast = parser.parse();
        parser.print(ast, 1);

        Generator gen;
        vector<Instruction> code = gen.generate(ast);
        cout << "******* code ********\n";
        for(Instruction i: code) cout << i.getName() << " " << i.getValue() << endl;
        cout << endl << endl;

        VMachine vm;
        vm.execute(code);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
