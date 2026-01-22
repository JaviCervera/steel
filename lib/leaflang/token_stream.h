#pragma once

#include "token.h"

struct TokenStream {
    const std::vector<Token>* tokens;
    int offset;
    
    TokenStream(const std::vector<Token>& tokens) : tokens(&tokens), offset(0) {}
    
    bool HasNext() const {
        TokenStream copy(*tokens);
        copy.offset = offset;
        copy.SkipEols();
        return copy.offset < tokens->size();
    }

    const Token& Peek(int offset = 0) const {
        TokenStream copy(*tokens);
        copy.offset = this->offset;
        copy.Skip(offset);
        return copy.Next();
    }
    
    const Token& Next() {
        SkipEols();
        if (HasNext()) {
            offset++;
            return (*tokens)[offset-1];
        } else {
            return GetEofToken();
        }
    }

    void Skip(int count) {
        for (int i = 0; i < count; ++i) {
            Next();
        }
    }

    bool SkipEols() {
        const bool skipped = offset < tokens->size() && (*tokens)[offset].type == TOK_EOL;
        while (offset < tokens->size() && (*tokens)[offset].type == TOK_EOL)
            ++offset;
        return skipped;
    }
private:
    static Token& GetEofToken() {
        static Token eofToken(TOK_EOF, "", "", 0);
        return eofToken;
    }
};
