
namespace AST{
    class Node{
    public:
        Node() {}
    };
    class Declaration: public Node{
    public:
    };
    class Block: public Declaration{
    public:
        inline void add(std::unique_ptr<Declaration> d) {}
    };
    class Expr {
    public:
        virtual ~Expr() {}
    };
    class NumberExpr : public Expr{
    public:
        NumberExpr(int val) {}
    };
    class BinaryExpr : public Expr {
    public:
        BinaryExpr(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r, int op) {}
    };
}

namespace Parser{
    std::unique_ptr<AST::Block> program;
    int cur_tok;
    int cur_scope = 0;
    int next_token() {return cur_tok = Lexer::scan_token();}
    std::unique_ptr<AST::Declaration> parse_declaration();
    std::unique_ptr<AST::Expr> parse_expression();
    std::unique_ptr<AST::Expr> parse_primary();
    std::unique_ptr<AST::NumberExpr> parse_number_expr();
    std::unique_ptr<AST::Expr> parse_paren_expr();

    void parse_statement() {
        //TODO: parse statement
    }
    void parse_program() {
        next_token();
        while (cur_tok != TOKEN_EOF) program->add(parse_declaration());
    }
    std::unique_ptr<AST::Declaration> parse_declaration() {
        if (cur_tok == TOKEN_IDENTIFIER && Lexer::token_data == "let") {
            if (next_token() != TOKEN_IDENTIFIER) {
                Lexer::report_error("expected identifier in declaration");
                return nullptr;
            }
            std::string name = Lexer::token_data;
            //TODO: add variable
            //TODO: function declaration support
            //TODO: add support: (let a;) instead of = 
            if (next_token() != '=') {
                Lexer::report_error("expected = in declaration");
                return nullptr;
            }
            next_token();
            //TODO: make declaration
            std::unique_ptr<AST::Expr> node = parse_expression();
            if (node != nullptr) printf("Parsed expression");
            return nullptr;
        }
        if (cur_tok == '{') {
            //TODO: parse block
            return nullptr;
        }
        parse_statement();
        return nullptr;
    }
    
    std::unique_ptr<AST::Expr> parse_term() {
        auto lv = parse_primary();
        while (cur_tok == '*' || cur_tok == '/') {
            const int op = cur_tok;
            next_token();
            auto rv = parse_primary();
            if (rv == nullptr) return nullptr;
            lv = std::make_unique<AST::BinaryExpr>(std::move(lv), std::move(rv), op);
        }
        return lv;
    }
    std::unique_ptr<AST::Expr> parse_expression() {
        auto lv = parse_term();
        while (cur_tok != '-' || cur_tok == '+') {
            const int op = cur_tok;
            next_token();
            auto rv = parse_term();
            if (rv == nullptr) return nullptr;
            lv = std::make_unique<AST::BinaryExpr>(std::move(lv), std::move(rv), op);
        }
        return lv;
    }
    std::unique_ptr<AST::Expr> parse_primary() {
        if (cur_tok == '(') return parse_paren_expr();
        if (cur_tok == TOKEN_INT) return parse_number_expr();
        printf("cannot parse primary expression");
        return nullptr;
    }
    std::unique_ptr<AST::Expr> parse_paren_expr() {
        next_token();
        auto res = parse_expression();
        if (cur_tok != ')') {
            Lexer::report_error(" expected ) in expression");
            return nullptr;
        }
        next_token();
        return res;
    }
    std::unique_ptr<AST::NumberExpr> parse_number_expr() {
        auto res = std::make_unique<AST::NumberExpr>(stoi(Lexer::token_data));
        next_token();
        return std::move(res);
    }
}
