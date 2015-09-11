#ifndef PARSING_PRACTICE_TOKEN_HPP
#define PARSING_PRACTICE_TOKEN_HPP

#include <string>
#include <vector>
#include "smartref/RefBase.hpp"
#include "smartref/RefPtr.hpp"

enum Tags : int {
    kNum, kReal, kAdd, kSub, kMul, kDiv, kEof
};

class Token : public xl::RefBase {
public:
    typedef xl::RefPtr<Token> Ref;

    static Ref Create(int t) {
        return xl::RefPtr<Token>(new Token(t));
    }
public:
    explicit Token(int t) : tag(t) { }

    virtual ~Token() = default;

    int GetTag() {
        return tag;
    }

    bool IsNumber() {
        return tag == Tags::kNum || tag == Tags::kReal;
    }

    virtual float GetValue() {
        return 0.0f;
    }

    virtual std::string ToString() const {
        return std::to_string(tag);
    }
private:
    explicit Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;
private:
    int tag;
};

typedef std::vector<Token::Ref> TokenList;

#endif // PARSING_PRACTICE_TOKEN_HPP
