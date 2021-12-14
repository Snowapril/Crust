#include "node.hpp"
#include "symtab.hpp"
#include <iostream>

Node::~Node()
{
    for (auto son : _sons)
    {
        if (son != nullptr)
        {
            delete son;
        }
    }

    _sons.clear();
}
void Node::addChild(Node* son)
{
    _sons.emplace_back(son);
}

std::vector<std::string> Node::codeGen(SymbolTable* symtab) const 
{
    return std::vector<std::string>();
}

VarType Node::getType() const 
{
    return VarType::INVALID;
}

void Node::print() const 
{
    std::cout << "Node";
}

void RichCompareNode::print() const 
{
    std::cout << "RichCompareNode";
}

void LogicCompareNode::print() const 
{
    std::cout << "LogicCompareNode";
}

OpNode::OpNode(OpType opType)
: _opType(opType)
{
    //! Do nothing
}

std::vector<std::string> OpNode::codeGen(SymbolTable* symtab) const
{
    std::vector<std::string> code;

    std::string opCode = to_string(_opType);
    if ((_opType == OpType::NEG) || (_opType == OpType::POS))
    {
        auto exprCode = _sons[0]->codeGen(symtab);
        code.insert(code.end(), exprCode.begin(), exprCode.end());
        code.push_back(opCode + ";");
    }
    else if ((_opType == OpType::ADD) || (_opType == OpType::SUB) || (_opType == OpType::DIV) || (_opType == OpType::MUL) || (_opType == OpType::MOD))
    {
        auto lhsCode = _sons[0]->codeGen(symtab);
        code.insert(code.end(), lhsCode.begin(), lhsCode.end());
        code.push_back(" " + opCode + " ");
        auto rhsCode = _sons[1]->codeGen(symtab);
        code.insert(code.end(), rhsCode.begin(), rhsCode.end());
        code.push_back(";");
    }

    return code;
}

VarType OpNode::getType() const
{

}

void OpNode::print() const 
{
    std::cout << "OpNode";
}

VarNode::VarNode(std::string name)
    : _name(name)
{
    //! Do nothing
}

void VarNode::print() const 
{
    std::cout << "VarNode";
}

void VarNode::addChild(Node* son)
{

}

std::vector<std::string> VarNode::codeGen(SymbolTable* symtab) const
{
    std::vector<std::string> code;
    auto typeCode = symtab->getTypeCode(_name);
    return std::vector<std::string>();
}

VarType VarNode::getType() const
{

}

LiteralNode::LiteralNode(VarType type, int value)
    : _type(type), _iVal(value)
{
    //! Do nothing
}

LiteralNode::LiteralNode(VarType type, char* value)
    : _type(type), _sVal(value)
{
    //! Do nothing
}

LiteralNode::LiteralNode(VarType type, bool value)
    : _type(type), _bVal(value)
{
    //! Do nothing
}

void LiteralNode::addChild(Node* son)
{

}

VarType LiteralNode::getType() const
{

}

std::vector<std::string> LiteralNode::codeGen(SymbolTable* symtab) const
{
    switch (_type) 
    {
        case VarType::INT:
            return std::vector<std::string>{std::to_string(_iVal)};
        case VarType::CHAR:
            return std::vector<std::string>{_sVal};
        case VarType::BOOL:
            return std::vector<std::string>{_bVal ? "true" : "false"};
        default:
            return std::vector<std::string>{"invalid"};
    }
}

void LiteralNode::print() const
{

}

void TypeNode::print() const 
{
    std::cout << "TypeNode";
}

TypeNode::TypeNode(VarType type)
    : _type(type)
{
    //! Do nothing
}

std::vector<std::string> TypeNode::codeGen(SymbolTable* symtab) const
{
    return { to_string(_type) };
}

VarType TypeNode::getType() const
{
    return _type;
}

ParamNode::ParamNode(Node* type, std::string name)
{

}

void ParamNode::addChild(Node* son)
{

}

std::vector<std::string> ParamNode::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

VarType ParamNode::getType() const
{

}

void ParamNode::print() const 
{
    std::cout << "ParamNode";
}

FuncCallNode::FuncCallNode(Node* id, std::vector<Node*>* args)
{

}

void FuncCallNode::addChild(Node* son)
{

}

std::vector<std::string> FuncCallNode::codeGen(SymbolTable* symtab) const
{
    return std::vector<std::string>();
}

VarType FuncCallNode::getType() const
{

}

void FuncCallNode::print() const 
{
    std::cout << "FuncCallNode";
}