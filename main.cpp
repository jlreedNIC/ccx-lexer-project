#include <iostream>
#include <fstream>
#include <string>

int main()
{
    //test file to open
    std::string testName = "testfile";

    // open file
    std::ifstream inFile(testName, std::ifstream::in);
    // check if file didn't open
    if(!inFile.is_open())
    {
        std::cout << "Error opening file.\n";
        return 0;
    }

    // change the file name
    testName += ".lexer.out";

    //create output file
    std::ofstream outFile(testName, std::ofstream::out);

    std::cout << "test\n";

    return 0;
}