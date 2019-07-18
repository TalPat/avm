#include "Vm.hpp"
#include <iostream>
#include <iomanip> 

//Constructor & destructor

Vm::Vm(/* args */)
{
}

Vm::~Vm()
{
}

//Copy constructor and assignment override
Vm::Vm(Vm &obj) {
    *this = obj;
}

Vm& Vm::operator=(const Vm &obj) {
    if (this != &obj) {
        this->_stack = obj._stack;
        this->_factory = obj._factory;
    }
    return (*this);
}

//Class methods

void Vm::vmPush(std::string value, eOperandType valType) {
    _stack.push_back(_factory.createOperand(valType, value));
}

void Vm::vmPop(void) {
    if (_stack.size() < 1) {
        throw EmptyStackException();
    }
    _stack.pop_back();
}

void Vm::vmDump(void) const {
    std::list<IOperand const*> rlist;

    for (IOperand const* i: _stack) {
        rlist.push_front(i);
    }
    for (IOperand const* j: rlist) {
        if (j->getPrecision() < 3) {
            std::cout << j->toString() << std::endl;
        } else {
            std::cout << j->toString() << std::endl;
        }
    }
}

void Vm::vmAssert(std::string value, eOperandType valType) const{
    if (_stack.size() < 1) {
        throw EmptyStackException();
    }
    if (_stack.back()->toString().compare(value) || valType != _stack.back()->getType()) {
        throw BadAssertExcpetion();
    }
}

void Vm::vmAdd(void){
    if (_stack.size() < 2) {
        throw MissingOperandException();
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) + (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmSub(void){
    if (_stack.size() < 2) {
        throw MissingOperandException();
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = *(*std::next(rit)) - *(*rit);
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmMul(void){
    if (_stack.size() < 2) {
        throw MissingOperandException();
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) * (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmDiv(void){
    if (_stack.size() < 2) {
        throw MissingOperandException();
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    if ((*rit)->toString() == "0") {
        throw DivisionByZeroException();
    }
    IOperand const* result = *(*std::next(rit)) / *(*rit);
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmMod(void){
    if (_stack.size() < 2) {
        throw MissingOperandException();
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    if ((*rit)->toString() == "0") {
        throw DivisionByZeroException();
    }if (
            (*std::next(rit))->getType() == Float ||
            (*std::next(rit))->getType() == Double ||
            (*rit)->getType() == Float ||
            (*rit)->getType() == Double
        ) {
        throw ModFloatException();
    }
    IOperand const* result = *(*std::next(rit)) % *(*rit);
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmPrint(void) const{
    if (_stack.back()->getType() != Int8) {
        throw BadAssertExcpetion();
    }
    char c = std::stoi(_stack.back()->toString());
    std::cout << c << std::endl; 
}

void Vm::vmExit(void) const{
    exit(0);
}

void Vm::vmExecute(std::list<SToken*> stlist) {
    std::map<std::string, eOperandType> typeMap = {
        {"int8", Int8},
        {"int16", Int16},
        {"int32", Int32},
        {"float", Float},
        {"double", Double},
    };
    std::list<SToken*>::iterator it = stlist.begin();
    for (;it != stlist.end(); it++)
    {
        std::string value = (*it)->value;
        if ((*it)->name == "Instruction") {
            if (value == "push") {
                vmPush((*(std::next(it, 3)))->value,typeMap[(*(std::next(it, 1)))->value]);
            }
            else if (value == "pop") vmPop();
            else if (value == "dump") vmDump();
            else if (value == "assert") vmAssert((*(std::next(it, 3)))->value,typeMap[(*(std::next(it, 1)))->value]);
            else if (value == "add") vmAdd();
            else if (value == "sub") vmSub();
            else if (value == "mul") vmMul();
            else if (value == "div") vmDiv();
            else if (value == "mod") vmMod();
            else if (value == "print") vmPrint();
            else if (value == "exit") vmExit();
        }
    }
    throw NoExitException();
}
//Getters and setters

//Exceptions
const char* Vm::EmptyStackException::what() const throw() {
    return("Exception: pop on empty stack");
}
const char* Vm::BadAssertExcpetion::what() const throw() {
    return("Exception: assertion failure");
}
const char* Vm::DivisionByZeroException::what() const throw() {
    return("Exception: division/modulo by zero");
}
const char* Vm::NoExitException::what() const throw() {
    return("Exception: missing exit instruction");
}
const char* Vm::MissingOperandException::what() const throw() {
    return("Exception: insufficient opperands on stack");
}
const char* Vm::ModFloatException::what() const throw() {
    return("Exception: Modulus of floating point values");
}
