#include <iostream>

#include "Error.h"
#include "RunCode.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: hednack [filename]";
        return ERROR_ARGUMENT_LENGTH;
    }
    else if (argc == 2) {
        return HedNack::RunSource(argv[1]);
    } else {
        HedNack::RunPrompt();
    }

    return EXIT_SUCCESS;
}
