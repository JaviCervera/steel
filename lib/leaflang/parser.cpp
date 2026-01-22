#include "error.h"
#include "parser.h"

using namespace std;

Parser::Parser(const vector<Token>& tokens) : stream(tokens), currentFunc(NULL) {
}

void Parser::Parse() {
    ScanFunctions();
    vector<string> functions;
    vector<string> program;
    while (stream.HasNext()) {
        const Token& token = stream.Peek();
        if (token.type == TOK_FUNCTION) {
            functions.push_back(ParseFunctionDef());
        } else {
            program.push_back(ParseStatement(0));
        }
    }
    code = generator.GenProgram(functions, program, definitions);
}

void Parser::ParseLibrary(const vector<Token>& tokens) {
    TokenStream prevStream = stream;
    stream = TokenStream(tokens);
    while (stream.HasNext()) {
        const Token& token = stream.Peek();
        if (token.type == TOK_FUNCTION) {
            const Function func = ScanFunctionHeader();
            ParseStatementEnd();
            definitions.ClearLocals();
            lib.push_back(func);
        } else {
            ErrorEx("Library can only contain function headers", token.file, token.line);
        }
    }
    stream = prevStream;
}

void Parser::ScanFunctions() {
    TokenStream prevStream = stream;
    stream = TokenStream(*prevStream.tokens);
    while (stream.HasNext()) {
        const Token& token = stream.Peek();
        if (token.type == TOK_FUNCTION) {
            const Function func = ScanFunctionHeader();
            definitions.AddFunction(func);
            SkipFunction();
            definitions.ClearLocals();
        } else {
            stream.Skip(1);
        }
    }
    stream = prevStream;
}

Function Parser::ScanFunctionHeader() {
    stream.Skip(1); // function
    const string name = ScanFunctionName();
    const int returnType = ParseReturnType();
    const vector<Var> params = ParseParams();
    return Function(name, returnType, params);
}

const string& Parser::ScanFunctionName() {
    const Token& nameToken = stream.Next();
    if (nameToken.type != TOK_ID) {
        ErrorEx("Expected identifier, got '" + nameToken.data + "'", nameToken.file, nameToken.line);
    } else if (FindLibFunction(lib, nameToken.data) != -1) {
        ErrorEx("Identifier already used as library function: " + nameToken.data, nameToken.file, nameToken.line);
    } else if (definitions.FindFunction(nameToken.data) != NULL) {
        ErrorEx("Identifier already used as function: " + nameToken.data, nameToken.file, nameToken.line);
    }
    return nameToken.data;
}

void Parser::SkipFunction() {
    int block = 1;
    while (block > 0 && stream.HasNext()) {
        const Token& token = stream.Next();
        switch (token.type) {
            case TOK_FUNCTION:
            case TOK_IF:
            case TOK_FOR:
            case TOK_WHILE:
                ++block;
                break;
            case TOK_END:
                --block;
                break;
        }
    }
}

string Parser::ParseFunctionDef() {
    const Function func = ParseFunctionHeader();
    currentFunc = definitions.FindFunction(func.name);
    const string block = ParseBlock(1);
    ParseEnd(0);
    const string code = generator.GenFunctionDef(func, block, definitions);
    definitions.ClearLocals();
    currentFunc = NULL;
    return code;
}

Function Parser::ParseFunctionHeader() {
    stream.Skip(1); // function
    const string name = ParseFunctionName();
    const int returnType = ParseReturnType();
    const vector<Var> params = ParseParams();
    return Function(name, returnType, params);
}

const string& Parser::ParseFunctionName() {
    const Token& nameToken = stream.Next();
    if (nameToken.type != TOK_ID) {
        ErrorEx("Expected identifier, got '" + nameToken.data + "'", nameToken.file, nameToken.line);
    } else if (definitions.FindVar(nameToken.data) != NULL) {
        ErrorEx("Identifier already used for variable: " + nameToken.data, nameToken.file, nameToken.line);
    }
    return nameToken.data;
}

vector<Var> Parser::ParseParams() {
    vector<Var> params;
    ParseOpenParen();
    while (stream.Peek().type == TOK_ID) {
        const string name = ParseVarName();
        const int type = ParseParamType();
        Var param(name, type);
        definitions.AddLocal(param);
        params.push_back(param);
        if (stream.Peek().type == TOK_COMMA) stream.Skip(1);
    }
    ParseCloseParen();
    return params;
}

