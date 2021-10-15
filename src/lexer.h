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

        void lex();                 // main parsing function
        void getChars();            // gets next char and one after
        void outputLexeme();        // outputs lexeme and token to out file

    private:
        std::string token;
        std::string lexeme;
        char currChar;          // next char
        char nextChar;          // next next char

        std::fstream inFile;
        std::fstream outFile;

        bool isCommentStart();      // checks to see if start of a comment, /*
        void getComment();          // gets comment into lexeme and sets token

        bool isSingleChar();        // checks if currChar is a single char
        bool isLetter();            // checks if currChar is a letter a-z or A-Z
        bool isWordPart();          // checks if currChar is part of a valid word (including nums and special chars)
        void getWord();             // gets word into lexeme
        bool isKeyword();           // checks if word matches any keywords
        void getToken();            // sets token to keyword or identifier

        bool isStringStart();       // checks for start of string "
        void getString();           // puts whole string into lexeme and sets token

        bool isNumber();            // checks for a number

        bool isOpStart();           // checks for start of an operator, or a single operator
        void getOperator();         // gets operator (even if double char) and puts into lexeme and sets token

        
};

#endif