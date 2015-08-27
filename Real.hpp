#ifndef PARSING_PRACTICE_REAL_HPP
#define PARSING_PRACTICE_REAL_HPP

#include "Token.hpp"

class Real : public Token {
public:
    typedef std::shared_ptr<Real> Ref;

    static Ref Create(float v) {
        return std::make_shared<Real>(v);
    }
public:
    explicit Real(float v) : Token(Tags::kReal), value(v) { }

    virtual ~Real() = default;

    virtual float GetValue() override {
        return value;
    }

    virtual std::string ToString() const override {
        return std::to_string(value);
    }
private:
    float value;
};

#endif // PARSING_PRACTICE_REAL_HPP