const string& Parser::ParseVarName() {
    const Token& nameToken = stream.Next();
    if (nameToken.type != TOK_ID) {
        ErrorEx("Expected identifier, got '" + nameToken.data + "'", nameToken.file, nameToken.line);
    } else if (FindLibFunction(lib, nameToken.data) != -1) {
        ErrorEx("Identifier already used as library function: " + nameToken.data, nameToken.file, nameToken.line);
    } else if (definitions.FindFunction(nameToken.data) != NULL) {
        ErrorEx("Identifier already used as function: " + nameToken.data, nameToken.file, nameToken.line);
    } else if (definitions.FindVar(nameToken.data) != NULL) {
        ErrorEx("Identifier already used for variable: " + nameToken.data, nameToken.file, nameToken.line);
    }
    return nameToken.data;
}

void Parser::ParseOpenParen() {
    const Token& token = stream.Next();
    if (token.type != TOK_OPENPAREN) {
        ErrorEx("Expected '(', got '" + token.data + "'", token.file, token.line);
    }
}

int Parser::ParseParamType() {
    if (IsType(stream.Peek().type)) {
        return GetType(stream.Next().type);
    } else {
        ErrorEx("Expected parameter type", stream.Peek().file, stream.Peek().line);
        return TYPE_VOID;
    }
}

void Parser::ParseCloseParen() {
    const Token& token = stream.Next();
    if (token.type != TOK_CLOSEPAREN) {
        ErrorEx("Expected ')', got '" + token.data + "'", token.file, token.line);
    }
}

int Parser::ParseReturnType() {
    if (IsType(stream.Peek().type)) {
        return GetType(stream.Next().type);
    } else {
        return TYPE_VOID;
    }
}

string Parser::ParseBlock(int indent) {
    string block;
    while (stream.Peek().type != TOK_EOF && stream.Peek().type != TOK_ELSEIF
            && stream.Peek().type != TOK_ELSE && stream.Peek().type != TOK_END) {
        block += ParseStatement(indent);
    }
    return block;
}

string Parser::ParseStatement(int indent) {
    if (IsAssignment()) {
        const string assignment = generator.GenIndent(indent) + generator.GenStatement(ParseAssignment());
        ParseStatementEnd();
        return assignment;
    } else if (IsControl(stream.Peek().type)) {
        return ParseControlStatement(indent);
    } else {
        const Expression exp = ParseExp();
        ParseStatementEnd();
        return generator.GenIndent(indent) + generator.GenStatement(exp.code);
    }
}

bool Parser::IsAssignment() const {
    const Token& idToken = stream.Peek();
    const Token& assignToken = stream.Peek(OffsetAfterIndexing(1));
    return idToken.type == TOK_ID && assignToken.type == TOK_ASSIGN;
}

int Parser::OffsetAfterIndexing(int offset) const {
    while (stream.Peek(offset).type == TOK_OPENBRACKET) {
        ++offset;
        while (stream.HasNext() && stream.Peek(offset).type != TOK_CLOSEBRACKET) {
            ++offset;
        }
        ++offset;
    }
    return offset;
}

string Parser::ParseAssignment() {
    const Token& nameToken = stream.Peek();
    const string varName = CheckId(nameToken);
    if (definitions.FindFunction(varName) || FindLibFunction(lib, varName) != -1) {
        ErrorEx("Cannot assign to a function", nameToken.file, nameToken.line);
    }
    const Var* var = definitions.FindVar(varName);
    if (var == NULL) return ParseVarDef();
    stream.Skip(1); // name
    if (stream.Peek().type == TOK_OPENBRACKET) {
        if (var->type == TYPE_LIST) {
            return ParseListAccess(generator.GenVar(*var), true).code;
        } else if (var->type == TYPE_DICT) {
            return ParseDictAccess(generator.GenVar(*var), true).code;
        } else {
            ErrorEx("Only lists and dicts can be indexed", nameToken.file, nameToken.line);
            return "";
        }
    } else {
        stream.Skip(1); // =
        const Token token = stream.Peek();
        const Expression exp = ParseExp();
        CheckTypes(var->type, exp.type, token);
        return generator.GenAssignment(*var, exp.type, exp.code);
    }
}

