//
// Created by minley on 10/02/22.
//

#include "Scanner.h"

std::vector<HedNack::Token>& HedNack::Scanner::ScanTokens() {

    // Loop over all characters
    while (!IsAtEnd()) {
        m_start = m_current;
        ScanToken();
    }

    m_Tokens.emplace_back(TokenType::FILEEND, "", nullptr, m_currentLineNo);
    return m_Tokens;
}

bool HedNack::Scanner::IsAtEnd() {
    return m_current >= m_Source.length();
}

char HedNack::Scanner::Advance() {
    return m_Source[m_current++];
}

void HedNack::Scanner::ScanToken() {
    char c = Advance();
    switch (c) {
        #pragma region SINGLE_TOKENS
                case '+' : {
                    AddToken(TokenType::PLUS);
                    break;
                }
                case '-' : {
                    AddToken(TokenType::MINUS);
                    break;
                }
                case '*' : {
                    AddToken(TokenType::ASTERISK);
                    break;
                }
                case '{' : {
                    AddToken(TokenType::LEFT_CURLY);
                    break;
                }
                case '}' : {
                    AddToken(TokenType::RIGHT_CURLY);
                    break;
                }
                case '(' : {
                    AddToken(TokenType::LEFT_PAREN);
                    break;
                }
                case ')' : {
                    AddToken(TokenType::RIGHT_PAREN);
                    break;
                }
                case '.' : {
                    AddToken(TokenType::PERIOD);
                    break;
                }
                case ',' : {
                    AddToken(TokenType::COMMA);
                    break;
                }
                case ';' : {
                    AddToken(TokenType::SEMICOLON);
                    break;
                }
        #pragma endregion SINGLE_TOKENS
        #pragma region DOUBLE_TOKENS
                case '!': {
                    if (PeekAt() == '=') {
                        Advance();
                        AddToken(TokenType::NOT_EQUAL);
                        return;
                    }
                    AddToken(TokenType::NOT);
                    break;
                }
                case '=': {
                    if (PeekAt() == '=') {
                        Advance();
                        AddToken(TokenType::EQUAL_EQUAL);
                        return;
                    }
                    AddToken(TokenType::EQUAL);
                    break;
                }
                case '>': {
                    if (PeekAt() == '=') {
                        Advance();
                        AddToken(TokenType::GREATER_EQUAL);
                        return;
                    }
                    AddToken(TokenType::GREATER);
                    break;
                }
                case '<': {
                    if (PeekAt() == '=') {
                        Advance();
                        AddToken(TokenType::LESSER_EQUAL);
                        return;
                    }
                    AddToken(TokenType::LESSER);
                    break;
                }
        #pragma endregion DOUBLE_TOKENS
        #pragma region COMMENTS
                    // Division + Comment
                case '/': {
                    if (PeekAt() == '/') {
                        while (PeekAt() != '\n' && !IsAtEnd()) Advance();
                    } else {
                        AddToken(TokenType::FORWARDSLASH);
                    }
                    break;
                }
        #pragma endregion COMMENTS
        #pragma region WHITESPACES
                case ' ':
                    break;
                case '\t':
                    break;
                case '\r':
                    break;

                case '\n': {
                    m_currentLineNo++;
                    break;
                }
        #pragma endregion WHITESPACES
        #pragma region STRINGS
                case '"' : {
                    StartString();
                    break;
                }
        #pragma endregion STRINGS

        default: {
            // Illegal Operation
            if (IsDigit(c)) StartNumber();
            else if (IsAlpha(c)) StartIdentifier();
            else Error::Throw(m_currentLineNo, "Illegal Character",std::string(1, m_Source[m_current]));
        }
    }
}

char HedNack::Scanner::PeekAt(unsigned int forward) {
    if (m_current + (forward - 1) >= m_Source.size()) return '\0';

    return m_Source[m_current+(forward-1)];
}

void HedNack::Scanner::AddToken(TokenType tt, literalval literal) {
    std::string lexeme = m_Source.substr(m_start, m_current - m_start);
    m_Tokens.emplace_back(Token(tt, lexeme, literal, m_currentLineNo));
}

void HedNack::Scanner::StartString() {
    while (PeekAt() != '"' && !IsAtEnd()) {
        if (PeekAt() == '\n') m_currentLineNo++;
        Advance();
    }
    if (IsAtEnd()) {
        Error::Throw(m_currentLineNo, "Unterminated String");
        return;
    }
    // Close String
    Advance();

    std::string value = m_Source.substr(m_start + 1, m_current - 1 - m_start);
    AddToken(TokenType::STRING, value);
}

void HedNack::Scanner::StartNumber() {
    while (IsDigit(PeekAt())) Advance();

    if (PeekAt() == '.' && IsDigit(PeekAt(2))) {
        Advance();
        while (IsDigit(PeekAt())) Advance();
        AddToken(TokenType::DECIMAL_NUMBER, std::stod(m_Source.substr(m_start, m_current - m_start)));
        return;
    }

    AddToken(TokenType::INTEGER_NUMBER, std::stoi(m_Source.substr(m_start, m_current - m_start)));
}

void HedNack::Scanner::StartIdentifier() {
    while (IsAlpha(PeekAt()) || IsDigit(PeekAt())) Advance();

    std::string text = m_Source.substr(m_start, m_current - m_start);
    auto it = HedNack::Token::IDENTIFIER_MAP.find(text);

    AddToken(it == HedNack::Token::IDENTIFIER_MAP.end() ? TokenType::IDENTIFIER : it->second);
}

bool HedNack::Scanner::IsDigit(char c) {
    return c >= '0' && c <= '9';
}

bool HedNack::Scanner::IsAlpha(char c) {
    return  (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_');
}


