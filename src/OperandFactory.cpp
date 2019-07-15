#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory():
  _createArr({&this->createInt8, &this->createInt16, &this->createInt32, &this->createFloat, &this->createDouble})
{
}

OperandFactory::~OperandFactory()
{
}

IOperand const* OperandFactory::createOperand(eOperandType type, std::string& value) const{
  return (this->_createArr[type](value));
}

IOperand const* OperandFactory::createInt8(std::string& value) const{
  return (new Operand<Int8>(value));
}

IOperand const* OperandFactory::createInt16(std::string& value) const{
  return (new Operand<Int16>(value));
}

IOperand const* OperandFactory::createInt32(std::string& value) const{
  return (new Operand<Int32>(value));
}

IOperand const* OperandFactory::createFloat(std::string& value) const{
  return (new Operand<Float>(value));
}

IOperand const* OperandFactory::createDouble(std::string& value) const{
  return (new Operand<Double>(value));
}