const string& Parser::CheckId(const Token& token) const {
    if (token.type != TOK_ID) {
        ErrorEx("Expected identifier, got '" + token.data + "'", token.file, token.line);
    }
    return token.data;
} 

void Parser::CheckTypes(int expected, int got, const Token& token) {
    if (!AreCompatible(expected, got)) {
        ErrorEx("Incompatible types", token.file, token.line);
    }
}

void Parser::ParseStatementEnd() {
    const bool hasEol = stream.SkipEols();
    if (!hasEol) {
        const Token& token = stream.Peek();
        if (token.type != TOK_SEMICOLON && token.type != TOK_END
                && token.type != TOK_ELSEIF && token.type != TOK_ELSE) {
            ErrorEx("Expected ';' or new line, got '" + token.data + "'", token.file, token.line);
        }
        if (token.type == TOK_SEMICOLON) stream.Skip(1);
    }
}

std::string Parser::ParseControlStatement(int indent) {
    switch (stream.Peek().type) {
    case TOK_IF:
        return ParseIf(indent);
        break;
    case TOK_FOR:
        return ParseFor(indent);
        break;
    case TOK_WHILE:
        return ParseWhile(indent);
        break;
    case TOK_RETURN:
        return ParseReturn(indent);
    }
    return "";
}

string Parser::ParseIf(int indent) {
    stream.Skip(1); // if
    const Expression exp = ParseExp();
    CheckThen();
    const string block = ParseBlock(indent + 1);
    string elseifs;
    while (stream.Peek().type == TOK_ELSEIF) {
        elseifs += ParseElseIf(indent);
    }
    string else_;
    if (stream.Peek().type == TOK_ELSE) {
        else_ = ParseElse(indent);
    }
    const string end = ParseEnd(indent);
    return generator.GenIndent(indent) + generator.GenIf(exp.code, block, elseifs, else_, end);
}

void Parser::CheckThen() {
    const Token& token = stream.Next();
    if (token.type != TOK_THEN) {
        ErrorEx("Expected 'then', got '" + token.data + "'", token.file, token.line);
    }
}

string Parser::ParseElseIf(int indent) {
    stream.Skip(1); //elseif
    const Expression exp = ParseExp();
    CheckThen();
    const string block = ParseBlock(indent + 1);
    return generator.GenIndent(indent) + generator.GenElseIf(exp.code, block);
}

string Parser::ParseElse(int indent) {
    stream.Skip(1); //else
    const string block = ParseBlock(indent + 1);
    return generator.GenIndent(indent) + generator.GenElse(block);
}

string Parser::ParseEnd(int indent) {
    const Token& token = stream.Next();
    if (token.type != TOK_END) {
        ErrorEx("Expected 'end', got '" + token.data + "'", token.file, token.line);
    }
    return generator.GenIndent(indent) + generator.GenEnd();
}

string Parser::ParseFor(int indent) {
    stream.Skip(1); // for
    const Token& varToken = stream.Peek();
    const string assignment = ParseAssignment();
    const Var& var = *definitions.FindVar(varToken.data);
    const Expression to = ParseTo();
    CheckTypes(var.type, to.type, varToken);
    const Expression step = ParseStep();
    CheckTypes(var.type, step.type, varToken);
    CheckDo();
    const string block = ParseBlock(indent + 1);
    const string end = ParseEnd(indent);
    return generator.GenIndent(indent) + generator.GenFor(var, assignment, to.code, step.code, block, end);
}

Expression Parser::ParseTo() {
    const Token& token = stream.Next();
    if (token.type != TOK_TO) {
        ErrorEx("Expected 'to', got '" + token.data + "'", token.file, token.line);
    }
    return ParseExp();
}

Expression Parser::ParseStep() {
    if (stream.Peek().type == TOK_STEP) {
        stream.Skip(1); // step
        return ParseExp();
    } else {
        return Expression(TYPE_INT, "1");
    }
}

void Parser::CheckDo() {
    const Token& token = stream.Next();
    if (token.type != TOK_DO) {
        ErrorEx("Expected 'do', got '" + token.data + "'", token.file, token.line);
    }
}

