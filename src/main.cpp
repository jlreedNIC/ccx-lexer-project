/**
 * @file main.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief Start of Lexical Analyzer program.
 *        Program currently takes a file given through the command line and copies
 *        the contents to a new file, with .lexer.out appended to the file name.
 */

#include "parser.h"

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

    Parser parser(argv[1]);
    parser.parse();

    return 0;
}