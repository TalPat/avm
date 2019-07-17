#ifndef OPERAND_CPP
#define OPERAND_CPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <math.h>
#include <iostream>
#include <sstream>
#include <limits>

template<eOperandType T, class U>
class Operand: public IOperand
{
private:
  eOperandType _type;
  double _value;
  U _typeValue;
  std::string _strVal;
public:
  //constructor and destructor
  Operand(std::string& value): _type(T)
  {
      _value = std::stod(value);
      switch (T)
      {
      case 0:
        if (_value > std::numeric_limits<int8_t>::max())
          throw OverflowException("int8");
        if (_value < std::numeric_limits<int8_t>::min())
          throw UnderflowException("int8");
        break;
      case 1:
        if (_value > std::numeric_limits<int16_t>::max())
          throw OverflowException("int16");
        if (_value < std::numeric_limits<int16_t>::min())
          throw UnderflowException("int16");
        break;
      case 2:
        if (_value > std::numeric_limits<int32_t>::max())
          throw OverflowException("int32");
        if (_value < std::numeric_limits<int32_t>::min())
          throw UnderflowException("int32");
        break;
      case 3:
        if (_value > std::numeric_limits<float_t>::max())
          throw OverflowException("float");
        if (_value < std::numeric_limits<float_t>::min())
          throw UnderflowException("float");
        break;
      case 4:
        if (_value > std::numeric_limits<double_t>::max())
          throw OverflowException("double");
        if (_value < std::numeric_limits<double_t>::min())
          throw UnderflowException("double");
        break;
      
      default:
        break;
      }
      _typeValue = _value;
      std::stringstream ss;
      ss << _typeValue;
      _strVal = ss.str();
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

    std::stringstream ss;
    ss << value;
    strVal = ss.str();

    if (_type > rhs.getPrecision()){
      Op = operandFactory.createOperand(T, strVal);
    } else {
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

    std::stringstream ss;
    ss << value;
    strVal = ss.str();

    if (_type > rhs.getPrecision()){
      Op = operandFactory.createOperand(T, strVal);
    } else {
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

    std::stringstream ss;
    ss << value;
    strVal = ss.str();

    if (_type > rhs.getPrecision()){
      Op = operandFactory.createOperand(T, strVal);
    } else {
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
    std::stringstream ss;
    ss << value;
    strVal = ss.str();

    if (_type > rhs.getPrecision()){
      Op = operandFactory.createOperand(T, strVal);
    } else {
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

    std::stringstream ss;
    ss << value;
    strVal = ss.str();

    if (_type > rhs.getPrecision()){
      Op = operandFactory.createOperand(T, strVal);
    } else {
      Op = operandFactory.createOperand(rhs.getType(), strVal);
    }

    return (Op);
  }

  std::string const& toString(void) const // String representation of the instance
  {
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