string Parser::ParseWhile(int indent) {
    stream.Skip(1); // while
    const Expression exp = ParseExp();
    CheckDo();
    const string block = ParseBlock(indent + 1);
    const string end = ParseEnd(indent);
    return generator.GenIndent(indent) + generator.GenWhile(exp.code, block, end);
}

string Parser::ParseReturn(int indent) {
    const Token& returnToken = stream.Next();
    if (currentFunc == NULL) {
        ErrorEx("Cannot use return statement outside a function",
            returnToken.file, returnToken.line);
    }
    Expression exp(TOK_EOF, "");
    if (stream.Peek().type != TOK_SEMICOLON) {
        if (currentFunc->type == TYPE_VOID) {
            ErrorEx("Function cannot return a value", returnToken.file, returnToken.line);
        }
        exp = ParseExp();
        CheckTypes(currentFunc->type, exp.type, returnToken);
    } else if (currentFunc->type != TYPE_VOID) {
        ErrorEx("Function must return a value", returnToken.file, returnToken.line);
    }
    ParseStatementEnd();
    return generator.GenIndent(indent) + generator.GenReturn(currentFunc, exp.code, definitions);
}

string Parser::ParseVarDef() {
    const string name = ParseVarName();
    const Token& assignToken = stream.Next();
    if (assignToken.type != TOK_ASSIGN) {
        ErrorEx("Variables must be initialized", assignToken.file, assignToken.line);
    }
    const Expression exp = ParseExp();
    const VarDef def(Var(name, exp.type), exp);
    if (currentFunc == NULL) {
        definitions.AddGlobal(def.var);
    } else {
        definitions.AddLocal(def.var);
    }
    return generator.GenVarDef(def.var, def.initExp.type, def.initExp.code, currentFunc == NULL);
}

Expression Parser::ParseExp() {
    return ParseOrExp();
}

Expression Parser::ParseOrExp() {
    Expression exp = ParseAndExp();
    while (stream.Peek().type == TOK_OR) {
        const Token& token = stream.Next();
        const Expression exp2 = ParseAndExp();
        if (!AreCompatible(exp.type, exp2.type)) {
            ErrorEx("Boolean operands must be of compatible types", token.file, token.line);
        }
        const int balancedTypes = BalanceTypes(exp.type, exp2.type);
        exp = Expression(balancedTypes, generator.GenBinaryExp(balancedTypes, token, exp.code, exp2.code));      
    }
    return exp;
}

Expression Parser::ParseAndExp() {
    Expression exp = ParseEqualExp();
    while (stream.Peek().type == TOK_AND) {
        const Token& token = stream.Next();
        const Expression exp2 = ParseEqualExp();
        if (!AreCompatible(exp.type, exp2.type)) {
            ErrorEx("Boolean operands must be of compatible types", token.file, token.line);
        }
        const int balancedTypes = BalanceTypes(exp.type, exp2.type);
        exp = Expression(balancedTypes, generator.GenBinaryExp(balancedTypes, token, exp.code, exp2.code));
    }
    return exp;
}

Expression Parser::ParseEqualExp() {
    Expression exp = ParseRelExp();
    while (stream.Peek().type == TOK_EQUAL || stream.Peek().type == TOK_NOTEQUAL) {
        const Token& token = stream.Next();
        const Expression exp2 = ParseRelExp();
        CheckTypes(exp.type, exp2.type, token);
        const int expType = BalanceTypes(exp.type, exp2.type);
        exp = Expression(TYPE_INT, generator.GenBinaryExp(expType, token, exp.code, exp2.code));
    }
    return exp;
}

Expression Parser::ParseRelExp() {
    Expression exp = ParseAddExp();
    while (stream.Peek().type == TOK_LESSER || stream.Peek().type == TOK_LEQUAL
            || stream.Peek().type == TOK_GREATER || stream.Peek().type == TOK_GEQUAL) {
        const Token& token = stream.Next();
        if (exp.type != TYPE_INT && exp.type != TYPE_FLOAT && exp.type != TYPE_STRING) {
            ErrorEx("Relational operators can only be applied to numeric and string types",
                token.file, token.line);
        }
        const Expression exp2 = ParseAddExp();
        CheckTypes(exp.type, exp2.type, token);
        const int expType = BalanceTypes(exp.type, exp2.type);
        exp = Expression(TYPE_INT, generator.GenBinaryExp(expType, token, exp.code, exp2.code));
    }
    return exp;
}

