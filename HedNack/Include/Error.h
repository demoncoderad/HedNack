//
// Created by minley on 11/02/22.
//

#ifndef HEDNACK_ERROR_H
#define HEDNACK_ERROR_H

#include <iostream>

#define GENERAL_ERROR 1
#define ERROR_ARGUMENT_LENGTH 2
#define ERROR_PROGRAM_ERROR 3

namespace HedNack {
    class Error {
    private:
        static bool HadError;
    public:
        inline static void SetError(bool x) { HadError = x; }
        inline static bool GetError()       { return HadError; }
        static void Throw(int line, std::string message, std::string where = "") {
            HadError = true;
            std::cerr << "Error at Line[" << line << "] at (" << where << "). WHY ->\n\t" << message << std::endl;
        }
    };

}

#endif //HEDNACK_ERROR_H
