#include "Parser.hpp"

//Constructor and destructor
Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}


//Copy constructor & assignment overide

//Class methods
void Parser::checkGrammar(std::list<SToken*> tokenList) {
  int line = 1;
  SToken currentToken;
  std::list<SToken*>::iterator it = tokenList.begin();

  if ((*it)->name != "Instruction" && (*it)->value != "\n") {
    if ((*it)->value == "\n") line++;
    throw InvalidInstructionExcepion(line, "'" + (*it)->value + "' is an invalid instruction, valid instruction expected");
  }
  currentToken = *(*it);
  it++;

  for (;it != tokenList.end(); it++) {
    if (currentToken.value == "\n") {
      line++;
      if ((*it)->name != "Instruction" && (*it)->value != "\n") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' is an invalid instruction, valid instruction expected");
    } else if (currentToken.name == "Instruction") {
      if (currentToken.value == "push" || currentToken.value == "assert"){
        if ((*it)->name != "Type") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' found, valid type expected");
      } else {
        if ((*it)->value != "\n") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' found, eol expected");
      }
    } else if (currentToken.name == "Type" && (*it)->value == "(") {
      it++;
      if (currentToken.value == "float" || currentToken.value == "double") {
        if ((*it)->name != "fValue") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' found, float/double expected");
      } else {
        if ((*it)->name != "iValue") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' found, int expected");
      }
      it++;
      if ((*it)->value != ")") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' found, ')' expected");
    } else if (currentToken.value == ")") {
      if ((*it)->value != "\n") throw InvalidInstructionExcepion(line, "'" + ((*it)->value=="\n"?"eol":(*it)->value) + "' found, eol expected");
    }
    currentToken = *(*it);
  }
}

//Getters and setters

//Exceptions
Parser::InvalidInstructionExcepion::InvalidInstructionExcepion(int line, std::string message) {
    Parser::InvalidInstructionExcepion::_line = line;
    Parser::InvalidInstructionExcepion::_message = message;
}

const char* Parser::InvalidInstructionExcepion::what() const throw() {
    std::string line = std::to_string(Parser::InvalidInstructionExcepion::_line);
    std::string message = "line: " + line + ": " + Parser::InvalidInstructionExcepion::_message;
    return(message.c_str());
}