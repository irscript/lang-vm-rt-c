#ifndef __ASTNODEEXP_INC__
#define __ASTNODEEXP_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstExp : public IAstNode
    {
    };
    // bool 常量表达式
    struct ExpBool : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // null 常量表达式
    struct ExpNull : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // sint 常量表达式
    struct ExpSInt : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // uint 常量表达式
    struct ExpUInt : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // flt32 常量表达式
    struct ExpFlt32 : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // flt64 常量表达式
    struct ExpFlt64 : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 字符 常量表达式
    struct ExpChar : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 字符串 常量表达式
    struct ExpString : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // this 表达式
    struct ExpThis : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // super 表达式
    struct ExpSuper : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 标识符 表达式
    struct ExpID : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 函数调用 表达式
    struct ExpFuncCall : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 成员调用 表达式
    struct ExpMemberCall : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 一元 表达式
    struct ExpUnary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 二元 表达式
    struct ExpBinary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 三元 表达式
    struct ExpTernary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 括号 表达式
    struct ExpParen : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // new 表达式
    struct ExpNew : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // cast 表达式
    struct ExpCast : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 数组索引 表达式
    struct ExpArrayIndex : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 范围 表达式
    struct ExpRang : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 块 表达式
    struct ExpBlock : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
}

#endif // __ASTNODEEXP_INC__