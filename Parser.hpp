#ifndef PARSING_PRACTICE_PARSER_HPP
#define PARSING_PRACTICE_PARSER_HPP

#include "Lexer.hpp"

class Parser {
public:
    Parser(Lexer& l, TokenList& tlist) : lexer(l), tokenList(tlist) {
        lookahead = lexer.Scan();
    }

    void Expr() {
        Term();
        while (true) {
            if (lookahead == Word::Add) {
                Match(Word::Add);
                Term();
                tokenList.push_back(Word::Add);
            } else if (lookahead == Word::Sub) {
                Match(Word::Sub);
                Term();
                tokenList.push_back(Word::Sub);
            } else {
                return;
            }
        }
    }
private:
    void Term() {
        if (lookahead->GetTag() == Tags::kNum || lookahead->GetTag() == Tags::kReal) {
            tokenList.push_back(lookahead);
            Match(lookahead);
        } else {
            throw std::logic_error("Syntax error: Expect a Num/Real");
        }
    }

    void Match(Token::Ref t) {
        if (lookahead == t) {
            lookahead = lexer.Scan();
        } else {
            throw std::logic_error("Syntax error: Unexcepted token");
        }
    }
private:
    Lexer& lexer;
    Token::Ref lookahead;
    TokenList& tokenList;
};

#endif // PARSING_PRACTICE_PARSER_HPP
