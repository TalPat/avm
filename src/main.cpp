#include "Lexer.hpp"
#include "Parser.hpp"
#include "Vm.hpp"

int main(int argc, char** argv) {
    Lexer lexer;
    Parser parser;
    Vm vm;
    
    try
    {
        if (argc == 1) {
            lexer.fetchFromIn();
            lexer.tokenize();
        } else {
            lexer.fetchFromFile(argv[1]);
            lexer.tokenize();
        }
        parser.checkGrammar(lexer.getTokenList());
        vm.vmExecute(lexer.getTokenList());
    }
    catch(const Lexer::BadFileException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Lexer::LexingException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Parser::InvalidInstructionExcepion& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const IOperand::OverflowException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const IOperand::UnderflowException& e){
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Vm::EmptyStackException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Vm::BadAssertExcpetion& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Vm::DivisionByZeroException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Vm::NoExitException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Vm::MissingOperandException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Vm::ModFloatException& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
}