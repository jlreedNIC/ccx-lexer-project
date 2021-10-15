/**
 * @file lexer.h
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief Lexical analyzer program.
 * 
 */

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <string>

class Lexer
{
    public:
        Lexer();                               // default constructor
        Lexer(const std::string &fileName);    // constructor with file name
        ~Lexer();                              // default destructor

        void lex();               // main parsing function
        void getChars();            // gets next char and one after
        void outputLexeme();        // outputs lexeme and token to out file

    private:
        std::string token;
        std::string lexeme;
        char currChar;          // next char
        char nextChar;          // next next char

        std::fstream inFile;
        std::fstream outFile;

        bool isSingleChar();
        bool isLetter();        // helper function
                                // checks if next char is a letter a-z or A-Z
        bool isWordPart();

        bool isNumber();

        bool isOpStart();
        void getOperator();

        void getToken();
        bool isKeyword();
};

#endif