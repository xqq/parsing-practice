#ifndef PARSING_PRACTICE_NUM_HPP
#define PARSING_PRACTICE_NUM_HPP

#include "Token.hpp"

class Num : public Token {
public:
    typedef std::shared_ptr<Num> Ref;

    static Ref Create(int v) {
        return std::make_shared<Num>(v);
    }
public:
    explicit Num(int v) : Token(Tags::kNum), value(v) { }

    virtual ~Num() = default;

    virtual float GetValue() override {
        return static_cast<float>(value);
    }

    virtual std::string ToString() const override {
        return std::to_string(value);
    }
private:
    int value;
};

#endif // PARSING_PRACTICE_NUM_HPP
