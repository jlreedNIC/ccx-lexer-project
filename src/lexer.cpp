/**
 * @file lexer.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief Lexical analyzer program.
 * 
 */

#include "lexer.h"

Lexer::Lexer()
{

}

Lexer::Lexer(const std::string &fileName)
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
    outFile.open(fileName + ".test.lexer.out", std::ios::out);
    if(!outFile)
    {
        std::cerr << "Could not open output file.\n";
        exit(1);
    }
    else std::cout << "Opened " << fileName << ".test.lexer.out file\n";
}

Lexer::~Lexer()
{
    // close files
    inFile.close();
    outFile.close();

    std::cout << "Closed files.\n";
}

void Lexer::lex()
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
        token = "\n"; // reset token

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

        if(isSingleChar())
        {
            getToken();
            std::cout << lexeme << token;
        }
        // word
        if(isWordPart() || isSingleChar())
        {
            if(!isSingleChar())
            {
                // getWord();
                do
                {
                    getChars();
                    lexeme += currChar;
                    
                } while (isWordPart());
            }

            getToken();
            // std::cout << lexeme << token;
            // token = " (placeholder)\n";            
        }

        // string
        if(currChar == '\"')
        {
            // getString();
            do
            {
                getChars();
                lexeme += currChar;
            } while (currChar != '\"');

            token = " (string)\n";            
        }

        // space
        if(currChar == ' ' || currChar == '\n')
        {
            // ignore space
            lexeme = "";
            token = "";
        }

        // have full lexeme and token is set
        lexeme += token;
        outputLexeme();
    }
}

// gets the next char and peeks at the char after
void Lexer::getChars()
{
    // FIX:why doesn't !inFile work?
    // just use inFile
    if(!inFile.eof())
    {
        inFile.get(currChar);
        nextChar = inFile.peek();
    }
}

// outputs lexeme to outfile
void Lexer::outputLexeme()
{
    outFile << lexeme;
}


// FIX: implement this part better
bool Lexer::isSingleChar()
{
    
    bool cChar = (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z');
    // nChar is not a letter or _ or a number
    bool nChar = !((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z')
                  || nextChar == '_' || (nextChar >= '0' && nextChar <= '9')); // implement isLetter(char)

    return cChar && nChar;
}
// checks to see if currChar and nextChar are part of a word (an alphabet char or numeric char or '_')
// does not work for single chars
// maybe do isLetter and isWordPart
// bool isLetter(char) ? check for single chars?
// bool isSingleChar()
bool Lexer::isLetter()
{
    
    return (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || currChar == '_';
}

// checks with currChar and nextChar to see if the currChar is part of a 'word'
bool Lexer::isWordPart()
{
    bool cLetter = (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || currChar == '_';
    bool nLetter = (nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || 
                    nextChar == '_' || (nextChar >= '0' && nextChar <= '9');
    return cLetter && nLetter;
}

// checks to see if currChar and nextChar are numbers
bool Lexer::isNumber()
{
    bool cNumber = (currChar >= '0' && currChar <= '9');
    bool nNumber = (nextChar >= '0' && nextChar <= '9');
    return cNumber && nNumber;
}

// returns the correct token based on if the lexeme is a keyword
void Lexer::getToken()
{
    if(isKeyword()) 
    {
        token = " (keyword)\n";
    }
    else token = " (identifier)\n";
}

// checks to see if the lexeme is a keyword
bool Lexer::isKeyword()
{
    // find better way to do keywords
    // maybe read into vector from file?
    std::string keywords[] = {"accessor", "and", "array", "begin", "bool", "case", 
                              "character", "constant", "else", "elsif", "end", "exit", 
                              "function", "if", "in", "integer", "interface", "is", 
                              "loop", "module", "mutator", "natural", "null", "of", "or", 
                              "others", "out", "positive", "procedure", "range", "return",
                              "struct", "subtype", "then", "type", "when", "while"};

    bool found = false;
    int i = 0;

    for(i=0; i<37; i++)
    {
        if(lexeme == keywords[i])
        {
            found = true;
            break;
        }
    }
    // while(*keywords != "\0" && !found)
    // {
    //     std::cout << keywords[i] << "\n";
    //     if(lexeme == keywords[i])
    //     {
    //         found = true;
    //     }
    //     else i++;
    // }

    
    return found;

}