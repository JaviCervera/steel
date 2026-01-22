#pragma once

#include "common.h"

// End of file
#define TOK_EOF 0

// Literals
#define TOK_INTLITERAL 1
#define TOK_FLOATLITERAL 2
#define TOK_STRINGLITERAL 3
#define TOK_NULLLITERAL 4
#define TOK_TRUELITERAL 5
#define TOK_FALSELITERAL 6

// Operators
#define TOK_NOT 10
#define TOK_AND 11
#define TOK_OR 12
#define TOK_EQUAL 13
#define TOK_NOTEQUAL 14
#define TOK_GREATER 15
#define TOK_LESSER 16
#define TOK_GEQUAL 17
#define TOK_LEQUAL 18
#define TOK_PLUS 19
#define TOK_MINUS 20
#define TOK_MUL 21
#define TOK_DIV 22
#define TOK_MOD 23
#define TOK_ASSIGN 24

// Separators
#define TOK_COMMA 30
#define TOK_COLON 31
#define TOK_SEMICOLON 32
#define TOK_OPENPAREN 33
#define TOK_CLOSEPAREN 34
#define TOK_OPENBRACKET 35
#define TOK_CLOSEBRACKET 36
#define TOK_OPENBRACE 37
#define TOK_CLOSEBRACE 38
#define TOK_EOL 39

// Control statements
#define TOK_IF 40
#define TOK_THEN 41
#define TOK_ELSEIF 42
#define TOK_ELSE 43
#define TOK_FOR 44
#define TOK_TO 45
#define TOK_STEP 46
#define TOK_DO 47
#define TOK_WHILE 48
#define TOK_RETURN 49
#define TOK_FUNCTION 50
#define TOK_END 51

// Identifiers
#define TOK_ID 55

// Type tags
#define TOK_INT 60
#define TOK_FLOAT 61
#define TOK_STRING 62
#define TOK_LIST 63
#define TOK_DICT 64
#define TOK_RAW 65

struct Token {
    const int type;
    const std::string data;
    const std::string file;
    const int line;

    Token(int type, const std::string& data, const std::string& file, int line) :
            type(type), data(data), file(file), line(line) {
    }
    
    // Copy constructor and assignment operator are required by some old compilers
    Token(const Token& other) :
            type(other.type), data(other.data), file(other.file), line(other.line) {
    }
    
    Token& operator=(const Token& other) {
        const_cast<int&>(type) = other.type;
        const_cast<std::string&>(data) = other.data;
        const_cast<std::string&>(file) = other.file;
        const_cast<int&>(line) = other.line;
        return *this;
    }

    bool operator==(const Token& other) const {
        return type == other.type
            && data == other.data
            && file == other.file
            && line == other.line;
    }
};

std::vector<Token> ParseTokens(const std::string& buffer, const std::string& filename);
bool IsControl(int type);
bool IsBooleanOp(int type);
bool IsRelationOp(int type);
bool IsAdditiveOp(int type);
bool IsMultiplicativeOp(int type);
bool IsUnaryOp(int type);
bool IsType(int type);
int GetType(int type);
bool IsStatementEnd(int type);
bool AreCompatible(int type1, int type2);
int BalanceTypes(int type1, int type2);
