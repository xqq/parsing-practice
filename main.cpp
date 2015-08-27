#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Token.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "RPN.hpp"

int main(int argc, char** argv) {
    std::string input;
    std::stringstream istream;

    while (std::getline(std::cin, input)) {
        istream << input;

        try {
            Lexer lexer(istream);
            TokenList tokens;
            Parser parser(lexer, tokens);
            parser.Expr();

            std::cout << "Tokens: ";
            for (auto& token : tokens) {
                std::cout << token->ToString() << ' ';
            }
            std::cout << std::endl;

            std::cout << "Result: " << RPN::Eval(tokens) << std::endl;
        } catch (std::exception& ex) {
            std::cout << '\n' << ex.what() << std::endl;
        }

        istream.clear();
        istream.str("");
    }

    return 0;
}