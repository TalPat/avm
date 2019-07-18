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
    Vm(Vm &obj);
    Vm& operator=(const Vm &obj);

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

    //Exceptions
    class EmptyStackException : public std::exception {
        public:
            virtual const char* what() const throw();
    };
    class BadAssertExcpetion : public std::exception {
        public:
            virtual const char* what() const throw();
    };
    class DivisionByZeroException : public std::exception {
        public:
            virtual const char* what() const throw();
    };
    class NoExitException : public std::exception {
        public:
            virtual const char* what() const throw();
    };
    class MissingOperandException : public std::exception {
        public:
            virtual const char* what() const throw();
    };
    class ModFloatException : public std::exception {
        public:
            virtual const char* what() const throw();
    };
};

#endif
