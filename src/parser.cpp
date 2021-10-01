#include "parser.h"

Parser::Parser()
{

}

Parser::Parser(const std::string &fileName)
{
    // open input file
    inFile.open(fileName);
    if(!inFile)
    {
        std::cerr << "Error opening file.\n";
        exit(1);
    }

    else std::cout << "Opened " << fileName << " file\n";

    // open output file
    outFile.open(fileName + ".lexer.out", std::ios::out);
}

Parser::~Parser()
{
    // close files
    inFile.close();
    outFile.close();

    std::cout << "Closed files.\n";
}

void Parser::parse()
{
    while(!inFile.eof())
    {
        getChars();
    }

}

void Parser::getChars()
{
    // FIX:why doesn't !inFile work?
    if(!inFile.eof())
    {
        inFile.get(nextChar);
        inFile.get(secondChar);
    }
}

void Parser::outputLexeme()
{
    outFile << lexeme << "\n";
}