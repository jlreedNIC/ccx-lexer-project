#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>


class Parser
{
    public:
        Parser();                               // default constructor
        Parser(const std::string &fileName);    // constructor with file name
        ~Parser();                              // default destructor

        void parse();               // main parsing function
        void getChars();            // gets next char and one after
        void outputLexeme();        // outputs lexeme and token to out file

    private:
        std::string token;
        std::string lexeme;
        char currChar;          // next char
        char nextChar;        // next next char

        std::fstream inFile;
        std::fstream outFile;

        bool isLetter();        // helper function
                                // checks if next char is a letter a-z or A-Z
};


#endif