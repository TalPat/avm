#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char** argv) {
    Lexer lexer;
    Parser parser;
    
    if (argc == 1) {
        lexer.fetchFromIn();
        lexer.tokenize();
    } else {
        lexer.fetchFromFile(argv[1]);
        lexer.tokenize();
    }
    parser.checkGrammar(lexer.getTokenList());
}