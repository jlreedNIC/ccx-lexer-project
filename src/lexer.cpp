/**
 * @file lexer.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief Lexical analyzer program.
 *          For assign5
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
    // else std::cout << "Opened " << fileName << " file\n";

    // open output file
    outFile.open(fileName + ".test.lexer.out", std::ios::out);
    if(!outFile)
    {
        std::cerr << "Could not open output file.\n";
        exit(1);
    }
    // else std::cout << "Opened " << fileName << ".test.lexer.out file\n";
}

Lexer::~Lexer()
{
    // close files
    inFile.close();
    outFile.close();

    // std::cout << "Closed files.\n";
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
        if(isCommentStart())
        {
            getComment();
        }

        // word
        else if(isLetter())
        {
            getWord();    
        }

        // string
        else if(isStringStart())
        {
            getString();                      
        }

        // character literal
        else if(isCharLitStart())
        {
            getCharLit();
        }

        // operator
        else if(isOpStart())
        {
            getOperator();
        }

        // numeric literal
        else if(isNumStart())
        {
            getNumLit();
        }
        // space
        else if(currChar == ' ' || currChar == '\n')
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
    if(inFile)
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

// checks for /*
bool Lexer::isCommentStart()
{
    return currChar == '/' && nextChar == '*';
}

// puts whole comment into lexeme
void Lexer::getComment()
{
    do
    {
        getChars();
        lexeme += currChar;
    } while (currChar != '*' || nextChar != '/');
    getChars();
    lexeme += currChar;

    token = " (comment)\n";
}

// FIX: implement this part better
// checks to see if currChar is a letter and nextChar is not an alphanumeric character
bool Lexer::isSingleChar()
{
    
    bool cChar = isLetter();

    // nChar is not a letter or _ or a number
    bool nChar = !((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z')
                  || nextChar == '_' || (nextChar >= '0' && nextChar <= '9')); // implement isLetter(char)

    return cChar && nChar;
}

// checks to see if currChar is a letter
bool Lexer::isLetter()
{
    return (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z');// || currChar == '_';
}

// checks with currChar and nextChar to see if the currChar is part of a 'word'
bool Lexer::isWordPart()
{
    bool cLetter = (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || currChar == '_';
    bool nLetter = (nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || 
                    nextChar == '_' || (nextChar >= '0' && nextChar <= '9');
    return cLetter && nLetter;
}

// puts whole word into lexeme
void Lexer::getWord()
{
    if(!isSingleChar())
    {
        do
        {
            getChars();
            lexeme += currChar;
                    
        } while (isWordPart());
    }

    getToken();
}

// checks to see if the lexeme is a keyword
bool Lexer::isKeyword()
{
    // FIX: find better way to do keywords
    // maybe read into vector from file?
    // or just use a vector
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

    return found;
}

// returns the correct token based on if the lexeme is a keyword
// think about implementing this to return correct token for every lexeme, 
// not just keywords and identifiers
void Lexer::getToken()
{
    if(isKeyword()) 
    {
        token = " (keyword)\n";
    }
    else token = " (identifier)\n";
}

// checks for ""
bool Lexer::isStringStart()
{
    return currChar == '\"';
}

// puts whole string into lexeme
void Lexer::getString()
{
    do
    {
        getChars();
        lexeme += currChar;
    } while (currChar != '\"');

    token = " (string)\n";  
}

// checks for '
bool Lexer::isCharLitStart()
{
    return currChar == '\'';
}

// puts whole char literal into lexeme
void Lexer::getCharLit()
{
    do
    {
        getChars();
        lexeme += currChar;
    } while (currChar != '\'');
    
    token = " (character literal)\n";
}

// checks to see if currChar and nextChar are numbers
bool Lexer::isNumStart()
{
    bool cNumber = (currChar >= '0' && currChar <= '9');
    // bool nNumber = (nextChar >= '0' && nextChar <= '9');
    return cNumber;
}

bool Lexer::isNumPart()
{
    bool cNum = isNumStart() || currChar == '#';// || (currChar >= 'A' && currChar <= 'F') || currChar == '.' || currChar == '#';
    bool nNum = (nextChar >= '0' && nextChar <= '9') || (nextChar >= 'A' && nextChar <= 'F') || nextChar == '.' || nextChar == '#';

    return cNum && nNum;
}

// FIX: does not handle 99..99 case
void Lexer::getNumLit()
{
    // peek at char after nextChar to make sure not ".." operator
    char nextNextChar;
    if(inFile)
    {
        inFile.get(currChar);
        nextNextChar = inFile.peek();
        inFile.putback(currChar);
    }

    bool notOperator = nextChar != '.' && nextNextChar != '.';

    if(notOperator)
    {
        while(isNumPart())
        {
            getChars();
            lexeme += currChar;
        }        
    }
    
    token = " (numeric literal)\n";
}

// checks to see if currChar is the start of an operator
bool Lexer::isOpStart()
{
    char ops[] = {'.', '<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':',
                  '[', ']', '=', '!'};
    bool found = false;

    for(int i=0; i<18; i++)
    {
        if(currChar == ops[i])
        {
            found = true;
            break;
        }
    }

    return found;
}

// checks nextChar to see if it's an operator. if it is, then it adds it to the lexeme
// sets token to operator
void Lexer::getOperator()
{
    // check next char
    // if next char is op
        // get next char
    // set lexeme and token
    if(nextChar == '=' || nextChar == '.' || nextChar == '<' || nextChar == '>' || nextChar == '*')
    {
        getChars();
        lexeme += currChar;
    }

    token = " (operator)\n";
}
