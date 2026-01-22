#include <map>
#include "error.h"
#include "token.h"

using namespace std;
using namespace swan;

struct Lexer {
    const std::string& buffer;
    int offset;
    const std::string& file;
    int line;
    
    Lexer(const std::string& buffer, const std::string& file)
            : buffer(buffer), offset(0), file(file), line(1) {
    }
    
    size_t BufferSize() const {
        return buffer.length();
    }
    
    char Char(size_t offset = 0) const {
        if (Valid(offset)) {
            return buffer[this->offset + offset];
        } else {
            return '\0';
        }
    }

    bool Valid(size_t offset = 0) const {
        return (this->offset + offset) < buffer.length();
    }
};

Token NextToken(Lexer& lexer);
Token SkipBlank(Lexer& lexer);
bool IsSlComment(const Lexer& lexer);
bool IsMlComment(const Lexer& lexer);
bool IsNumber(char c);
bool IsAlpha(char c);
string CheckSymbol(const Lexer& lexer);
int TokenType(const string& str);

vector<Token> ParseTokens(const string& buffer, const string& filename) {
    Lexer lexer(buffer, filename);
    vector<Token> tokens;
    while (true) {
        Token token = NextToken(lexer);
        if (token.type == TOK_EOF) {
			break;
        } else if (token.type != TOK_EOL
                || (tokens.size() > 0 && !IsStatementEnd(tokens.back().type))) {
            tokens.push_back(token);
        }
    }
    if (!IsStatementEnd(tokens.back().type)) {
        tokens.push_back(Token(TOK_EOL, "\n", lexer.file, lexer.line));
    }
    return tokens;
}

bool IsControl(int type) {
    return type == TOK_IF || type == TOK_FOR || type == TOK_WHILE || type == TOK_RETURN;
}

bool IsBooleanOp(int type) {
    return type == TOK_AND || type == TOK_OR;
}

bool IsRelationOp(int type) {
    return type >= TOK_EQUAL && type <= TOK_LEQUAL;
}

bool IsAdditiveOp(int type) {
    return type == TOK_PLUS || type == TOK_MINUS;
}

bool IsMultiplicativeOp(int type) {
    return type == TOK_MUL || type == TOK_DIV || type == TOK_MOD;
}

bool IsUnaryOp(int type) {
    return type == TOK_NOT || type == TOK_MINUS;
}

bool IsType(int type) {
    return type >= TOK_INT && type <= TOK_RAW;
}

int GetType(int type) {
    switch (type) {
    case TOK_INT:
        return TYPE_INT;
    case TOK_FLOAT:
        return TYPE_FLOAT;
    case TOK_STRING:
        return TYPE_STRING;
    case TOK_LIST:
        return TYPE_LIST;
    case TOK_DICT:
        return TYPE_DICT;
    case TOK_RAW:
        return TYPE_RAW;
    default:
        return TYPE_VOID;
    }
}

bool IsStatementEnd(int type) {
    return type == TOK_EOL || type == TOK_SEMICOLON;
}

bool AreCompatible(int type1, int type2) {
    if (type1 == type2 && type2 != TYPE_VOID) {
        return true;
    } else if (type1 == TYPE_INT && type2 == TYPE_FLOAT) {
        return true;
    } else if (type1 == TYPE_FLOAT && type2 == TYPE_INT) {
        return true;
    } else {
        return false;
    }
}

int BalanceTypes(int type1, int type2) {
    if (type1 == type2) {
        return type1;
    } else if (type1 == TYPE_INT && type2 == TYPE_FLOAT) {
        return TYPE_FLOAT;
    } else if (type1 == TYPE_FLOAT && type2 == TYPE_INT) {
        return TYPE_FLOAT;
    } else {
        return TYPE_VOID;
    }
}

Token NextToken(Lexer& lexer) {
    // Skip blank characters. If an end of line is found, return it
    const Token maybeEol = SkipBlank(lexer);
    if (maybeEol.type == TOK_EOL) return maybeEol;

    // Check end of file
    if (!lexer.Valid()) return Token(TOK_EOF, "", lexer.file, lexer.line);

    // Check numeric literal
    const bool negNumber = (lexer.Char() == '-' && IsNumber(lexer.Char(1)))
        ? true
        : false;
    if (negNumber || IsNumber(lexer.Char())) {
        string str = "";
        if (lexer.Char() == '-') {
            str = "-";
            lexer.offset++;
        }
        while (IsNumber(lexer.Char())) {
            str += lexer.Char();
            lexer.offset++;
        }
        if (lexer.Char() == '.') {
            str += '.';
            lexer.offset++;
            if (!IsNumber(lexer.Char())) ErrorEx("Invalid float number", lexer.file, lexer.line);
            while (IsNumber(lexer.Char())) {
                str += lexer.Char();
                lexer.offset++;
            }
            return Token(TOK_FLOATLITERAL, str, lexer.file, lexer.line);
        } else {
            return Token(TOK_INTLITERAL, str, lexer.file, lexer.line);
        }
    }

    // Check symbol
    string symbol = CheckSymbol(lexer);
    if (symbol != "") {
        lexer.offset += symbol.length();
        return Token(TokenType(symbol), symbol, lexer.file, lexer.line);
    }

    // Check string
    if (lexer.Char() == '"') {
        string str;
        lexer.offset++; // Skip "
        while (lexer.Valid() && lexer.Char() != '"' && lexer.Char() != '\n') {
            str += lexer.Char();
            lexer.offset++;
        }
        if (lexer.Char() != '"') ErrorEx("String must be closed", lexer.file, lexer.line);
        lexer.offset++;
        return Token(TOK_STRINGLITERAL, str, lexer.file, lexer.line);
    }

    // Check keyword, identifier or null literal
    if (IsAlpha(lexer.Char())) {
        string str = "";
        while (IsAlpha(lexer.Char()) || IsNumber(lexer.Char())) {
            str += lexer.Char();
            lexer.offset++;
        }
        return Token(TokenType(str), str, lexer.file, lexer.line);
    }

    // Not recognized
    ErrorEx("Unrecognized token", lexer.file, lexer.line);
    return Token(TOK_EOF, "", lexer.file, lexer.line);
}

