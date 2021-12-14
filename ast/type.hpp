#ifndef TYPE_HPP_
#define TYPE_HPP_

#include <string>

enum class NodeType : unsigned char {
    VAR,
    RICH_COMPARE,
    LOGIC_COMPARE,
    ARITHMETIC,
};

enum class VarType : unsigned char {
    INT,
    CHAR,
    BOOL,
    FLOAT,
    VOID,
    INVALID,
};

std::string to_string(VarType type);

enum class RichCompareType : unsigned char {
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    INVALID,
};

enum class LogicCompareType : unsigned char {
    AND,
    OR,
    INVALID,
};

enum class OpType : unsigned char {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NEG,
    POS,
    INVALID,
};

std::string to_string(OpType type);

#endif  // _TYPE_HPP_