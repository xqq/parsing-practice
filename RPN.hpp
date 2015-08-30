#ifndef PARSING_PRACTICE_RPN_HPP
#define PARSING_PRACTICE_RPN_HPP

#include <stack>
#include "Token.hpp"
#include "Num.hpp"
#include "Token.hpp"

class RPN {
public:
    static float Eval(TokenList& list) {
        std::stack<Token::Ref> stack;

        for (auto& token : list) {
            int tag = token->GetTag();

            if (tag == Tags::kNum || tag == Tags::kReal) {
                stack.push(token);
            } else if (tag == Tags::kAdd || tag == Tags::kSub || tag == Tags::kMul || tag == Tags::kDiv) {
                Token::Ref top1 = stack.top(); stack.pop();
                Token::Ref top2 = stack.top(); stack.pop();
                if (top1->IsNumber() && top2->IsNumber()) {
                    float value2 = top1->GetValue();
                    float value1 = top2->GetValue();
                    float result = 0;
                    if (tag == Tags::kAdd || tag == Tags::kSub) {
                        result = tag == Tags::kAdd ? value1 + value2 : value1 - value2;
                    } else if (tag == Tags::kMul || tag == Tags::kDiv) {
                        result = tag == Tags::kMul ? value1 * value2 : value1 / value2;
                    }
                    stack.push(Real::Create(result));
                } else {
                    throw std::runtime_error("Eval error: Unexcepted stack top element");
                }
            } else {
                throw std::runtime_error("Eval error: Unexpected token");
            }
        }
        if (stack.size() != 1) {
            throw std::runtime_error("Eval error: Stack size != 1");
        }
        return stack.top()->GetValue();
    }
};

#endif // PARSING_PRACTICE_RPN_HPP
