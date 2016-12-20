#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <string>

class InputStream{
    private:
        int pos;
        std::string source;

    public:
        InputStream();
        InputStream(std::string filename);

        char peek();
        char get();
        char ignore();
        bool eof();

        virtual ~InputStream();

    protected:
};

#endif // INPUTSTREAM_H
