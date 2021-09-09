#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    // give error if more than one file is passed through
    if(argc > 2)
    {
        std::cerr << "Can't handle more than one file at a time.\n";
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
    while(!inFile.eof())
    {
        // TO DO: find better way for reading from file. 
        // read from input file
        getline(inFile, dummyString);

        // output to new file
        outFile << dummyString << "\n";
    }

    // close files
    inFile.close();
    outFile.close();

    return 0;
}