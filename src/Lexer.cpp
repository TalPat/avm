#include "Lexer.hpp"

//Constructor and destructor

Lexer::Lexer(/* args */)
{
}

Lexer::~Lexer()
{
}

//Copy constructor & assignment overide

//Class methods
void Lexer::fetchFromFile(std::string avmFile) {
    std::string line;
    std::ifstream myfile (avmFile);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            _source += line + '\n';
        }
        myfile.close();
    } else {
        // throw error
        /* */std::cout << "failing" << std::endl;
    }
}

void Lexer::fetchFromIn(void) {
    std::string line;
    while (1) {
        std::getline(std::cin, line);
        if (line.compare(";;") == 0) break;
        _source += line + "\n";
    }
}

void Lexer::removeComments(void) {
    while (_source.find(';') != std::string::npos) {
        _source.erase(_source.find(';'),_source.find('\n', _source.find(';')) - _source.find(';') + 1);
    }
}

bool Lexer::isInt(std::string str) {
    std::string::const_iterator it = str.begin();
    if ((*it == '-' && str.length() > 1) || std::isdigit(*it)) {
        it++;
        while (it != str.end() && std::isdigit(*it)) ++it;
        return !str.empty() && it == str.end();
    } else {
        return (false);
    }
}

bool Lexer::isFloat(std::string str) {
    if (std::count(str.begin(), str.end(), '.') > 1) return (false);
    std::string::const_iterator it = str.begin();
    if ((*it == '-' && str.length() > 1) || std::isdigit(*it)) {
        it++;
        while (it != str.end() && (std::isdigit(*it) || (*it) == '.')) ++it;
        return !str.empty() && it == str.end();
    } else {
        return (false);
    }
}

std::string Lexer::determineName(std::string token) {
    if (token == "\n" || token == "(" || token == ")") return ("Separator");
    else if (token == "push" || token == "pop" || token == "dump"  || token == "assert"  || token == "add"  || token == "sub" || token == "mul" || token == "div" || token == "mod" || token == "print" || token == "exit") return ("Instruction");
    else if (token == "int8" || token == "int16" || token == "int32" || token == "float" || token == "double") return ("Type");
    else if (isInt(token)) return ("iValue");
    else if (isFloat(token)) return("fValue");
    else {
        //throw lexing error
        /* */return ("basd");
    }
}

void Lexer::tokenize(void) {
    std::string delimiter = " ";
    size_t stringSize = 0;
    std::string keyWords[] = {"push", "pop", "dump" , "assert" , "add" , "sub", "mul", "div", "mod", "print", "exit", "int8", "int16", "int32", "float", "double", "\n", "(", ")"};

    removeComments();

    std::string token;
    while (_source.length() > 0) {
        if (_source.find(" ") == 0) {
            _source.erase(0, 1);
        } else {
            for(const std::string& word: keyWords) {
                if (_source.find(word) == 0) {
                    SToken* stoken = new SToken;
                    stoken->name = determineName(word);
                    stoken->value = word;
                    _tokenList.push_back(stoken);
                    /* */std::cout << _tokenList.back()->name << " " << _tokenList.back()->value << std::endl;
                    _source.erase(0, word.length());
                    break;
                }
                if (isInt(_source.substr(0, _source.find(")"))) || isFloat(_source.substr(0, _source.find(")")))) {
                    SToken* stoken = new SToken;
                    stoken->name = determineName(_source.substr(0, _source.find(")")));
                    stoken->value = _source.substr(0, _source.find(")"));
                    _tokenList.push_back(stoken);
                    /* */std::cout << _tokenList.back()->name << " " << _tokenList.back()->value << std::endl;
                    _source.erase(0, _source.substr(0, _source.find(")")).length());
                    break;
                }
            }
        }
        if (stringSize == _source.length()) {
            /* */break;
            //throw error
        }
        stringSize = _source.length();
    }
}

//Getters and setters
