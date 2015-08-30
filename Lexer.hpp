#ifndef PARSING_PRACTICE_LEXER_HPP
#define PARSING_PRACTICE_LEXER_HPP

#include <sstream>
#include "Token.hpp"
#include "Word.hpp"
#include "Num.hpp"
#include "Real.hpp"

class Lexer {
public:
    explicit Lexer(std::istream& sm) : peek(' '), stream(sm) { }

    void ReadChar() {
        stream.get(peek);
        if (stream.eof()) {
            peek = 0;
        }
    }

    bool MatchChar(char c) {
        ReadChar();
        if (peek != c) {
            return false;
        }
        peek = ' ';
        return true;
    }

    Token::Ref Scan() {
        for (;;ReadChar()) {
            if (peek == ' ' || peek == '\t') {
                continue;
            } else {
                break;
            }
        }

        switch (peek) {
            case '+':
                ReadChar();
                return Word::Add;
            case '-':
                ReadChar();
                return Word::Sub;
            case '*':
                ReadChar();
                return Word::Mul;
            case '/':
                ReadChar();
                return Word::Div;
        }

        if (isdigit(peek)) {
            int v = 0;
            char buffer[2] = {0};

            do {
                buffer[0] = peek;
                v = v * 10 + atoi(buffer);
                ReadChar();
            } while (isdigit(peek));

            if (peek != '.') {
                return Num::Create(v);
            }

            float x = static_cast<float>(v), d = 10;
            while (true) {
                ReadChar();
                if (!isdigit(peek)) {
                    break;
                }
                buffer[0] = peek;
                x = x + atoi(buffer) / d;
                d = d * 10;
            }
            return Real::Create(x);
        }

        if (peek == 0) {
            return Token::Create(Tags::kEof);
        }

        std::string error("Lexer error: Unexcepted char ");
        char buf[2] = {peek, 0};
        error.append(buf);
        throw std::invalid_argument(error);
    }

private:
    char peek;
    std::istream& stream;
};

#endif // PARSING_PRACTICE_LEXER_HPP
