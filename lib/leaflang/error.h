#pragma once

#include <stdlib.h>
#include "common.h"
#include "swan/console.hh"

inline void Error(const std::string& message) {
    swan::console::println(message);
    exit(-1);
}


inline void ErrorEx(const std::string& message, const std::string& file, int line) {
    Error(file + "(" + swan::strmanip::fromint(line) + "): " + message);
}
