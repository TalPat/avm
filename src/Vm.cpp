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

//Copy constructor & assignment overide



//Class methods

void Vm::vmPush(std::string value, eOperandType valType) {
    _stack.push_back(_factory.createOperand(valType, value));
}

void Vm::vmPop(void) {
    if (_stack.size() < 1) {
        //throw error
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
    if (_stack.back()->toString().compare(value) || valType != _stack.back()->getType()) {
        //throw error
    }
}

void Vm::vmAdd(void){
    if (_stack.size() < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) + (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmSub(void){
    if (_stack.size() < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = *(*std::next(rit)) - *(*rit);
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmMul(void){
    if (_stack.size() < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) * (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmDiv(void){
    if (_stack.size() < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = *(*std::next(rit)) / *(*rit);
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmMod(void){
    if (_stack.size() < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = *(*std::next(rit)) % *(*rit);
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmPrint(void) const{
    if (_stack.back()->getType() != Int8) {
        //throw err
    }
    char c = std::stoi(_stack.back()->toString());
    std::cout << c << std::endl; 
}

void Vm::vmExit(void) const{
    //clear memory
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
}
//Getters and setters
