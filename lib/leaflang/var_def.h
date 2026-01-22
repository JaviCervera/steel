#pragma once

#include "common.h"
#include "expression.h"
#include "lib.h"

struct VarDef {
    Var var;
    Expression initExp;

    VarDef(const Var& var, const Expression& initExp) : var(var), initExp(initExp) {
    }
};
