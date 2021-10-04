/**
 * @file lexer.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief Lexical analyzer program.
 * 
 */

#include "lexer.h"

Lexer::Lexer()
{

}

Lexer::Lexer(const std::string &fileName)
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
    outFile.open(fileName + ".test.lexer.out", std::ios::out);
    if(!outFile)
    {
        std::cerr << "Could not open output file.\n";
        exit(1);
    }
    else std::cout << "Opened " << fileName << ".test.lexer.out file\n";
}

Lexer::~Lexer()
{
    // close files
    inFile.close();
    outFile.close();

    std::cout << "Closed files.\n";
}

void Lexer::lex()
{
    // get char
    // add to lexeme
    // check for what token it fits
        // go to that function
    // loop

    while(!inFile.eof())
    {
        getChars();

        lexeme = currChar;
        token = "\n"; // reset token

        // comment
        if(currChar == '/' && nextChar == '*')
        {
            // getComment();
            do
            {
                getChars();
                lexeme += currChar;
            } while (currChar != '*' || nextChar != '/');
            getChars();
            lexeme += currChar;

            token = " (comment)\n";
        }

        // word
        if(isLetter())
        {
            // getWord();
            do
            {
                getChars();
                lexeme += currChar;
            } while (isLetter());

            // getToken();
            token = " (placeholder)\n";            
        }

        // string
        if(currChar == '\"')
        {
            // getString();
            do
            {
                getChars();
                lexeme += currChar;
            } while (currChar != '\"');

            token = " (string)\n";            
        }

        // space
        if(currChar == ' ' || currChar == '\n')
        {
            // ignore space
            lexeme = "";
            token = "";
        }

        // have full lexeme and token is set
        lexeme += token;
        outputLexeme();
    }
}

void Lexer::getChars()
{
    // FIX:why doesn't !inFile work?
    if(!inFile.eof())
    {
        inFile.get(currChar);
        nextChar = inFile.peek();
    }
}

void Lexer::outputLexeme()
{
    outFile << lexeme;
}

// checks to see if currChar and nextChar are part of a word (an alphabet char or numeric char or '_')
bool Lexer::isLetter()
{
    bool cLetter = (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || currChar == '_';
    bool nLetter = (nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || 
                    nextChar == '_' || (nextChar >= '0' && nextChar <= '9');
    return cLetter && nLetter;
}

// checks to see if currChar and nextChar are numbers
bool Lexer::isNumber()
{
    bool cNumber = (currChar >= '0' && currChar <= '9');
    bool nNumber = (nextChar >= '0' && nextChar <= '9');
    return cNumber && nNumber;
}