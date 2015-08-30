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
            if (lookahead == Word::Add || lookahead == Word::Sub) {
                Token::Ref current = lookahead;
                Match(lookahead);
                Term();
                tokenList.push_back(current);
            } else {
                return;
            }
        }
    }
private:
    void Term() {
        Factor();
        while (true) {
            if (lookahead == Word::Mul || lookahead == Word::Div) {
                Token::Ref current = lookahead;
                Match(lookahead);
                Factor();
                tokenList.push_back(current);
            } else {
                return;
            }
        }
    }

    void Factor() {
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
            std::string message("Syntax error: Unexcepted token ");
            message.append(t->ToString());
            throw std::logic_error(message);
        }
    }
private:
    Lexer& lexer;
    Token::Ref lookahead;
    TokenList& tokenList;
};

#endif // PARSING_PRACTICE_PARSER_HPP
