#ifndef SYM_TAB_HPP_
#define SYM_TAB_HPP_

#include <string>
#include <unordered_map>
#include "type.hpp"

class Node;
class FuncStmt;

struct Symbol {
    std::string id;
    VarType type;
    Node* value;
};

class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();
    VarType getTypeCode(std::string name) const;
    void addNode(std::string name, VarType type, Node* value);
    void addFunction(std::string name, FuncStmt* func);
    std::unordered_map<std::string, Symbol*> _nodeTable;
    std::unordered_map<std::string, FuncStmt*> _funcTable;
};

#endif // SYM_TAB_HPP_