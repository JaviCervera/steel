#pragma once

#include "definitions.h"
#include "expression.h"
#include "generator.h"
#include "lib.h"
#include "token.h"
#include "token_stream.h"
#include "var_def.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    void Parse();
    void ParseLibrary(const std::vector<Token>& tokens);
    const Lib& GetLib() const;
    const std::string& GetCode() const;
private:
    Lib lib;
    Generator generator;
    Definitions definitions;
    TokenStream stream;
    std::string code;
    const Function* currentFunc;
    
    void ScanFunctions();
    Function ScanFunctionHeader();
    const std::string& ScanFunctionName();
    void SkipFunction();
    std::string ParseFunctionDef();
    Function ParseFunctionHeader();
    const std::string& ParseFunctionName();
    std::vector<Var> ParseParams();
    const std::string& ParseVarName();
    void ParseOpenParen();
    int ParseParamType();
    void ParseCloseParen();
    int ParseReturnType();
    std::string ParseBlock(int indent);
    std::string ParseStatement(int indent);
    bool IsAssignment() const;
    int OffsetAfterIndexing(int offset) const;
    std::string ParseAssignment();
    const std::string& CheckId(const Token& token) const;
    void CheckTypes(int expected, int got, const Token& token);
    void ParseStatementEnd();
    std::string ParseControlStatement(int indent);
    std::string ParseIf(int indent);
    void CheckThen();
    std::string ParseElseIf(int indent);
    std::string ParseElse(int indent);
    std::string ParseEnd(int indent);
    std::string ParseFor(int indent);
    Expression ParseTo();
    Expression ParseStep();
    void CheckDo();
    std::string ParseWhile(int indent);
    std::string ParseReturn(int indent);
    std::string ParseVarDef();
    Expression ParseExp();
    Expression ParseOrExp();
    Expression ParseAndExp();
    Expression ParseEqualExp();
    Expression ParseRelExp();
    Expression ParseAddExp();
    Expression ParseMulExp();
    Expression ParseListExp();
    Expression ParseDictExp();
    void ParseDictEntry(std::vector<Expression>& keys, std::vector<Expression>& values);
    Expression ParseNotExp();
    Expression ParseCastExp();
    Expression ParseNegExp();
    Expression ParseGroupExp();
    Expression ParseAtomicExp();
    Expression ParseFunctionCall(const Token& nameToken);
    Expression ParseArgs(const Function* func);
    Expression ParseArg(int paramType, const Token& token);
    Expression ParseVarAccess(const Token& nameToken);
    Expression ParseListAccess(std::string listCode, bool isSetter);
    Expression ParseDictAccess(std::string dictCode, bool isSetter);
};
