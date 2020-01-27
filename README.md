# avm
# C++ Project

## Abstract VM

_Summary: The purpose of this project is to create a simple virtual machine that can
interpret programs written in a basic assembly language._


## Contents

- I A Machine
- II The project
   - II.1 The assembly language
      - II.1.1 Example
      - II.1.2 Description
      - II.1.3 Grammar
      - II.1.4 Errors
      - II.1.5 Execution
- III Mandatory part
   - III.1 Generic instructions
   - III.2 The IOperand interface
   - III.3 Creation of a new operand
   - III.4 The precision
   - III.5 The Stack
- IV Bonus part


# Chapter I

# A Machine

A machine, virtual or not, has a specific architecture. The only real difference between
a virtual machine and a physical one is that the physical one uses real electronic compo-
nents, while a virtual one emulates them by using to a program.

A virtual machine is nothing more than a program that simulates a physical machine,
or another virtual machine. Nevertheless, it is clear that a virtual machine that emulates
a physical machine such as a desktop computer is a very advanced program that requires
an important programming experience as well as a very in-depth architectural knowledge.

For this project, requirements will be limited to a very simple virtual machine: it will
run some basic arithmetic programs coded in a very basic assembly language. If you want
to have an idea of what your program’s capabilities should look like, type the command
man dcin your shell.

The virtual machine we are describing has a classical architecture. However you may
wonder what a classical architecture is...

There is no easy answer to this question. It depends on the precision you want to
adopt, as well as the kind of problem you are looking at. Each "organ" of a machine can
be translated into a program or set of (more or less) complex functions. Moreover, this
complexity is linked to what your machine is used for in the end. Let’s look at memory
for instance. We do agree that the emulation complexity of a machine’s memory between
a virtual machine running an operating system, such as Linux or Windows, and a virtual
machine running a CoreWar is completely different!

