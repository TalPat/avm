#ifndef VM_HPP
#define VM_HPP

#include <list>
#include <map>
#include "../src/Operand.cpp"
#include "OperandFactory.hpp"
#include "SToken.hpp"

class Vm
{
private:
    std::list<IOperand const*> _stack;
    OperandFactory _factory;
public:
    //constructor and destructor
    Vm(/* args */);
    ~Vm();

    //copy constructor && assignment overload

    //vm commands
    void vmPush(std::string value, eOperandType type);
    void vmPop(void);
    void vmDump(void) const;
    void vmAssert(std::string value, eOperandType type) const;
    void vmAdd(void);
    void vmSub(void);
    void vmMul(void);
    void vmDiv(void);
    void vmMod(void);
    void vmPrint(void) const;
    void vmExit(void) const;

    void vmExecute(std::list<SToken*> tokenList);

    //getters and setters
};

#endif
