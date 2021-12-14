#include "type.hpp"

std::string to_string(VarType type)
{
    switch (type)
    {
        case VarType::INT:
            return "int";
        case VarType::FLOAT:
            return "float";
        case VarType::BOOL:
            return "bool";
        case VarType::VOID:
            return "void";
        default:
            return "invalid";
    }
}

std::string to_string(OpType type)
{
    switch (type)
    {
        case OpType::ADD:
            return "+";
        case OpType::SUB:
            return "-";
        case OpType::MUL:
            return "*";
        case OpType::DIV:
            return "/";
        case OpType::MOD:
            return "%";
        case OpType::POS:
            return "+";
        case OpType::NEG:
            return "-";
        default:
            return "invalid";
    }
}