Expression Parser::ParseAddExp() {
    Expression exp = ParseMulExp();
    while (stream.Peek().type == TOK_PLUS || stream.Peek().type == TOK_MINUS) {
        const Token& token = stream.Next();
        if (token.type == TOK_PLUS && exp.type != TYPE_INT && exp.type != TYPE_FLOAT && exp.type != TYPE_STRING) {
            ErrorEx("Addition can only be applied to numeric and string types", token.file, token.line);
        } else if (token.type == TOK_MINUS && exp.type != TYPE_INT && exp.type != TYPE_FLOAT) {
            ErrorEx("Subtraction can only be applied to numeric types", token.file, token.line);
        }
        const Expression exp2 = ParseMulExp();
        CheckTypes(exp.type, exp2.type, token);
        const int expType = BalanceTypes(exp.type, exp2.type);
        exp = Expression(expType, generator.GenBinaryExp(expType, token, exp.code, exp2.code));
    }
    return exp;
}

Expression Parser::ParseMulExp() {
    Expression exp = ParseListExp();
    while (stream.Peek().type == TOK_MUL || stream.Peek().type == TOK_DIV
            || stream.Peek().type == TOK_MOD) {
        const Token& token = stream.Next();
        if (exp.type != TYPE_INT && exp.type != TYPE_FLOAT) {
            ErrorEx("Multiplication and division can only be applied to numeric types",
                token.file, token.line);
        }
        const Expression exp2 = ParseListExp();
        CheckTypes(exp.type, exp2.type, token);
        const int expType = BalanceTypes(exp.type, exp2.type);
        exp = Expression(expType, generator.GenBinaryExp(expType, token, exp.code, exp2.code));
    }
    return exp;
}

Expression Parser::ParseListExp() {
    if (stream.Peek().type == TOK_OPENBRACKET) {
        vector<Expression> values;
        stream.Skip(1); // [
        if (stream.Peek().type != TOK_CLOSEBRACKET) {
            values.push_back(ParseExp());
            while (stream.Peek().type == TOK_COMMA) {
                stream.Skip(1); // ,
                values.push_back(ParseExp());
            }
        }
        const Token& closeToken = stream.Next();
        if (closeToken.type != TOK_CLOSEBRACKET) {
            ErrorEx("Expected ']', got '" + closeToken.data + "'", closeToken.file, closeToken.line);
        }
        return Expression(TYPE_LIST, generator.GenList(values));
    } else {
        return ParseDictExp();
    }
}

Expression Parser::ParseDictExp() {
    if (stream.Peek().type == TOK_OPENBRACE) {
        vector<Expression> keys;
        vector<Expression> values;
        stream.Skip(1); // {
        if (stream.Peek().type != TOK_CLOSEBRACE) {
            ParseDictEntry(keys, values);
            while (stream.Peek().type == TOK_COMMA) {
                stream.Skip(1); // ,
                ParseDictEntry(keys, values);
            }
        }
        const Token& closeToken = stream.Next();
        if (closeToken.type != TOK_CLOSEBRACE) {
            ErrorEx("Expected '}', got '" + closeToken.data + "'", closeToken.file, closeToken.line);
        }
        return Expression(TYPE_DICT, generator.GenDict(keys, values));
    } else {
        return ParseNotExp();
    }
}

void Parser::ParseDictEntry(vector<Expression>& keys, vector<Expression>& values) {
    const Token& keyToken = stream.Peek();
    const Expression keyExp = ParseExp();
    if (keyExp.type != TYPE_STRING) {
        ErrorEx("Expected string expression as key.", keyToken.file, keyToken.line);
    }
    const Token& colonToken = stream.Next();
    if (colonToken.type != TOK_COLON) {
        ErrorEx("Expected ':', got '" + colonToken.data + "'", colonToken.file, colonToken.line);
    }
    const Expression valueExp = ParseExp();
    keys.push_back(keyExp);
    values.push_back(valueExp);
}

