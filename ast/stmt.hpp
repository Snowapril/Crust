#ifndef STMT_HPP_
#define STMT_HPP_

#include <vector>
#include <string>
#include "type.hpp"

class Node;
class SymbolTable;

class Statement {
public:
    Statement() = default;
    virtual ~Statement();
    virtual std::vector<std::string> codeGen(SymbolTable* symtab) const;
    virtual void print() const = 0;
};

class Block {
public:
    Block();
    Block(std::vector<Statement*>* stmts);
    ~Block();
    void print() const;
    std::vector<std::string> codeGen(SymbolTable* symtab) const;
private:
    std::vector<Statement*>* _statements { nullptr };
};

class VarDecStmt : public Statement {
public:
    VarDecStmt(std::string id, Node* expr);
    VarDecStmt(std::string id, Node* type, Node* expr);
    ~VarDecStmt();
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
private:
    std::string _id;
    Node* _type { nullptr };
    Node* _expr { nullptr };
};

class IfStmt : public Statement {
public:
    IfStmt(Node* cond, Block* then_block);
    IfStmt(Node* cond, Block* then_block, Block* else_block);
    ~IfStmt();
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
private:
    Node* _condition { nullptr };
    Block* _then_block { nullptr };
    Block* _else_block { nullptr };
};

class ForStmt : public Statement {
public:
    ForStmt(Node* pivot, Node* iters, Block* block);
    ~ForStmt();
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
private:
    Node* _pivot { nullptr };
    Node* _iters { nullptr };
    Block* _block { nullptr };
};

class LoopStmt : public Statement {
public:
    LoopStmt(Block* block);
    ~LoopStmt();
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
private:
    Block* _block { nullptr };
};

class BreakStmt : public Statement {
public:
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
};

class AssignStmt : public Statement {
public:
    AssignStmt(Node* id, Node* expr);
    ~AssignStmt();
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
private:
    Node* _id { nullptr };
    Node* _expr { nullptr };
};

class ReturnStmt : public Statement {
public:
    ReturnStmt(Node* expr);
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
private:
    Node* _expr { nullptr };
};

class FuncStmt : public Statement {
public:
    FuncStmt(std::string id, std::vector<Node*>* params, Block* block);
    FuncStmt(std::string id, std::vector<Node*>* params, Node* returnType, Block* block);
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    void print() const override;
    std::vector<Node*>* _params { nullptr };
    std::string _id;
    Node* _returnType { nullptr };
    Block* _body { nullptr };
};

#endif // STMT_HPP_