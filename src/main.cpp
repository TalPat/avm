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
    }
    catch(const Lexer::BadFileException& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Lexer::LexingException& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    catch(const Parser::InvalidInstructionExcepion& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    vm.vmExecute(lexer.getTokenList());
}