Token SkipBlank(Lexer& lexer) {
    while (lexer.Char() == ' ' || lexer.Char() == '\t'
            || lexer.Char() == '\n' || IsSlComment(lexer) || IsMlComment(lexer)) {
        if (IsSlComment(lexer)) {
            while (lexer.Valid() && lexer.Char() != '\n') lexer.offset++;
        }
        if (IsMlComment(lexer)) {
            lexer.offset += 2;
            while (lexer.Valid() && (lexer.Char() != '*' || lexer.Char(1) != '/')) {
                if (lexer.Char() == '\n') lexer.line++;
                lexer.offset++;
            }
            if (lexer.Char(1) != '/') {
                ErrorEx("Comment must be closed", lexer.file, lexer.line);
            }
            lexer.offset++;
        }
        const bool isEol = lexer.Char() == '\n';
        if (isEol) lexer.line++;
        if (lexer.Valid()) lexer.offset++;
        if (isEol) return Token(TOK_EOL, "\n", lexer.file, lexer.line - 1);
    }
    return Token(TOK_EOF, "", lexer.file, lexer.line);
}

bool IsSlComment(const Lexer& lexer) {
    return lexer.Char() == '/' && lexer.Char(1) == '/';
}

bool IsMlComment(const Lexer& lexer) {
    return lexer.Char() == '/' && lexer.Char(1) == '*';
}

bool IsNumber(char c) {
    return c >= '0' && c <= '9';
}

bool IsAlpha(char c) {
    return c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

string CheckSymbol(const Lexer& lexer) {
    static vector<string> symbols;
    if (symbols.size() == 0) {
        symbols.push_back("==");
        symbols.push_back("<>");
        symbols.push_back(">=");
        symbols.push_back("<=");
        symbols.push_back("<");
        symbols.push_back(">");
        symbols.push_back("+");
        symbols.push_back("-");
        symbols.push_back("*");
        symbols.push_back("/");
        symbols.push_back("=");
        symbols.push_back(",");
        symbols.push_back(";");
        symbols.push_back("(");
        symbols.push_back(")");
        symbols.push_back("[");
        symbols.push_back("]");
        symbols.push_back("{");
        symbols.push_back("}");
        symbols.push_back(":Int");
        symbols.push_back(":Float");
        symbols.push_back(":String");
        symbols.push_back(":List");
        symbols.push_back(":Dict");
        symbols.push_back(":Raw");
        symbols.push_back(":");
    }
    for (size_t i = 0; i < symbols.size(); ++i) {
        string str = "";
        for (size_t j = 0; j < symbols[i].length(); ++j) {
            if (lexer.Valid(j)) str += lexer.Char(j);
        }
        if (str == symbols[i]) return str;
    }
    return "";
}

int TokenType(const string& str) {
    static map<string, int> types;
    if (types.size() == 0) {
        types["not"] = TOK_NOT;
        types["and"] = TOK_AND;
        types["or"] = TOK_OR;
        types["=="] = TOK_EQUAL;
        types["<>"] = TOK_NOTEQUAL;
        types[">"] = TOK_GREATER;
        types["<"] = TOK_LESSER;
        types[">="] = TOK_GEQUAL;
        types["<="] = TOK_LEQUAL;
        types["+"] = TOK_PLUS;
        types["-"] = TOK_MINUS;
        types["*"] = TOK_MUL;
        types["/"] = TOK_DIV;
        types["mod"] = TOK_MOD;
        types["="] = TOK_ASSIGN;
        types[","] = TOK_COMMA;
        types[":"] = TOK_COLON;
        types[";"] = TOK_SEMICOLON;
        types["("] = TOK_OPENPAREN;
        types[")"] = TOK_CLOSEPAREN;
        types["["] = TOK_OPENBRACKET;
        types["]"] = TOK_CLOSEBRACKET;
        types["{"] = TOK_OPENBRACE;
        types["}"] = TOK_CLOSEBRACE;
        types["end"] = TOK_END;
        types["if"] = TOK_IF;
        types["then"] = TOK_THEN;
        types["elseif"] = TOK_ELSEIF;
        types["else"] = TOK_ELSE;
        types["for"] = TOK_FOR;
        types["to"] = TOK_TO;
        types["step"] = TOK_STEP;
        types["do"] = TOK_DO;
        types["while"] = TOK_WHILE;
        types["return"] = TOK_RETURN;
        types["function"] = TOK_FUNCTION;
        types[":Int"] = TOK_INT;
        types[":Float"] = TOK_FLOAT;
        types[":String"] = TOK_STRING;
        types[":List"] = TOK_LIST;
        types[":Dict"] = TOK_DICT;
        types[":Raw"] = TOK_RAW;
        types["null"] = TOK_NULLLITERAL;
        types["true"] = TOK_TRUELITERAL;
        types["false"] = TOK_FALSELITERAL;
    }
    return (types.count(str) > 0) ? types[str] : TOK_ID;
}
