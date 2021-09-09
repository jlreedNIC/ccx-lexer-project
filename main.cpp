#include <iostream>
#include <fstream>
#include <string>

int main()
{
    //test file to open
    std::string fileName = "testfile.cpp";

    // open file
    std::fstream inFile;
    inFile.open(fileName, std::ios::in);

    // check if file opened
    if(!inFile)
    {
        std::cerr << "Error opening file\n";
        exit(1);
    }
    
    // change the file name
    fileName += ".lexer.out";

    //create new output file
    std::fstream outFile;
    outFile.open(fileName, std::ios::out);

    std::string dummyString = "";

    while(!inFile.eof())
    {
        // read from input file
        getline(inFile, dummyString);

        // output to new file
        outFile << dummyString << "\n";
    }

    inFile.close();
    outFile.close();

    return 0;
}