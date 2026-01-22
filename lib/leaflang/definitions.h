#pragma once

#include "lib.h"
#include "token_stream.h"

class Definitions {
public:
    void AddFunction(const Function& func);
    void AddGlobal(const Var& global);
    void AddLocal(const Var& local);
    void ClearLocals();
    const Function* FindFunction(const std::string& name) const;
    size_t NumFunctions() const;
    const Function* GetFunction(size_t index) const;
    const Var* FindVar(const std::string& name) const;
    const bool IsGlobal(const std::string& name) const;
    const std::vector<Var>& GetGlobals() const;
    const std::vector<Var>& GetLocals() const;
private:
    std::vector<Function> functions;
    std::vector<Var> globals;
    std::vector<Var> locals;
    
    const Var* FindLocal(const std::string& name) const;
    const Var* FindGlobal(const std::string& name) const;
};
