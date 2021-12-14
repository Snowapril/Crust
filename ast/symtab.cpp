#include "symtab.hpp"
#include "node.hpp"

SymbolTable::SymbolTable()
{
    
}

SymbolTable::~SymbolTable()
{
    
}

VarType SymbolTable::getTypeCode(std::string name) const
{
    return _nodeTable.find(name) != _nodeTable.end() ? _nodeTable.at(name)->type : VarType::INVALID;
}

void SymbolTable::addNode(std::string name, VarType type, Node* value)
{

}

void SymbolTable::addFunction(std::string name, FuncStmt* func)
{
    _funcTable.emplace(name, func);
}
