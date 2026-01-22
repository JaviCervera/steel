#pragma once

#include "definitions.h"
#include "expression.h"
#include "lib.h"
#include "token.h"

class Generator {
public:
    std::string GenProgram(const std::vector<std::string>& functions, const std::vector<std::string>& program, const Definitions& definitions) const;
    std::string GenFunctionDef(const Function& func, const std::string& block, const Definitions& definitions) const;
    std::string GenStatement(const std::string& exp) const;
    std::string GenIf(const std::string& exp, const std::string& block, const std::string& elseifs, const std::string& else_, const std::string& end) const;
    std::string GenElseIf(const std::string& exp, const std::string& block) const;
    std::string GenElse(const std::string& block) const;
    std::string GenEnd() const;
    std::string GenFor(const Var& controlVar, const std::string& assignment, const std::string& to, const std::string& step, const std::string& block, const std::string& end) const;
    std::string GenWhile(const std::string& exp, const std::string& block, const std::string& end) const;
    std::string GenReturn(const Function* func, const std::string& exp, const Definitions& definitions) const;
    std::string GenVarDef(const Var& var, int expType, const std::string& exp, bool isGlobal) const;
    std::string GenAssignment(const Var& var, int expType, const std::string& exp) const;
    std::string GenBinaryExp(int expType, const Token& token, const std::string& left, const std::string& right) const;
    std::string GenList(const std::vector<Expression>& values) const;
    std::string GenDict(const std::vector<Expression>& keys, const std::vector<Expression>& values) const;
    std::string GenNotExp(const std::string& exp) const;
    std::string GenCastExp(int castType, int expType, const std::string& exp) const;
    std::string GenNegExp(const std::string& exp) const;
    std::string GenGroupExp(const std::string& exp) const;
    std::string GenFunctionCall(const Function& func, const std::string& args) const;
    std::string GenArgs(const Function& func, const std::vector<Expression>& args) const;
    std::string GenVar(const Var& var) const;
    std::string GenLiteral(const Token& token) const;
    std::string GenListGetter(int type, const std::string& listCode, const std::string& indexCode) const;
    std::string GenListSetter(const std::string& listCode, const std::string& indexCode, const Expression& valueExp) const;
    std::string GenDictGetter(int type, const std::string& dictCode, const std::string& indexCode) const;
    std::string GenDictSetter(const std::string& dictCode, const std::string& indexCode, const Expression& valueExp) const;
    std::string GenIndent(int level) const;
private:
    static std::string GenFunctionHeader(const Function& func);
    static std::string GenParams(const Function& func);
    static std::string GenType(int type);
    static std::string GenFuncId(const std::string& id);
    static std::string GenVarId(const std::string& id);
    static std::string GenFunctionCleanup(const Function* func, const std::vector<Var>& varsInScope, const std::string exclude = "");
    static std::vector<Var> GetManagedVars(const std::vector<Var>& vars);
};
