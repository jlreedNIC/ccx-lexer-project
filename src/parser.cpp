#include "parser.h"

Parser::Parser()
{

}

Parser::Parser(const std::string &fileName)
{
    std::fstream file;

    file.open(fileName);
    if(!file)
    {
        std::cerr << "Error opening file.\n";
        exit(1);
    }

    else std::cout << "Opened " << fileName << " file\n";
}

Parser::~Parser()
{

}