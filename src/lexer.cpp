/**
 * @file lexer.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 10-01-21
 * @class CS 210
 * @brief Implementation file for Lexer class and lexical analyzer program.
 * 
 */

#include "lexer.h"

/**
 * @brief Construct a new Lexer object.
 *        Default constructor
 * 
 */
Lexer::Lexer()
{

}

/**
 * @brief Construct a new Lexer object. Initializes the 
 *        in and out file streams
 * 
 * @param fileName string of pathname of file to open
 */
Lexer::Lexer(const std::string &fileName)
{
    // open input file
    inFile.open(fileName);
    if(!inFile)
    {
        std::cerr << "Error opening file.\n";
        exit(1);
    }

    // open output file
    outFile.open(fileName + ".test.lexer.out", std::ios::out);
    if(!outFile)
    {
        std::cerr << "Could not open output file.\n";
        exit(1);
    }
}

/**
 * @brief Destroy the Lexer object. Closes files.
 * 
 */
Lexer::~Lexer()
{
    // close files
    inFile.close();
    outFile.close();
}

/**
 * @brief Loops through input file, decides what to do with the 
 *        current char, and then outputs the lexeme and token to
 *        the output file.
 * 
 */
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

/**
 * @brief Gets the next character from the input file
 *        and peeks at the character after
 * 
 */
void Lexer::getChars()
{
    if(inFile)
    {
        inFile.get(currChar);
        nextChar = inFile.peek();
    }
}

/**
 * @brief Outputs the lexeme to the output file
 * 
 */
void Lexer::outputLexeme()
{
    outFile << lexeme;
}

/**
 * @brief Checks to see if the current character is the start of a comment
 * 
 * @return true If current char and next char are part of a comment
 * @return false If chars are not part of a comment
 */
bool Lexer::isCommentStart()
{
    return currChar == '/' && nextChar == '*';
}

/**
 * @brief Loops through file until end of comment is found.
 *        Then outputs the updated lexeme and token to the
 *        output file.
 * 
 */
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
/**
 * @brief Checks to see if current character is a letter and the next character
 *        is not an alphanumeric character
 * 
 * @return true if currChar is a letter and nextChar is not
 * @return false if currChar is a letter
 */
bool Lexer::isSingleChar()
{
    
    bool cChar = isLetter();

    // nChar is not a letter or _ or a number
    bool nChar = !((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z')
                  || nextChar == '_' || (nextChar >= '0' && nextChar <= '9')); // implement isLetter(char)

    return cChar && nChar;
}

/**
 * @brief Checks to see if the current character is a letter
 * 
 * @return true if currChar is letter, capitalized or not
 * @return false if currChar is not a letter
 */
bool Lexer::isLetter()
{
    return (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z');// || currChar == '_';
}

/**
 * @brief Checks to see if the current character is part of a 'word', ie
 *        part of a string
 * 
 * @return true if currChar is a letter and nextChar is alphanumeric or _
 * @return false if currchar is not part of a 'word'
 */
bool Lexer::isWordPart()
{
    bool cLetter = (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || currChar == '_';
    bool nLetter = (nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || 
                    nextChar == '_' || (nextChar >= '0' && nextChar <= '9');
    return cLetter && nLetter;
}

/**
 * @brief Gets the entire 'word' and updates lexeme. Calls to update token
 * 
 */
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

/**
 * @brief Checks the lexeme to see if it is a keyword
 * 
 * @return true if lexeme is a keyword
 * @return false if lexeme is not a keyword
 */
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
/**
 * @brief Updates the token string on whether or not the lexeme
 *        is a keyword. If it's not a keyword, token is an identifier.
 * 
 */
void Lexer::getToken()
{
    if(isKeyword()) 
    {
        token = " (keyword)\n";
    }
    else token = " (identifier)\n";
}

/**
 * @brief Checks to see if the current character is part of a string
 *        literal, ie if it starts with "
 * 
 * @return true if currChar is "
 * @return false if currChar is not "
 */
bool Lexer::isStringStart()
{
    return currChar == '\"';
}

/**
 * @brief Grabs the string literal (until currChar is matching ")
 *        and updates both the lexeme and token
 * 
 */
void Lexer::getString()
{
    do
    {
        getChars();
        lexeme += currChar;
    } while (currChar != '\"');

    token = " (string)\n";  
}

/**
 * @brief Checks to see if current character is the start
 *        of a character literal, ie if it starts with '
 * 
 * @return true if currChar is '
 * @return false if currChar is not '
 */
bool Lexer::isCharLitStart()
{
    return currChar == '\'';
}

/**
 * @brief Grabs the entire character literal (until matching ')
 *        and updates both lexeme and token
 * 
 */
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
/**
 * @brief Checks to see if current character is the start of a number
 * 
 * @return true if currChar is a number
 * @return false if currChar is not a number
 */
bool Lexer::isNumStart()
{
    bool cNumber = (currChar >= '0' && currChar <= '9');
    // bool nNumber = (nextChar >= '0' && nextChar <= '9');
    return cNumber;
}

/**
 * @brief Checks to see if current character is part of a number
 * 
 * @return true if currChar is a number and nextChar is a number
 * @return false if currChar or nextChar are not numbers
 */
bool Lexer::isNumPart()
{
    bool cNum = isNumStart() || currChar == '#';// || (currChar >= 'A' && currChar <= 'F') || currChar == '.' || currChar == '#';
    bool nNum = (nextChar >= '0' && nextChar <= '9') || (nextChar >= 'A' && nextChar <= 'F') || nextChar == '.' || nextChar == '#';

    return cNum && nNum;
}

// FIX: does not handle 99..99 case
/**
 * @brief grabs the entire number literal and updates both lexeme and token
 * 
 */
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

/**
 * @brief Checks to see if current character is the start of an operator
 * 
 * @return true if currChar matches an operator symbol
 * @return false if currChar does not match an operator symbol
 */
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

/**
 * @brief Updates lexeme to hold the entire operator. Updates token to operator.
 * 
 */
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
