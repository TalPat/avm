#ifndef VM_HPP
#define VM_HPP

#include <list>
#include <map>
#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "SToken.hpp"

class Vm
{
private:
    std::list<IOperand const*> _stack;
    OperandFactory _factory;
    std::map<std::string, eOperandType> _typeMap = {
        {"Int8", Int8},
        {"Int16", Int16},
        {"Int32", Int32},
        {"Float", Float},
        {"Double", Double},
    };
public:
    Vm(/* args */);
    ~Vm();

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
};

#endif
