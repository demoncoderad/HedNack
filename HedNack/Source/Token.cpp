//
// Created by minley on 10/02/22.
//

#include "Token.h"

const std::map<std::string, HedNack::TokenType> HedNack::Token::IDENTIFIER_MAP = {

        {"and",    HedNack::TokenType::AND},
        {"class",  HedNack::TokenType::CLASS},
        {"else",   HedNack::TokenType::ELSE},
        {"false",  HedNack::TokenType::FALSE},
        {"funct",  HedNack::TokenType::FUNCT},
        {"for",    HedNack::TokenType::FOR},
        {"if",     HedNack::TokenType::IF},
        {"nil",    HedNack::TokenType::NIL},
        {"or",     HedNack::TokenType::OR},
        {"print",  HedNack::TokenType::PRINT},
        {"return", HedNack::TokenType::RETURN},
        {"super",  HedNack::TokenType::SUPER},
        {"this",   HedNack::TokenType::THIS},
        {"true",   HedNack::TokenType::TRUE},
        {"var",    HedNack::TokenType::VAR},
        {"while",  HedNack::TokenType::WHILE}

};

HedNack::TokenType HedNack::Token::GetTokenType() const {
    return m_TokenType;
}

std::string HedNack::Token::GetLexeme() const {
    return m_Lexeme;
}
