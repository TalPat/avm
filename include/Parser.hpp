#ifndef PARSER_HPP
#define PARSER_HPP

#include "SToken.hpp"
#include <list>

class parser
{
private:
public:
    //Constructor and destructor
    parser(/* args */);
    ~parser();

    //Copy constructor & assignment overide

    //Class methods
    void checkGrammar(std::list<SToken*> tokenList);

    //Getters and setters
};

#endif