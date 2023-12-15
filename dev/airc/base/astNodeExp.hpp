#ifndef __ASTNODEEXP_INC__
#define __ASTNODEEXP_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstExp : public IAstNode
    {
    };
    struct ExpBool;       // bool 常量表达式
    struct ExpNull;       // null 常量表达式
    struct ExpSInt;       // sint 常量表达式
    struct ExpUInt;       // uint 常量表达式
    struct ExpFlt32;      // flt32 常量表达式
    struct ExpFlt64;      // flt64 常量表达式
    struct ExpChar;       // 字符 常量表达式
    struct ExpString;     // 字符串 常量表达式
    struct ExpThis;       // this 表达式
    struct ExpSuper;      // super 表达式
    struct ExpID;         // 标识符 表达式
    struct ExpFuncCall;   // 函数调用 表达式
    struct ExpMemberCall; // 成员调用 表达式
    struct ExpUnary;      // 一元 表达式
    struct ExpBinary;     // 二元 表达式
    struct ExpTernary;    // 三元 表达式
    struct ExpParen;      // 括号 表达式
    struct ExpNew;        // new 表达式
    struct ExpCast;       // cast 表达式
    struct ExpArrayIndex; // 数组索引 表达式
    struct ExpRang;       // 范围 表达式
    struct ExpBlock;      // 块 表达式
}

#endif // __ASTNODEEXP_INC__