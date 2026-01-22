#include "definitions.h"

using namespace std;
using namespace swan;

void Definitions::AddFunction(const Function& func) {
    functions.push_back(func);
}

void Definitions::AddGlobal(const Var& global) {
    globals.push_back(global);
}

void Definitions::AddLocal(const Var& local) {
    locals.push_back(local);
}

void Definitions::ClearLocals() {
    locals.clear();
}

const Function* Definitions::FindFunction(const string& name) const {
    for (size_t i = 0; i < functions.size(); ++i) {
        if (functions[i].name == name) {
            return &functions[i];
        }
    }
    return NULL;
}

size_t Definitions::NumFunctions() const {
    return functions.size();
}

const Function* Definitions::GetFunction(size_t index) const {
    if (index >= 0 && index < NumFunctions()) {
        return &functions[index];
    } else {
        return NULL;
    }
}

const Var* Definitions::FindVar(const string& name) const {
    const Var* local = FindLocal(name);
    return (local != NULL)
        ? local
        : FindGlobal(name);
}

const bool Definitions::IsGlobal(const string& name) const {
    return FindGlobal(name) != NULL;
}

const vector<Var>& Definitions::GetGlobals() const {
    return globals;
}

const vector<Var>& Definitions::GetLocals() const {
    return locals;
}

const Var* Definitions::FindLocal(const string& name) const {
    for (size_t i = 0; i < locals.size(); ++i) {
        if (locals[i].name == name) {
            return &locals[i];
        }
    }
    return NULL;
}

const Var* Definitions::FindGlobal(const string& name) const {
    for (size_t i = 0; i < globals.size(); ++i) {
        if (globals[i].name == name) {
            return &globals[i];
        }
    }
    return NULL;
}
