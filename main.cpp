#include <cstdlib>
#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

enum Tags : int {
    kNum, kReal, kAdd, kSub, kMul, kDiv
};

class Token {
public:
    typedef std::shared_ptr<Token> Ref;

    static Ref Create(int t) {
        return std::make_shared<Token>(t);
    }
public:
    explicit Token(int t) : tag(t) { }

    virtual ~Token() = default;

    int GetTag() {
        return tag;
    }

    virtual std::string ToString() const {
        return std::to_string(tag);
    }
private:
    int tag;
};

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

    virtual std::string ToString() const override {
        return lexeme;
    }
private:
    std::string lexeme;
};

const Word::Ref Word::Add = Word::Create("+", Tags::kAdd);
const Word::Ref Word::Sub = Word::Create("-", Tags::kSub);
const Word::Ref Word::Mul = Word::Create("*", Tags::kMul);
const Word::Ref Word::Div = Word::Create("/", Tags::kDiv);

class Num : public Token {
public:
    typedef std::shared_ptr<Num> Ref;

    static Ref Create(int v) {
        return std::make_shared<Num>(v);
    }
public:
    explicit Num(int v) : Token(Tags::kNum), value(v) { }

    virtual ~Num() = default;

    virtual std::string ToString() const override {
        return std::to_string(value);
    }
private:
    int value;
};

class Real : public Token {
public:
    typedef std::shared_ptr<Real> Ref;

    static Ref Create(float v) {
        return std::make_shared<Real>(v);
    }
public:
    explicit Real(float v) : Token(Tags::kReal), value(v) { }

    virtual ~Real() = default;

    virtual std::string ToString() const override {
        return std::to_string(value);
    }
private:
    float value;
};

class Lexer {
public:
    Lexer(std::istream& sm) : peek(' '), stream(sm) { }

    void ReadChar() {
        stream.get(peek);
    }

    bool ReadMatchChar(char c) {
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
                return Word::Add;
            case '-':
                return Word::Sub;
            case '*':
                return Word::Mul;
            case '/':
                return Word::Div;
        }

        if (isdigit(peek)) {
            int v = 0;
            char buffer[2] = {peek, 0};

            do {
                v = v * 10 + atoi(buffer);
                ReadChar();
            } while (isdigit(peek));

            if (peek != '.') {
                return Num::Create(v);
            }

            float x = v, d = 10;
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

        std::string error("Lexer error: Unexcepted char ");
        error.append(std::to_string(peek));
        throw std::invalid_argument(error);
    }

private:
    char peek;
    std::istream& stream;
};


class Parser {
public:
    explicit Parser(Lexer* l, std::ostream& osm) : lexer(l), ostream(osm) {
        lookahead = lexer->Scan();
    }

    void Expr() {
        Term();
        while (true) {
            if (lookahead == Word::Add) {
                Match(Word::Add);
                Term();
                ostream << '+';
            } else if (lookahead == Word::Sub) {
                Match(Word::Sub);
                Term();
                ostream << '-';
            } else {
                return;
            }
        }
    }
private:
    void Term() {
        if (lookahead->GetTag() == Tags::kNum || lookahead->GetTag() == Tags::kReal) {
            ostream << lookahead->ToString();
            Match(lookahead);
        } else {
            throw std::logic_error("Syntax error");
        }
    }

    void Match(Token::Ref t) {
        if (lookahead == t) {
            lookahead = lexer->Scan();
        } else {
            throw std::logic_error("Syntax error: Unexcepted token");
        }
    }
private:
    Lexer* lexer;
    Token::Ref lookahead;
    std::ostream& ostream;
};

int main() {
    std::stringstream istream;
    std::stringstream ostream;
    std::string input;

    while (std::getline(std::cin, input)) {
        istream << input;
        try {
            Lexer lexer(istream);
            Parser parser(&lexer, ostream);
            parser.Expr();
        } catch (std::exception& ex) {
            std::cout << '\n' << ex.what() << std::endl;
        }
        std::cout << "Result: " << ostream.str() << std::endl;
        istream.str("");
        ostream.str("");
    }

    return 0;
}