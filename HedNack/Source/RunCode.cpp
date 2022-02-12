//
// Created by minley on 10/02/22.
//

#include "RunCode.h"
#include "Scanner.h"
#include "Error.h"

namespace HedNack {

    int RunSource (const char* location) {
        // String holding the file contents
        std::string source;

        // Loading file into memory
        std::ifstream inputSrc;
        inputSrc.open(location);

        if (inputSrc.fail()) {
            std::cerr << "Error opening file at ( " << location << " ): Error Code (" << errno << ")" << std::endl;
        }

        std::stringstream ss;
        ss << inputSrc.rdbuf();
        source = ss.str();

        Run(source);
        if (Error::GetError()) { return ERROR_PROGRAM_ERROR; }

        return 0;
    }

    void RunPrompt () {
        // Loop till user enters `exit()`
        while (true) {
            std::string source;
            std::cout << ">>> ";
            getline(std::cin, source);

            if (source == "exit()") break;

            Run(source);
            Error::SetError(false);
        }

    }

    void Run (std::string code) {

        Scanner scanner(code);
        auto tokens = scanner.ScanTokens();

        for (auto token : tokens) {
            std::cout << token << std::endl;
        }
    }
}