Expression Parser::ParseNotExp() {
    const bool isNot = stream.Peek().type == TOK_NOT;
    if (isNot) stream.Skip(1);
    const Expression exp = ParseCastExp();
    return isNot ? Expression(TYPE_INT, generator.GenNotExp(exp.code)) : exp;
}

Expression Parser::ParseCastExp() {
    const Expression exp = ParseNegExp();
    if (IsType(stream.Peek().type)) {
        const Token& typeToken = stream.Next();
        const int tokenType = GetType(typeToken.type);
        if (exp.type < TYPE_LIST || exp.type > 0) {
            ErrorEx("Can only cast numeric, string, list and dict types", typeToken.file, typeToken.line);
        }
        if (tokenType < TYPE_STRING || tokenType > 0) {
            ErrorEx("Can only cast to numeric and string types", typeToken.file, typeToken.line);
        }
        return Expression(tokenType, generator.GenCastExp(tokenType, exp.type, exp.code));
    } else {
        return exp;
    }
}

Expression Parser::ParseNegExp() {
    const Token* token = (stream.Peek().type == TOK_NOT || stream.Peek().type == TOK_MINUS)
        ? &stream.Next()
        : NULL;
    const Expression exp = ParseGroupExp();
    if (token != NULL && exp.type != TYPE_INT && exp.type != TYPE_FLOAT) {
        ErrorEx("Unary '-' operator must be applied to numeric types", token->file, token->line);
    }
    return (token != NULL) ? Expression(exp.type, generator.GenNegExp(exp.code)) : exp;
}

Expression Parser::ParseGroupExp() {
    if (stream.Peek().type == TOK_OPENPAREN) {
        stream.Skip(1); // (
        const Expression exp = ParseExp();
        ParseCloseParen();
        return Expression(exp.type, generator.GenGroupExp(exp.code));
    } else {
        return ParseAtomicExp();
    }
}

Expression Parser::ParseAtomicExp() {
    const Token& token = stream.Next();
    switch (token.type) {
    case TOK_INTLITERAL:
        return Expression(TYPE_INT, generator.GenLiteral(token));
    case TOK_FLOATLITERAL:
        return Expression(TYPE_FLOAT, generator.GenLiteral(token));
    case TOK_STRINGLITERAL:
        return Expression(TYPE_STRING, generator.GenLiteral(token));
    case TOK_NULLLITERAL:
        return Expression(TYPE_RAW, generator.GenLiteral(token));
    case TOK_TRUELITERAL:
    case TOK_FALSELITERAL:
        return Expression(TYPE_INT, generator.GenLiteral(token));
    case TOK_ID:
        return (stream.Peek().type == TOK_OPENPAREN)
            ? ParseFunctionCall(token)
            : ParseVarAccess(token);
    default:
        ErrorEx("Unexpected element '" + token.data + "'", token.file, token.line);
    }
    return Expression(TYPE_VOID, "");
}

Expression Parser::ParseFunctionCall(const Token& nameToken) {
    const size_t index = FindLibFunction(lib, nameToken.data);
    const Function* func = (index != -1)
        ? &lib[index]
        : definitions.FindFunction(nameToken.data);
    if (func == NULL) {
        ErrorEx("Unknown function", nameToken.file, nameToken.line);
    }
    const Expression args = ParseArgs(func);
    return Expression(func->type, generator.GenFunctionCall(*func, args.code));
}

Expression Parser::ParseArgs(const Function* func) {
    vector<Expression> args;
    ParseOpenParen();
    if (stream.Peek().type != TOK_CLOSEPAREN) {
        args.push_back(ParseArg(func->params[args.size()].type, stream.Peek()));
        while (stream.Peek().type == TOK_COMMA) {
            stream.Skip(1); // ,
            if (args.size() < func->params.size()) {
                args.push_back(ParseArg(func->params[args.size()].type, stream.Peek()));
            } else {
                ErrorEx("Too many arguments", stream.Peek().file, stream.Peek().line);
            }
        }
    }
    if (args.size() < func->params.size()) {
        ErrorEx("Not enough arguments", stream.Peek().file, stream.Peek().line);
    }
    ParseCloseParen();
    return Expression(TYPE_VOID, generator.GenArgs(*func, args));
}

