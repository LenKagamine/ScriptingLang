#include "InputStream.h"

#include <fstream>

InputStream::InputStream(){
}

InputStream::InputStream(std::string filename){
	std::ifstream input("script.txt");
	source = std::string((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    pos = 0;
}

char InputStream::peek(){
    if(pos >= source.length()) throw "InputStream: Cannot peek, end of file";
    return source[pos];
}

char InputStream::get(){
    if(pos >= source.length()) throw "InputStream: Cannot peek, end of file";
    return source[pos++];
}

char InputStream::ignore(){
    ++pos;
}

bool InputStream::eof(){
    return pos >= source.length();
}

InputStream::~InputStream(){
    //dtor
}
