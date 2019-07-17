#include "OperandFactory.hpp"
#include "Operand.cpp"

OperandFactory::OperandFactory()
{
}

OperandFactory::~OperandFactory()
{
}

IOperand const* OperandFactory::createOperand(eOperandType type, std::string& value) const{
  typedef IOperand const* (OperandFactory::*fnCreate)(std::string& value) const;
  fnCreate _createArr[5] = {&OperandFactory::createInt8, &OperandFactory::createInt16, &OperandFactory::createInt32, &OperandFactory::createFloat, &OperandFactory::createDouble};
  return ((this->*(_createArr[type]))(value));
}

IOperand const* OperandFactory::createInt8(std::string& value) const{
  return (new Operand<Int8, int>(value));
}

IOperand const* OperandFactory::createInt16(std::string& value) const{
  return (new Operand<Int16, int>(value));
}

IOperand const* OperandFactory::createInt32(std::string& value) const{
  return (new Operand<Int32, int>(value));
}

IOperand const* OperandFactory::createFloat(std::string& value) const{
  return (new Operand<Float, float>(value));
}

IOperand const* OperandFactory::createDouble(std::string& value) const{
  return (new Operand<Double, double>(value));
}
