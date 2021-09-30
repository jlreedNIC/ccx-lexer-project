/**
 * @file main.cpp
 * @author Jordan Reed
 * @brief Start of Lexical Analyzer program.
 *        Program currently takes a file given through the command line and copies
 *        the contents to a new file, with .lexer.out appended to the file name.
 * 
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
    if(argc < 1)
    {
        std::cerr << "Please enter a filename.\n";
        exit(1);
    }

    // file to open, taken from command line
    std::string fileName = argv[1];

    // open file
    std::fstream inFile;
    inFile.open(fileName, std::ios::in);

    // check if file opened
    if(!inFile)
    {
        std::cerr << "Error opening file\n";
        exit(1);
    }
    
    // change the file name for correct output file
    fileName += ".lexer.out";

    //create new output file
    std::fstream outFile;
    outFile.open(fileName, std::ios::out);

    // loop through input file and put into output file
    std::string dummyString = "";
    std::string placeHolder = "";
    int size = 0;
    while(!inFile.eof())
    {
        // TO DO: find better way for reading from file. 
        // read from input file
        inFile >> dummyString;

        // check for comments
        if(dummyString[0] == '/' && dummyString[1] == '*')
        {
            // ignore next /n
            inFile.ignore();
            // comment found
            do
            {
                // store comment in place holder until end of comment is found
                placeHolder += dummyString + '\n';
                // get next line of comment
                getline(inFile, dummyString);
                // check to see if end of comment is found
                size = dummyString.length();
            } while (dummyString[size-1] != '/' && dummyString[size-2] != '*');

            // reset placeHolder and output dummyString
            placeHolder += dummyString;
            dummyString = placeHolder;
            placeHolder = "";
            // output comment to file
            outFile << dummyString << " (comment)\n";
        }
        else
        {
            // output to new file
            outFile << dummyString << "\n"; 
        }  
    }

    // close files
    inFile.close();
    outFile.close();

    return 0;
}