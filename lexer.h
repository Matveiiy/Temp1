#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
#include "common.h"
enum {
    TOKEN_EOF = -1, 
    TOKEN_IDENTIFIER,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_LET,
};
namespace Lexer{
    inline void report_error(const char* text) {
        printf("error: %s\n", text);
    }
    inline const char* token_to_str(int token, std::string& data) {
        if (token == TOKEN_EOF) return "EOF";
        if (token == TOKEN_INT) return data.c_str();
        if (token == TOKEN_FLOAT) return data.c_str();
        if (token == TOKEN_IDENTIFIER) return data.c_str();
        data[0] = char(token);
        return data.c_str();
    }
    std::string token_stream;
    std::string token_data = "";
    int cur_char = ' ';
    int cur_line = 0;

    inline int _scan_char()  {if (token_stream.empty()) return EOF; cur_char = token_stream.back(); token_stream.pop_back(); return cur_char;}
    inline int scan_token() {
        while (isspace(cur_char)) {
            if (cur_char == '\n') cur_line++;
            _scan_char();
        }
        while (cur_char == '/') {
            if (_scan_char() != '/') return '/';
            while (_scan_char() != '\n');
            _scan_char(); 
        }
        if (isdigit(cur_char)) {
            token_data = "";
            do {
                token_data += cur_char;
            }
            while (isdigit(_scan_char()));
            return TOKEN_INT;
        }
        if (isalpha(cur_char)) {
            token_data = "";
            do {
                token_data += cur_char;
            }
            while (isalnum(_scan_char()));
            if (token_data == "let") return TOKEN_LET;
            return TOKEN_IDENTIFIER; 
        }
        if (cur_char == EOF) return EOF;
        const int temp = cur_char;
        _scan_char();
        return temp;
    }
}

#endif