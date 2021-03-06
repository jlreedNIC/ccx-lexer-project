/**
 * @file main.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief A lexical analyzer program.
 */

#include "lexer.h"
#include <iostream>

int main(int argc, char **argv)
{
    // give error if more than one file is passed through
    if(argc > 2)
    {
        std::cerr << "Can't handle more than one file at a time.\n";
        exit(1);
    }
    // error if not enough files passed in
    if(argc <= 1)
    {
        std::cerr << "Please enter a filename.\n";
        exit(1);
    }

    Lexer lexer(argv[1]);
    lexer.lex();

    return 0;
}