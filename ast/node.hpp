#ifndef NODE_HPP_
#define NODE_HPP_

#include "type.hpp"
#include "symtab.hpp"
#include "stmt.hpp"
#include <vector>
#include <string>

class Node {
public:
    Node() = default;
    virtual ~Node();
    virtual void addChild(Node* son);
    virtual std::vector<std::string> codeGen(SymbolTable* symtab) const;
    virtual VarType getType() const;
    virtual void print() const;
protected:
    std::vector<Node*> _sons;
};

class RichCompareNode : public Node {
public:
    RichCompareNode() = default;
    ~RichCompareNode() = default;
    void addChild(Node* son) override;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
private:
    RichCompareType _type;
};

class LogicCompareNode : public Node {
public:
    LogicCompareNode() = default;
    ~LogicCompareNode() = default;
    void addChild(Node* son) override;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
private:
    LogicCompareType _type;
};

class OpNode : public Node {
public:
    OpNode(OpType opType);
    ~OpNode() = default;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
private:
    OpType _opType;
};

class VarNode : public Node {
public:
    VarNode(std::string name);
    void addChild(Node* son) override;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
protected:
    std::string _name;
};

class LiteralNode : public Node {
public:
    LiteralNode(VarType type, int value);
    LiteralNode(VarType type, char* value);
    LiteralNode(VarType type, bool value);
    void addChild(Node* son) override;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
protected:
    VarType _type;
    union {
        int _iVal;
        char *_sVal;
        bool _bVal;
    };
};

class TypeNode : public Node {
public:
    TypeNode(VarType type);
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
private:
    VarType _type;
};

class ParamNode : public Node {
public:
    ParamNode(Node* type, std::string name);
    void addChild(Node* son) override;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
};

class FuncCallNode : public Node {
public:
    FuncCallNode(Node* id, std::vector<Node*>* args);
    void addChild(Node* son) override;
    std::vector<std::string> codeGen(SymbolTable* symtab) const override;
    VarType getType() const override;
    void print() const override;
};

#endif // _NODE_HPP_