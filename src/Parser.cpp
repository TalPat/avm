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
  SToken currentToken;
  std::list<SToken*>::iterator it = tokenList.begin();

  if ((*it)->name != "Instruction" || (*it)->value != "\n") {
    //throw error;
  }
  currentToken = *(*it);
  it++;

  for (;it != tokenList.end(); it++) {
    if (currentToken.value == "\n") {
      if ((*it)->name != "Instruction" && (*it)->value != "\n") /*throw error*/std::cout << "Error: current token val:("+currentToken.value+")--it value:("+(*it)->value << ")--it name:(" +(*it)->name << std::endl;
    } else if (currentToken.name == "Instruction") {
      if (currentToken.value == "push" || currentToken.value == "assert"){
        if ((*it)->name != "Type") /*throw error*/std::cout << "Error "+currentToken.value+"--"+(*it)->value << std::endl;
      } else {
        if ((*it)->value != "\n") /*throw error*/std::cout << "Error "+currentToken.value+"--"+(*it)->value << std::endl;
      }
    } else if (currentToken.name == "Type" && (*it)->value == "(") {
      it++;
      if (currentToken.value == "float" || currentToken.value == "double") {
        if ((*it)->name != "fValue") /*throw error*/std::cout << "Error: current token val:("+currentToken.value+")--it value:("+(*it)->value << ")--it name:(" +(*it)->name << std::endl;
      } else {
        if ((*it)->name != "iValue") /*throw error*/std::cout << "Error: current token val:("+currentToken.value+")--it value:("+(*it)->value << ")--it name:(" +(*it)->name << std::endl;
      }
      it++;
      if ((*it)->value != ")") /*throw error*/std::cout << "Error "+currentToken.value+"--"+(*it)->value << std::endl;
    } else if (currentToken.value == ")") {
      if ((*it)->value != "\n") /*throw error*/std::cout << "Error "+currentToken.value+"--"+(*it)->value << std::endl;
    }
    currentToken = *(*it);
  }
  /* */std::cout << "Grammar correct" << std::endl;
}

//Getters and setters
