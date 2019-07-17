#include "IOperand.hpp"

IOperand::OverflowException::OverflowException(std::string type) {
  IOperand::OverflowException::_type = type;
}
const char* IOperand::OverflowException::what() const throw() {
  std::string message = IOperand::OverflowException::_type + " overflow";
  const char* mystr = message.c_str();

  char *b = new char[message.length() + 1]{};
  std::copy(mystr, mystr + message.length(), b); //Ubuntu doesnt like strings passing through what
  
  return (b);
};

IOperand::UnderflowException::UnderflowException(std::string type) {
  IOperand::UnderflowException::_type = type;
}
const char* IOperand::UnderflowException::what() const throw() {
  std::string message = IOperand::UnderflowException::_type + " underflow";
  const char* mystr = message.c_str();

  char *b = new char[message.length() + 1]{};
  std::copy(mystr, mystr + message.length(), b); //Ubuntu doesnt like strings passing through what
  
  return (b);
};
