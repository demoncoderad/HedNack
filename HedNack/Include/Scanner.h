//
// Created by minley on 10/02/22.
//

#ifndef HEDNACK_SCANNER_H
#define HEDNACK_SCANNER_H


#include <vector>
#include "Token.h"
#include "Error.h"

namespace HedNack {
    class Scanner {
    private:
        std::string m_Source;
        std::vector<Token> m_Tokens;

        // Indexes for scanning
        int m_start = 0, m_current = 0, m_currentLineNo = 1;

        // Helper Functions
        inline bool IsAtEnd();
        void ScanToken();

        inline bool IsDigit(char c);
        inline bool IsAlpha(char c);

        inline char Advance();
        void AddToken(TokenType tt, literalval literal = nullptr);
        inline char PeekAt(unsigned int forward = 1);

        // Lexemes
        void StartString();
        void StartNumber();
        void StartIdentifier();
    public:
        explicit Scanner(std::string& source) : m_Source(source) {}

        std::vector<Token>& ScanTokens();

    };
}


#endif //HEDNACK_SCANNER_H
