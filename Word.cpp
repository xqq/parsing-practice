#include "Word.hpp"

const Word::Ref Word::Add = Word::Create("+", Tags::kAdd);
const Word::Ref Word::Sub = Word::Create("-", Tags::kSub);
const Word::Ref Word::Mul = Word::Create("*", Tags::kMul);
const Word::Ref Word::Div = Word::Create("/", Tags::kDiv);
