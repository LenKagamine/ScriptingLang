#include "include/Parser.h"

#include <iostream>

using namespace std;
int main(){
    try{
        Parser parser(Lexer("script.txt"));
        //parser.temp();
        vector<Node> ast = parser.parse();
        parser.print(ast, 1);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
