#ifndef __ASTNODEEXP_INC__
#define __ASTNODEEXP_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstExp : public IAstNode
    {
        IAstExp() : type(nullptr) {}
        ISymbolType *type; // 表达式的类型
    };
    // bool 常量表达式
    struct ExpBool : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpBool(bool val) : value(val) {}
        bool value;
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
        ExpSInt(int64_t val) : value(val) {}
        int64_t value;
    };
    // uint 常量表达式
    struct ExpUInt : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpUInt(uint64_t val) : value(val) {}
        uint64_t value;
    };
    // flt32 常量表达式
    struct ExpFlt32 : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpFlt32(flt32_t val) : value(val) {}
        flt32_t value;
    };
    // flt64 常量表达式
    struct ExpFlt64 : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpFlt64(flt64_t val) : value(val) {}
        flt64_t value;
    };
    // 字符 常量表达式
    struct ExpChar : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpChar(uint32_t val) : value(val) {}
        uint32_t value;
    };
    // 字符串 常量表达式
    struct ExpString : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpString(const std::string &val) : value(val) {}
        std::string value;
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
        ExpID(StringRef &name) : name(name) {}
        StringRef name;
    };
    // 函数调用 表达式
    struct ExpFuncCall : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpFuncCall(StringRef &name) : name(name) {}
        StringRef name;
        std::list<AstExpRef> arg; // 函数参数
    };
    // 成员调用 表达式
    struct ExpMemberCall : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpMemberCall() {}
        std::list<AstDeclRef> items;
    };
    // 一元 表达式
    struct ExpUnary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpUnary(AstDeclRef exp, TkOpEnum op, bool preop)
            : exp(exp), op(op), preop(preop) {}
        AstDeclRef exp;
        TkOpEnum op; // 操作符
        bool preop;  // 前置一元操作符
    };
    // 二元 表达式
    struct ExpBinary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpBinary(AstDeclRef left, AstDeclRef right, TkOpEnum op)
            : left(left), right(right), op(op) {}
        AstDeclRef left;
        AstDeclRef right;
        TkOpEnum op; // 操作符
    };
    // 三元 表达式
    struct ExpTernary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpTernary(AstDeclRef cond) : cond(cond) {}
        AstDeclRef cond;    // 条件表达式
        AstDeclRef result;  // 分支结果1
        AstDeclRef result2; // 分支结果2
    };
    // 括号 表达式
    struct ExpParen : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpParen(AstDeclRef exp)
            : exp(exp) {}
        AstDeclRef exp;
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

        ExpRang(AstDeclRef left, AstDeclRef right,
                bool loc, bool roc, bool neg)
            : left(left), right(right),
              loc(loc), roc(roc), neg(neg) {}

        AstDeclRef left;
        AstDeclRef right;
        bool loc; // 左开？左闭？
        bool roc; // 右开？右闭？
        bool neg; // 不在范围内
    };
    // 块 表达式
    struct ExpBlock : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
}

#endif // __ASTNODEEXP_INC__