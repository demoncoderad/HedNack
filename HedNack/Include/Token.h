//
// Created by minley on 10/02/22.
//

#ifndef HEDNACK_TOKEN_H
#define HEDNACK_TOKEN_H

#include <iostream>
#include <variant>
#include <map>

typedef std::variant<int, std::string, double, nullptr_t> literalval;

namespace HedNack {
    enum struct TokenType {
        FILEEND = -1,

        // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_CURLY, RIGHT_CURLY,
        COMMA, PERIOD, MINUS, PLUS, SEMICOLON, FORWARDSLASH, ASTERISK,

        // One or two character tokens.
        NOT, NOT_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESSER, LESSER_EQUAL,

          // Literals.
        IDENTIFIER, STRING, INTEGER_NUMBER, DECIMAL_NUMBER,

        // Keywords.
        AND, CLASS, ELSE, FALSE, FUNCT, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    };

    class Token {
    private:
        TokenType m_TokenType;
        std::string m_Lexeme;
        const literalval m_Literal;
        const int m_LineNo;
    public:

        static const std::map<std::string, TokenType> IDENTIFIER_MAP;
        Token(TokenType tokentype, std::string Lexeme, literalval Literal, const int LineNo)
            : m_TokenType(tokentype), m_Lexeme(Lexeme), m_Literal(Literal), m_LineNo(LineNo){}

        TokenType GetTokenType() const;
        std::string GetLexeme() const;

        friend std::ostream& operator<< (std::ostream& os, const Token& t);
    };

    inline std::ostream& operator<< (std::ostream& os, const Token& t) {
        os <<  static_cast<int>(t.m_TokenType) << " : " << t.m_Lexeme << " : " << t.m_LineNo;
        return os;
    }
}
#endif //HEDNACK_TOKEN_H
