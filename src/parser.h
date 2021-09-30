#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <string>


class Parser
{
    public:
        Parser();                               // default constructor
        Parser(const std::string &fileName);    // constructor with file name
        ~Parser();                              // default destructor



    private:
        std::string token;
        char nextChar;
};


#endif