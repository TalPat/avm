#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "SToken.hpp"

class Lexer
{
private:
    std::list<SToken*> _tokenList;
    std::string _source;
public:
    //Constructor and destructor
    Lexer(/* args */);
    ~Lexer();

    //Copy constructor & assignment overide

    //Class methods
    void fetchFromFile(std::string avmFile);
    void fetchFromIn(void);
    bool isInt(std::string str);
    bool isFloat(std::string str);
    void removeComments(void);
    std::string determineName(std::string token);
    void tokenize(void);

    //Getters and setters
    std::list<SToken*> getTokenList();
};

#endif
