//
// Created by minley on 10/02/22.
//

#ifndef HEDNACK_RUNCODE_H
#define HEDNACK_RUNCODE_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

namespace HedNack {
    void Run(std::string code);
    int RunSource (const char* location);
    void RunPrompt ();
}

#endif //HEDNACK_RUNCODE_H
