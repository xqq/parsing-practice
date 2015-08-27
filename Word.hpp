#ifndef PARSING_PRACTICE_WORD_HPP
#define PARSING_PRACTICE_WORD_HPP

#include <stdexcept>
#include "Token.hpp"

class Word : public Token {
public:
    typedef std::shared_ptr<Word> Ref;

    static Ref Create(const std::string& s, int tag) {
        return std::make_shared<Word>(s, tag);
    }

    static const Word::Ref Add, Sub, Mul, Div;
public:
    Word(const std::string& s, int tag) : Token(tag), lexeme(s) { }

    virtual ~Word() = default;

    virtual float GetValue() override {
        throw std::runtime_error("Word: Unsupported operation");
    }

    virtual std::string ToString() const override {
        return lexeme;
    }
private:
    std::string lexeme;
};

#endif // PARSING_PRACTICE_WORD_HPP
