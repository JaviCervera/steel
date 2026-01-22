#pragma once

#include "common.h"

struct Var {
    const std::string name;
    const int type;

    Var(const std::string& name, int type) : name(name), type(type) {
    }
    
    // Copy constructor and assignment operator are required by some old compilers
    Var(const Var& other) : name(other.name), type(other.type) {
    }
    
    Var& operator=(const Var& other) {
        const_cast<std::string&>(name) = other.name;
        const_cast<int&>(type) = other.type;
        return *this;
    }
};

struct Function {
    const std::string name;
    const int type;
    const std::vector<Var> params;

    Function(const std::string& name, int type, const std::vector<Var>& params) :
            name(name), type(type), params(params) {
    }

    Function(const std::string& name, int type, const std::vector<int>& params) :
            name(name), type(type), params(ParseParams(params)) {
    }
    
    // Copy constructor and assignment operator are required by some old compilers
    Function(const Function& other) :
            name(other.name), type(other.type), params(other.params) {
    }
    
    Function& operator=(const Function& other) {
        const_cast<std::string&>(name) = other.name;
        const_cast<int&>(type) = other.type;
        const_cast<std::vector<Var>&>(params) = other.params;
        return *this;
    }
private:
    std::vector<Var> ParseParams(const std::vector<int>& iparams) {
        std::vector<Var> out;
        for (size_t i = 0; i < iparams.size(); ++i)
            out.push_back(Var("", iparams[i]));
        return out;
    }
};

typedef std::vector<Function> Lib;

size_t FindLibFunction(const Lib& lib, const std::string& name);
