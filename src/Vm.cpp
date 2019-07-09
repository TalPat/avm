#include "Vm.hpp"
#include <iostream>

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
    if (_stack.size < 1) {
        //throw error
    }
    _stack.pop_back();
}

void Vm::vmDump(void) const {
    for (std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin(); rit != _stack.rend(); rit++) {
        std::cout << (*rit)->toString() << std::endl;
    }
}

void Vm::vmAssert(std::string value, eOperandType valType) const{
    if (_stack.back()->toString().compare(value) || valType != _stack.back()->getType()) {
        //throw error
    }
}

void Vm::vmAdd(void){
    if (_stack.size < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) + (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmSub(void){
    if (_stack.size < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) - (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmMul(void){
    if (_stack.size < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) * (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmDiv(void){
    if (_stack.size < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) / (*(*(++rit))));
    this->vmPop();
    this->vmPop();
    _stack.push_back(result);
}

void Vm::vmMod(void){
    if (_stack.size < 2) {
        //throw err
    }
    std::list<IOperand const*>::reverse_iterator rit = _stack.rbegin();
    IOperand const* result = ((*(*rit)) % (*(*(++rit))));
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
//Getters and setters
