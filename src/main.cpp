#include "Lexer.hpp"

int main(int argc, char** argv) {
    Lexer lexer;
    if (argc == 1) {
        lexer.fetchFromIn();
        lexer.tokenize();
    } else {
        lexer.fetchFromFile(argv[1]);
        lexer.tokenize();
    }
}