```
Whatever decision you make, you really should have a look at these articles:
```
1. [http://en.wikipedia.org/wiki/Central_processing_unit](http://en.wikipedia.org/wiki/Central_processing_unit)
2. [http://en.wikipedia.org/wiki/Chipset](http://en.wikipedia.org/wiki/Chipset)
3. [http://en.wikipedia.org/wiki/Computer_data_storage](http://en.wikipedia.org/wiki/Computer_data_storage)
4. [http://en.wikipedia.org/wiki/Input/output](http://en.wikipedia.org/wiki/Input/output)


# Chapter II

# The project

```
AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.
```
### II.1 The assembly language

#### II.1.1 Example

As an example is still better that all the possible explanations in the world, this is an
example of an assembly program that your machine will be able to compute:
```
1 ; -------------
2 ; exemple.avm -
3 ; -------------
4
5 push int32(42)
6 push int32(33)
7
8 add
9
10 push float(44.55)
11
12 mul
13
14 push double(42.42)
15 push int32(42)
16
17 dump
18
19 pop
20
21 assert double(42.42)
22
23 exit
```


**C++ Project Abstract VM**

#### II.1.2 Description

As for any assembly language, the language ofAbstractVMis composed of a series of
instructions, with one instruction per line. However, AbstractVM’s assembly language
has a limited type system, which is a major difference from other real world assembly
languages.

- Comments: Comments start with a’;’and finish with a newline. A comment can
    be either at the start of a line, or after an instruction.
- **push** **_v_** : Pushes the value _v_ at the top of the stack. The value _v_ must have one of
    the following form:

```
◦ int8( n ) : Creates an 8-bit integer with value n.
```
```
◦ int16( n ) : Creates a 16-bit integer with value n.
```
```
◦ int32( n ) : Creates a 32-bit integer with value n.
```
```
◦ float( z ) : Creates a float with value z.
```
```
◦ double( z ) : Creates a double with value z.
```
- **pop** : Unstacks the value from the top of the stack. If the stack is empty, the
    program execution must stop with an error.
- **dump** : Displays each value of the stack, from the most recent one to the oldest
    one WITHOUT CHANGING the stack. Each value is separated from the next one
    by a newline.
- **assert** **_v_** : Asserts that the value at the top of the stack is equal to the one passed
    as parameter for this instruction. If it is not the case, the program execution must
    stop with an error. The value _v_ has the same form that those passed as parameters
    to the instruction **push**.
- **add** : Unstacks the first two values on the stack, adds them together and stacks the
    result. If the number of values on the stack is strictly inferior to 2, the program
    execution must stop with an error.
- **sub** : Unstacks the first two values on the stack, subtracts them, then stacks the
    result. If the number of values on the stack is strictly inferior to 2, the program
    execution must stop with an error.
- **mul** : Unstacks the first two values on the stack, multiplies them, then stacks the
    result. If the number of values on the stack is strictly inferior to 2, the program
    execution must stop with an error.


**C++ Project Abstract VM**

- **div** : Unstacks the first two values on the stack, divides them, then stacks the result.
    If the number of values on the stack is strictly inferior to 2, the program execution
    must stop with an error. Moreover, if the divisor is equal to 0, the program execution
    must stop with an error too. Chatting about floating point values is relevant a this
    point. If you don’t understand why, some will understand. The linked question is
    an open one, there’s no definitive answer.
- **mod** : Unstacks the first two values on the stack, calculates the modulus, then
    stacks the result. If the number of values on the stack is strictly inferior to 2, the
    program execution must stop with an error. Moreover, if the divisor is equal to 0,
    the program execution must stop with an error too. Same note as above about fp
    values.
- **print** : Asserts that the value at the top of the stack is an 8-bit integer. (If not,
    see the instructionassert), then interprets it as an ASCII value and displays the
    corresponding character on the standard output.
- **exit** : Terminate the execution of the current program. If this instruction does not
    appears while all others instruction has been processed, the execution must stop
    with an error.

```
For non commutative operations, consider the stack v1 on v2 on
stack_tail, the calculation in infix notation v2 op v1.
```
When a computation involves two operands of different types, the value returned has
the type of the more precise operand. Please do note that because of the extensibility of
the machine, the precision question is not a trivial one. This is covered more in details
later in this document.


```
C++ Project Abstract VM
```
#### II.1.3 Grammar

```
The assembly language ofAbstractVMis generated from the following grammar (#cor-
responds to the end of the input, not to the character’#’):
```
1 S := INSTR [SEP INSTR]* #
2
3 INSTR :=
4 push VALUE
5 | pop
6 | dump
7 | assert VALUE
8 | add
9 | sub
10 | mul
11 | div
12 | mod
13 | print
14 | exit
15
16 VALUE :=
17 int8(N)
18 | int16(N)
19 | int32(N)
20 | float(Z)
21 | double(Z)
22
23 N := [-]?[0..9]+
24
25 Z := [-]?[0..9]+.[0..9]+
26
27 SEP :='\n'+

#### II.1.4 Errors

```
When one of the following cases is encountered,AbstractVMmust raise an exception
and stop the execution of the program cleanly. It is forbidden to raise scalar exceptions.
Moreover your exception classes must inherit fromstd::exception.
```
- The assembly program includes one or several lexical errors or syntactic errors.
- An instruction is unknown
- Overflow on a value
- Underflow on a value
- Instruction pop on an empty stack
- Division/modulo by 0
- The program doesn’t have anexitinstruction
- Anassertinstruction is not true
- The stack is composed of strictly less that two values when an arithmetic instruction
    is executed.

```
Perhaps there are more errors cases. However, you machine must never crash (segfault,
bus error, infinite loop, unhandled exception, ...).
```

```
C++ Project Abstract VM
```
#### II.1.5 Execution

```
Your machine must be able to run programs from a file passed as a parameter and from
the standard input. When reading from the standard input, the end of the program is
indicated by the special symbol";;"otherwise absent.
```
```
Be very careful avoiding conflicts during lexical or syntactic
analysis between ";;" (end of a program read from the standard input)
and ";" (beginning of a comment.)
```
Now let see some examples of execution:
1 $>./avm
2 push int32(2)
3 push int32(3)
4 add
5 assert int32(5)
6 dump
7 exit
8 ;;
95
10 $>

1 $>cat sample.avm
2 ; -------------
3 ; sample.avm -
4 ; -------------
5
6 push int32(42)
7 push int32(33)
8 add
9 push float(44.55)
10 mul
11 push double(42.42)
12 push int32(42)
13 dump
14 pop
15 assert double(42.42)
16 exit
17 $>./avm ./sample.avm
1842
19 42.
20 3341.
21 $>

```
1 $>./avm
2 pop
3 ;;
4 Line 1 : Error : Pop on empty stack
5 $>
```
```
The error message is given as an example. Feel free to use yours
instead.
```

# Chapter III

# Mandatory part

In order to help you with your project, we provide you with the following instructions
that you **MUST** respect.

### III.1 Generic instructions

- You are free to use any compiler you like.
- Your code must compile with:-Wall -Wextra -Werror.
- You are free to use anyC++version you like.
- You are free to use any library you like.
- You must provide a Makefile with the usual rules.
- Any class that declares at least one attribute must be written in canonical form. In-
    heriting from a class that declares attributes does not count as declaring attributes.
- It’s forbidden to implement any function in a header file, except for templates and
    the virtual destructor of a base class.
- The “keyword”"using namespace"is forbidden.


**C++ Project Abstract VM**

### III.2 The IOperand interface

AbstractVMuses 5 operand classes that you must declare and define:

- **Int8** : Representation of a signed integer coded on 8bits.
- **Int16** : Representation of a signed integer coded on 16bits.
- **Int32** : Representation of a signed integer coded on 32bits.
- **Float** : Representation of a float.
- **Double** : Representation of a double.

```
Each one of these operand classes MUST implement the followingIOperandinterface:
```
```
class IOperand{
public :
virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
virtual eOperandType getType( void ) const = 0; // Type of the instance
virtual IOperand const * operator +( IOperand const & rhs ) const = 0; // Sum
virtual IOperand const * operator -( IOperand const & rhs ) const = 0; // Difference
virtual IOperand const * operator *( IOperand const & rhs ) const = 0; // Product
virtual IOperand const * operator /( IOperand const & rhs ) const = 0; // Quotient
virtual IOperand const * operator %( IOperand const & rhs ) const = 0; // Modulo
virtual std::string const & toString( void ) const = 0; // String representation of the instance
virtual ~IOperand( void ) {}
};
```
Considering similarities between operand classes, it can be relevant to use a class
template. However, this is not mandatory.


**C++ Project Abstract VM**

### III.3 Creation of a new operand

New operands **MUST** be created via a "factory method". SearchGoogleif you don’t
know what it is. This member function must have the following prototype:

```
IOperand const * createOperand( eOperandType type, std::string const & value ) const ;
```
TheeOperandTypetype is anenumdefining the following values:Int8,Int16,Int32,
FloatandDouble.

Depending on theenumvalue passed as a parameter, the member functioncreateOperand
creates a newIOperandby calling one of the followingprivatemember functions:

```
IOperand const * createInt8( std::string const & value ) const ;
IOperand const * createInt16( std::string const & value ) const ;
IOperand const * createInt32( std::string const & value ) const ;
IOperand const * createFloat( std::string const & value ) const ;
IOperand const * createDouble( std::string const & value ) const ;
```
In order to choose the right member function for the creation of the newIOperand,
you **MUST** create and use an array (here, avectorshows little interest) of pointers on
member functions with enum values as index.

### III.4 The precision

When an operation happens between two operands of the same type, there is no problem.
However, what about when the types are different? The usual method is to order types
using their precision. For this machine you should use the following order:Int8 < Int
< Int32 < Float < Double. This order may be represented as anenum, asenumvalues
evaluate to integers.

The pure methodgetPrecisionfrom the interfaceIOperandallows to get the preci-
sion of an operand. When an operation uses two operands from two different types, the
comparison of theirs precisions allows to figure out the result type of the operation.

### III.5 The Stack

AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
another container that behaves like a stack is up to you. Whatever the container, itMUST
only contain pointers to the abstract typeIOperand.


# Chapter IV

# Bonus part

Once you’re done with the mandatory part and sure you’ll get the maximum grade for
it, consider doing the following bonuses :

- Making your VM capable of diagnosing all errors in a file without stopping at the
    first error encountered.
- Having a well structured lexer/parser couple, with clearly defined roles.

You can add some bonuses of your own creation if you like, but most of the bonus
points will be reserved for the above bonuses.


