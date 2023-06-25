#include "common.h"
#include "lexer.h"
#include "vm.h"

namespace Parser{
    class Expr {
    public:
        virtual ~Expr() {}
        virtual void print() {std::cout << "(expr)";}
    };
    class NumberExpr : public Expr{
    public:
        int number = 0;
        NumberExpr(int val): number(val) {}
        void print() override {std::cout << number;}
    };
    class BinaryExpr : public Expr {
    public:
        std::unique_ptr<Expr> lhs, rhs;
        int op;
        BinaryExpr(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r, int o):lhs(std::move(l)), rhs(std::move(r)), op(o) {}
        void print() override {
            std::cout << "binary(l : ";
            lhs->print();
            std::cout << " r: ";
            rhs->print();
            std::cout << " " << char(op) << ")";
        }
    };
    int cur_tok;
    int next_token() {return cur_tok = Lexer::scan_token();}
    std::unique_ptr<Expr> parse_number_expr();
    std::unique_ptr<Expr> parse_paren_expr();
    std::unique_ptr<Expr> parse_primary();
    std::unique_ptr<Expr> parse_expression();
    std::unique_ptr<Expr> parse_term();
    std::unique_ptr<Expr> parse_factor();
    void parse_declaration();
    void parse_program() {
        next_token();
        while (cur_tok != TOKEN_EOF) parse_declaration();
    }
    void parse_declaration() {
        if (cur_tok == TOKEN_LET) {
            next_token();
            if (cur_tok != TOKEN_IDENTIFIER) throw 0;
            std::string name = Lexer::token_data;
            next_token();
            next_token();
            auto e = parse_expression();
            if (e == nullptr) return;
            std::cout << char(cur_tok) << std::endl;
            if (cur_tok == ';') std::cout << "Parsed succesfully\n";
            e->print();
            return;
        }
    }
    std::unique_ptr<Expr> parse_term() {
        auto lhs = parse_primary();
        if (lhs == nullptr) return nullptr;
        while (cur_tok == '*' || cur_tok == '/') {
            const int op = cur_tok;
            next_token();
            auto rhs = parse_primary();
            if (rhs == nullptr) return nullptr;
            lhs = std::make_unique<BinaryExpr>(std::move(lhs), std::move(rhs), op);
        }
        return lhs;
    }
    std::unique_ptr<Expr> parse_expression() {
        auto lhs = parse_term();
        if (lhs == nullptr) return nullptr;
        while (cur_tok == '+' || cur_tok == '-') {
            const int op = cur_tok;
            next_token();
            auto rhs = parse_term();
            if (rhs == nullptr) return nullptr;
            lhs = std::make_unique<BinaryExpr>(std::move(lhs), std::move(rhs), op);
        }
        return lhs;
    }
    std::unique_ptr<Expr> parse_paren_expr() {
        next_token();
        auto res = parse_expression();
        if (cur_tok != ')') {
            Lexer::report_error("expected ) in expression");
            return nullptr;
        }
        next_token();
        return res;
    }
    std::unique_ptr<Expr> parse_primary() {
        if (cur_tok == TOKEN_INT) return parse_number_expr();
        if (cur_tok == '(') return parse_paren_expr();
        Lexer::report_error(" expected ; or expression");
        return nullptr;
    }
    std::unique_ptr<Expr> parse_number_expr() {
        auto res = std::make_unique<NumberExpr>(stoi(Lexer::token_data));
        next_token();
        return res;
    }
}


void compile() {
    std::string data = "let a = 2 + 3 * 4;";
    const int al = data.size();
    const int bl = data.size()/2;
    for (int i = 0; i < bl; ++i) std::swap(data[i], data[al - 1- i]);
    Lexer::token_stream = data;
    Parser::parse_program();
}
int main(int argc, char** argv) {
    compile();   
    return 0;
}

/*
program: declaration* EOF
declaration: 
    var_decl
    | func_decl
    | block
    | statement

block: { declaration* }
statement: 
    ..
*/