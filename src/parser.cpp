#include "parser.h"

Parser::Parser()
{

}

Parser::Parser(const std::string &fileName)
{
    // open input file
    inFile.open(fileName);
    if(!inFile)
    {
        std::cerr << "Error opening file.\n";
        exit(1);
    }

    else std::cout << "Opened " << fileName << " file\n";

    // open output file
    outFile.open(fileName + ".lexer.out", std::ios::out);

    std::cout << "Opened " << fileName << ".lexer.out file\n";
}

Parser::~Parser()
{
    // close files
    inFile.close();
    outFile.close();

    std::cout << "Closed files.\n";
}

void Parser::parse()
{
    // get char
    // add to lexeme
    // check for what token it fits
        // go to that function
    // loop


    while(!inFile.eof())
    {
        getChars();

        lexeme = currChar;

        // comment
        if(currChar == '/' && nextChar == '*')
        {
            // getComment();
            do
            {
                getChars();
                lexeme += currChar;
            } while (currChar != '*' || nextChar != '/');
            getChars();
            lexeme += currChar;

            token = " (comment)\n";
        }

        // word
        if(isLetter())
        {
            // get word
            do
            {
                getChars();
                lexeme += currChar;
            } while (isLetter());
            // getChars();
            // lexeme += currChar;

            // getToken();
            token = " (placeholder)\n";            
        }

        // space
        if(currChar == ' ' || currChar == '\n')
        {
            // ignore space
            // lexeme - currChar

            lexeme = "";
            token = "";
        }

        // have full lexeme and token is set
        lexeme += token;
        outputLexeme();
    }
}

// void Parser::parse()
// {
//     // currChar = ' ';
//     // read entire file
//     while(!inFile.eof())
//     {
//         getChars();
//         token = "";
//
//         lexeme = currChar;
//
//         // comment
//         if(currChar == '/' && nextChar == '*')
//         {
//             token = " (comment)";
//
//             do
//             {
//                 getChars();
//                 lexeme += currChar;
//             } while (currChar != '*' || nextChar != '/');
//             getChars();
//             lexeme += currChar;            
//         }
//
//         // string
//
//         // word
//         if(isLetter())
//         {
//             getChars();
//             while(isLetter())
//             {
//                 // getChars();
//                 lexeme += currChar;
//                 getChars();
//             }
//             lexeme += currChar;
//
//             // findToken();
//         }
//
//         lexeme += token;
//         outputLexeme();
//
//         // ignore spaces
//         // if(currChar != ' ' || currChar != '\n')
//         // {
//         //     lexeme = "";
//         //     token = "";
//         // }
//     }
//
// }

void Parser::getChars()
{
    // FIX:why doesn't !inFile work?
    if(!inFile.eof())
    {
        inFile.get(currChar);
        nextChar = inFile.peek();
        // inFile.get(nextChar);

        // std::cout << currChar;// << nextChar;
    }
}

void Parser::outputLexeme()
{
    outFile << lexeme;
}

//checks to see if currChar and nextChar is a letter
// FIX: function needs work. Does not handle strings correctly
bool Parser::isLetter()
{
    bool nLetter = (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || currChar == '_';
    bool sLetter = (nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || nextChar == '_';
    return nLetter && sLetter;
}