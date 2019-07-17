#ifndef PARSER_HPP
#define PARSER_HPP

#include "SToken.hpp"
#include <list>
#include <iostream>

class Parser
{
private:
public:
    //Constructor and destructor
    Parser(/* args */);
    ~Parser();

    //Copy constructor & assignment overide

    //Class methods
    void checkGrammar(std::list<SToken*> tokenList);

    //Getters and setters

    //Exceptions
    class InvalidInstructionExcepion : public std::exception {
        private:
            int _line;
            std::string _message;
        public:
            InvalidInstructionExcepion(int line, std::string message);
            virtual const char* what() const throw();
    };
};

#endif