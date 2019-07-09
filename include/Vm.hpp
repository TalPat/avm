#ifndef VM_HPP
#define VM_HPP

#include <list>
#include "Operand.hpp"
#include "OperandFactory.hpp"

class Vm
{
private:
    std::list<IOperand const*> _stack;
    OperandFactory _factory;
public:
    Vm(/* args */);
    ~Vm();

    //vm commands
    void vmPush(std::string value, eOperandType type);
    void vmPop(void);
    void vmDump(void) const;
    void vmAssert(std::string value, eOperandType type) const;
    void vmAdd(void) const;
    void vmSub(void) const;
    void vmMul(void) const;
    void vmDiv(void) const;
    void vmMod(void) const;
    void vmPrint(void) const;
    void vmExit(void) const;
};

#endif
