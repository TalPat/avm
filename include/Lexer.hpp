#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "SToken.hpp"
#include <exception>

class Lexer
{
private:
    std::list<SToken*> _tokenList;
    std::string _source;
public:
    //Constructor and destructor
    Lexer();
    ~Lexer();

    //Copy constructor & assignment overide
    Lexer(Lexer &obj);
    Lexer& operator=(const Lexer &obj);

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

    //exceptions
    class BadFileException : public std::exception {
        public:
            virtual const char* what() const throw();
    };

    class LexingException : public std::exception {
        private:
            int _line;
            std::string _message;
        public:
            LexingException(int line, std::string message);
            virtual const char* what() const throw();
    };

};

#endif
