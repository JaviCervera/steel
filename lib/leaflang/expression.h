#pragma once

#include "common.h"

struct Expression {
    int type;
    std::string code;

    Expression(int type, const std::string& code) : type(type), code(code) {
    }
};
