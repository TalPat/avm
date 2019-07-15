#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"

template<eOperandType T>
class Operand: public IOperand
{
private:
  eOperandType _type;
  OperandFactory* _operandFactory;
  double _value;
public:
  //constructor and destructor
  Operand(std::string& value);
  ~Operand();

  //Copy constructor and assignment override

  //Method functions
  int getPrecision(void) const; // Precision of the type of the instance
  eOperandType getType(void) const; // Type of the instance
  
  IOperand const* operator+( IOperand const& rhs ) const; // Sum
  IOperand const* operator-( IOperand const& rhs ) const; // Difference
  IOperand const* operator*( IOperand const& rhs ) const; // Product
  IOperand const* operator/( IOperand const& rhs ) const; // Quotient
  IOperand const* operator%( IOperand const& rhs ) const; // Modulo

  std::string const& toString(void) const; // String representation of the instance

  void setValue(double value);
  double getValue(void) const;

  //Getters and setters
};

#endif