Expression Parser::ParseArg(int paramType, const Token& token) {
    const Expression exp = ParseExp();
    CheckTypes(exp.type, paramType, token);
    return exp;
}

Expression Parser::ParseVarAccess(const Token& nameToken) {
    const Var* var = definitions.FindVar(nameToken.data);
    if (var != NULL) {
        const Expression& exp = Expression(var->type, generator.GenVar(*var));
        const Token& nextToken = stream.Peek();
        if (nextToken.type == TOK_OPENBRACKET) {
            if (var->type == TYPE_LIST) {
                return ParseListAccess(exp.code, false);
            } else if (var->type == TYPE_DICT) {
                return ParseDictAccess(exp.code, false);
            } else {
                ErrorEx("Only lists and dicts can be indexed", nameToken.file, nameToken.line);
                return Expression(TYPE_VOID, "");
            }
        } else {
            return exp;
        }
    } else {
        if (definitions.FindFunction(nameToken.data) != NULL) {
            ErrorEx("Expected '(' in function call", nameToken.file, nameToken.line);
        } else {
            ErrorEx("Variable has not been initialized: " + nameToken.data, nameToken.file, nameToken.line);
        }
        return Expression(TYPE_VOID, "");
    }
}

Expression Parser::ParseListAccess(string listCode, bool isSetter) {
    Expression indexExp(TYPE_VOID, "");
    while (stream.Peek().type == TOK_OPENBRACKET) {
        stream.Skip(1); // [
        const Token& expToken = stream.Peek();
        indexExp = ParseExp();
        if (indexExp.type != TYPE_INT) {
            ErrorEx("Only int expressions can be used as list indices", expToken.file, expToken.line);
        }
        const Token& closeToken = stream.Next();
        if (closeToken.type != TOK_CLOSEBRACKET) {
            ErrorEx("Expected ']', got '" + closeToken.data + "'", closeToken.file, closeToken.line);
        }
        if (stream.Peek().type == TOK_OPENBRACKET) {
            listCode = generator.GenListGetter(TYPE_LIST, listCode, indexExp.code);
        }
    }
    if (isSetter) {
        stream.Skip(1); // =
        const Expression exp = ParseExp();
        return Expression(exp.type, generator.GenListSetter(listCode, indexExp.code, exp));
    } else {
        const Token& typeToken = stream.Next();
        if (!IsType(typeToken.type)) {
            ErrorEx("Expected type suffix at end of dict indexing", typeToken.file, typeToken.line);
        }
        const int type = GetType(typeToken.type);
        return Expression(type, generator.GenListGetter(type, listCode, indexExp.code));
    }
}

Expression Parser::ParseDictAccess(string dictCode, bool isSetter) {
    Expression indexExp(TYPE_VOID, "");
    while (stream.Peek().type == TOK_OPENBRACKET) {
        stream.Skip(1); // [
        const Token& expToken = stream.Peek();
        indexExp = ParseExp();
        if (indexExp.type != TYPE_STRING) {
            ErrorEx("Only string expressions can be used as dict indices", expToken.file, expToken.line);
        }
        const Token& closeToken = stream.Next();
        if (closeToken.type != TOK_CLOSEBRACKET) {
            ErrorEx("Expected ']', got '" + closeToken.data + "'", closeToken.file, closeToken.line);
        }
        if (stream.Peek().type == TOK_OPENBRACKET) {
            dictCode = generator.GenDictGetter(TYPE_DICT, dictCode, indexExp.code);
        }
    }
    if (isSetter) {
        stream.Skip(1); // =
        const Expression exp = ParseExp();
        return Expression(exp.type, generator.GenDictSetter(dictCode, indexExp.code, exp));
    } else {
        const Token& typeToken = stream.Next();
        if (!IsType(typeToken.type)) {
            ErrorEx("Expected type suffix at end of dict indexing", typeToken.file, typeToken.line);
        }
        const int type = GetType(typeToken.type);
        return Expression(type, generator.GenDictGetter(type, dictCode, indexExp.code));
    }
}

const Lib& Parser::GetLib() const {
    return lib;
}

const string& Parser::GetCode() const {
    return code;
}
