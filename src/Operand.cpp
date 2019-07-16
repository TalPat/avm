#ifndef OPERAND_CPP
#define OPERAND_CPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <math.h>
#include <iostream>

template<eOperandType T>
class Operand: public IOperand
{
private:
  eOperandType _type;
  double _value;
  std::string _strVal;
public:
  //constructor and destructor
  Operand(std::string& value): _type(T)
  {
      _value = std::stod(value);
      _strVal = value;
  }
  ~Operand() {}

  //Copy constructor and assignment override

  //Method functions
  int getPrecision(void) const // Precision of the type of the instance
  {
    return (_type);
  }
  eOperandType getType(void) const // Type of the instance
  {
    return (_type);
  }
  
  IOperand const* operator+( IOperand const& rhs ) const // Sum
  {
    const IOperand* Op;
    double value = 0;
    OperandFactory operandFactory;
    std::string strVal;

    value = _value + std::stod(rhs.toString());

    if (_type > rhs.getPrecision()){
      if (getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(T, strVal);
    } else {
      if (rhs.getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(rhs.getType(), strVal);
    }

    return (Op);
  }
  IOperand const* operator-( IOperand const& rhs ) const // Difference
  {
    const IOperand* Op;
    double value = 0;
    OperandFactory operandFactory;
    std::string strVal;

    value = _value - std::stod(rhs.toString());

    if (_type > rhs.getPrecision()){
      if (getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(T, strVal);
    } else {
      if (rhs.getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(rhs.getType(), strVal);
    }

    return (Op);
  }
  IOperand const* operator*( IOperand const& rhs ) const // Product
  {
    const IOperand* Op;
    double value = 0;
    OperandFactory operandFactory;
    std::string strVal;

    value = _value * std::stod(rhs.toString());

    if (_type > rhs.getPrecision()){
      if (getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(T, strVal);
    } else {
      if (rhs.getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(rhs.getType(), strVal);
    }

    return (Op);
  }
  IOperand const* operator/( IOperand const& rhs ) const // Quotient
  {
    const IOperand* Op;
    double value = 0;
    OperandFactory operandFactory;
    std::string strVal;

    value = _value / std::stod(rhs.toString());

    if (_type > rhs.getPrecision()){
      if (getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(T, strVal);
    } else {
      if (rhs.getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(rhs.getType(), strVal);
    }

    return (Op);
  }
  IOperand const* operator%( IOperand const& rhs ) const // Modulo
  {
    const IOperand* Op;
    double value = 0;
    OperandFactory operandFactory;
    std::string strVal;

    value = static_cast<int>(round(_value)) % static_cast<int>(round(std::stod(rhs.toString())));

    if (_type > rhs.getPrecision()){
      if (getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(T, strVal);
    } else {
      if (rhs.getPrecision() < 3) {
        value = round(value);
      }
      strVal = std::to_string(value);
      Op = operandFactory.createOperand(rhs.getType(), strVal);
    }

    return (Op);
  }

  std::string const& toString(void) const // String representation of the instance
  {
    /* */std::cout << _strVal << std::endl;
    return(_strVal);
  }

  void setValue(double value)
  { //set overflow check here
    _value = value;
  }
  double getValue(void) const
  {
    return (this->_value);
  }

  //Getters and setters
};

#endif
