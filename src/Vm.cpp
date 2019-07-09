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

void Vm::vmAdd(void) const{
    
}

//Getters and setters
