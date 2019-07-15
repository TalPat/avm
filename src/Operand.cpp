#include "Operand.hpp"
#include <math.h>

//Constructors and destructors

template <eOperandType T>
Operand<T>::Operand(std::string& value): _type(T)
{
    _value = std::stod(value);
    _operandFactory = new OperandFactory;
}

template <eOperandType T>
Operand<T>::~Operand()
{
}

//Assignment and constructor overload



//Class methods

template <eOperandType T>
int Operand<T>::getPrecision(void) const {
    return (_type);
}

template <eOperandType T>
eOperandType Operand<T>::getType(void) const {
    return (_type);
}

template <eOperandType T>
std::string const& Operand<T>::toString(void) const {
    return(std::to_string(_value));
}

//Binary operator overloads

template <eOperandType T>
IOperand const* Operand<T>::operator+( IOperand const& rhs ) const{
    Operand* Op;
    double value = 0;
    if (_type > rhs.getPrecision()){
        Op = new Operand<T>(toString());
    } else {
        Op = _operandFactory->createOperand(rhs.getType(), toString());
    }
    value += std::stod(rhs.toString());
    if (Op->getPrecision() < 3) {
        value = round(value);
    }
    return (Op);
}

template <eOperandType T>
IOperand const* Operand<T>::operator-( IOperand const& rhs ) const{
    Operand* Op;
    double value = 0;
    if (_type > rhs.getPrecision()){
        Op = new Operand<T>(toString());
    } else {
        Op = _operandFactory->createOperand(rhs.getType(), toString());
    }
    value -= std::stod(rhs.toString());
    if (Op->getPrecision() < 3) {
        value = round(value);
    }
    return (Op);
}

template <eOperandType T>
IOperand const* Operand<T>::operator*( IOperand const& rhs ) const{
    Operand* Op;
    double value = 0;
    if (_type > rhs.getPrecision()){
        Op = new Operand<T>(toString());
    } else {
        Op = _operandFactory->createOperand(rhs.getType(), toString());
    }
    value *= std::stod(rhs.toString());
    if (Op->getPrecision() < 3) {
        value = round(value);
    }
    return (Op);
}

template <eOperandType T>
IOperand const* Operand<T>::operator/( IOperand const& rhs ) const{
    Operand* Op;
    double value = 0;
    if (_type > rhs.getPrecision()){
        Op = new Operand<T>(toString());
    } else {
        Op = _operandFactory->createOperand(rhs.getType(), toString());
    }
    value /= std::stod(rhs.toString());
    if (Op->getPrecision() < 3) {
        value = round(value);
    }
    return (Op);
}

template <eOperandType T>
IOperand const* Operand<T>::operator%( IOperand const& rhs ) const{
    Operand* Op;
    double value = 0;
    if (_type > rhs.getPrecision()){
        Op = new Operand<T>(toString());
    } else {
        Op = _operandFactory->createOperand(rhs.getType(), toString());
    }
    value = _value % std::stod(rhs.toString());
    if (Op->getPrecision() < 3) {
        value = round(value);
    }
    return (Op);
}

//Getters and setters

template <eOperandType T>
void Operand<T>::setValue(double value) { //set overflow check here
    _value = value;
}

template <eOperandType T>
double Operand<T>::getValue(void) const {
    return (this->_value);
}