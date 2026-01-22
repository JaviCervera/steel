#pragma once

#include <stdlib.h>
#include "common.h"
#include "swan/console.hh"

void Error(const char* message);


inline void ErrorEx(const std::string& message, const std::string& file, int line) {
    Error((file + "(" + swan::strmanip::fromint(line) + "): " + message).c_str());
}
