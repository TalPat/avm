#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "eOperandType.hpp"
#include "IOperand.hpp"

class OperandFactory
{
private:
  IOperand const* (*_createArr[5])(std::string& value);
public:
  OperandFactory();
  ~OperandFactory();

  IOperand const* createOperand(eOperandType type, std::string& value) const;

  IOperand const* createInt8(std::string& value) const;
  IOperand const* createInt16(std::string& value) const;
  IOperand const* createInt32(std::string& value) const;
  IOperand const* createFloat(std::string& value) const;
  IOperand const* createDouble(std::string& value) const;
};

#endif
