#include "stmt.hpp"
#include "node.hpp"
#include <iostream>

Statement::~Statement() {
    std::cout << "Statement destructor" << std::endl;
}

std::vector<std::string> Statement::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}


Block::Block()
{
    
}

Block::Block(std::vector<Statement*>* stmts)
    : _statements(stmts)
{
    
}

Block::~Block()
{
    for (auto stmt : *_statements)
    {
        delete stmt;
    }
    delete _statements;
    _statements = nullptr;
}

std::vector<std::string> Block::codeGen(SymbolTable* symtab) const
{
    std::vector<std::string> code;
    code.emplace_back("{\n");
    if (_statements)
    {
        code.reserve(_statements->size());
        for (auto stmt : *_statements)
        {
            const auto stmtCode = stmt->codeGen(symtab);
            code.insert(code.end(), stmtCode.begin(), stmtCode.end());
            code.push_back(";\n");
        }
    }
    code.emplace_back("}\n");
    return code;
}

void Block::print() const 
{
    if (_statements)
    {
        std::cout << "#statements : " << _statements->size() << std::endl;
        for (const auto& stmt : *_statements)
        {
            stmt->print();
            std::cout << "\n";
        }
    }
}

VarDecStmt::VarDecStmt(std::string id, Node* expr)
    : _id(id), _expr(expr)
{
    //! Do nothing
}

VarDecStmt::VarDecStmt(std::string id, Node* type, Node* expr)
    : _id(id), _type(type), _expr(expr)
{
    //! Do nothing
}

VarDecStmt::~VarDecStmt()
{
    if (_type) 
    {
        delete _type;
        _type = nullptr;
    }
    if (_expr) 
    {
        delete _expr;
        _expr = nullptr;
    }
}

std::vector<std::string> VarDecStmt::codeGen(SymbolTable* symtab) const
{
    std::vector<std::string> code;
    if (_type)
    {
        const auto typeCode = _type->codeGen(symtab);
        code.insert(code.end(), typeCode.begin(), typeCode.end());
    }
    code.push_back(_id);
    
    if (_expr)
    {
        code.push_back(" = ");
        const auto exprCode = _expr->codeGen(symtab);
        code.insert(code.end(), exprCode.begin(), exprCode.end());
    }
    code.push_back(";\n");
    return std::vector<std::string>();
}

void VarDecStmt::print() const 
{
    if (_type)
    {
        _type->print();
    }
    std::cout << "( " << _id << " )";
    _expr->print();
}

IfStmt::IfStmt(Node* cond, Block* then_block)
    : _condition(cond), _then_block(then_block)
{
    //! Do nothing
}

IfStmt::IfStmt(Node* cond, Block* then_block, Block* else_block)
    : _condition(cond), _then_block(then_block), _else_block(else_block)
{
    //! Do nothing
}

IfStmt::~IfStmt()
{
    if (_condition)
    {
        delete _condition;
        _condition = nullptr;
    }
    if (_then_block)
    {
        delete _then_block;
        _then_block = nullptr;
    }
    if (_else_block)
    {
        delete _else_block;
        _else_block = nullptr;
    }
}

std::vector<std::string> IfStmt::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

void IfStmt::print() const 
{
    std::cout << "if";
}

ForStmt::ForStmt(Node* pivot, Node* iters, Block* block)
    : _pivot(pivot), _iters(iters), _block(block)
{
    //! Do nothing
}

ForStmt::~ForStmt()
{
    if (_pivot)
    {
        delete _pivot;
        _pivot = nullptr;
    }
    if (_iters)
    {
        delete _iters;
        _iters = nullptr;
    }
    if (_block)
    {
        delete _block;
        _block = nullptr;
    }
}

std::vector<std::string> ForStmt::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

void ForStmt::print() const 
{
    std::cout << "for";
}

LoopStmt::LoopStmt(Block* block)
    : _block(block)
{
    //! Do nothing
}

LoopStmt::~LoopStmt()
{
    if (_block)
    {
        delete _block;
        _block = nullptr;
    }
}

std::vector<std::string> LoopStmt::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

void LoopStmt::print() const 
{
    std::cout << "loop";
}

std::vector<std::string> BreakStmt::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

void BreakStmt::print() const 
{
    std::cout << "break";
}

AssignStmt::AssignStmt(Node* id, Node* expr)
    : _id(id), _expr(expr)
{
    //! Do nothing
}

AssignStmt::~AssignStmt() 
{
    if (_id)
    {
        delete _id;
        _id = nullptr;
    }
    if (_expr)
    {
        delete _expr;
        _expr = nullptr;
    }
}

std::vector<std::string> AssignStmt::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

void AssignStmt::print() const 
{
    std::cout << "assign";
}

ReturnStmt::ReturnStmt(Node* expr)
    : _expr(expr)
{
    //! Do nothing
}

std::vector<std::string> ReturnStmt::codeGen(SymbolTable* symtab) const
{
    std::vector<std::string> code;
    code.push_back("return ");

    auto exprCode = _expr->codeGen(symtab);
    code.insert(code.end(), exprCode.begin(), exprCode.end());
    return code;
}

void ReturnStmt::print() const 
{
    std::cout << "return";
}

FuncStmt::FuncStmt(std::string id, std::vector<Node*>* params, Block* block)
: _params(params), _id(id), _returnType(new TypeNode(VarType::VOID)), _body(block)
{
    //! Do nothing
}

FuncStmt::FuncStmt(std::string id, std::vector<Node*>* params, Node* returnType, Block* block)
: _params(params), _id(id), _returnType(returnType), _body(block)
{
    //! Do nothing
}

std::vector<std::string> FuncStmt::codeGen(SymbolTable* symtab) const
{
    std::vector<std::string> code;
    
    const auto returnTypeCode = _returnType->codeGen(symtab);
    code.insert(code.end(), returnTypeCode.begin(), returnTypeCode.end());

    code.push_back(" ");
    code.push_back(_id);

    code.push_back(" (");
    for (const auto& param : *_params)
    {
        const auto paramCode = param->codeGen(symtab);
        code.insert(code.end(), paramCode.begin(), paramCode.end());
    }
    code.emplace_back(")\n");

    const auto bodyCode = _body->codeGen(symtab);
    code.insert(code.end(), bodyCode.begin(), bodyCode.end());

    return code;
}

void FuncStmt::print() const 
{
    std::cout << "fn " << _id << "(";
    for (const auto& param : *_params)
    {
        param->print();
        std::cout << ", ";
    }
    std::cout << ") -> ";
    _returnType->print();
    _body->print();
}