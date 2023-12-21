#ifndef __ASTNODEEXP_INC__
#define __ASTNODEEXP_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 表达式类别
    enum class ExpKind : uint32_t
    {
        Unknown, // 未知表达式

        AnnFile, //@file
        AnnFunc, //@func
        AnnLine, //@line

        Unary,   // 一元表达式
        Binary,  // 二元表达式
        Ternary, // 三元表达式

        Identity, // 标识符表达式
        FunCall,  // 函数调用表达式
        Array,    // 数组索引表达式

        Int,     // 有符号常量表达式
        Uint,    // 无符号常量表达式
        Float,   // 浮点数常量表达式
        Char,    // 字符 常量表达式
        CString, // 字符串常量表达式
        Null,    // null表达式
        Bool,    // true/false 常量表达式

        New, // new表达式

        Cast,  // 类型转换表达式
        This,  // this 表达式
        Super, // super 表达式

        Dot,   // 成员访问表达式
        Paren, // 括号表达式

        Rang,  // 范围表达式
        Block, // 块表达式

        Lambda, // 匿名表达式

    };

    struct IAstExp : public IAstNode
    {
        IAstExp(ExpKind kind) : type(nullptr), kind(kind) {}
        ISymbolType *type; // 表达式的类型

        inline ExpKind getKind() const { return kind; }

    private:
        ExpKind kind;
    };
    //@file
    struct ExpAnnFile : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpAnnFile() : IAstExp(ExpKind::AnnFile) {}
        std::string file;
    };
    //@func
    struct ExpAnnFunc : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpAnnFunc() : IAstExp(ExpKind::AnnFunc) {}
        std::string func;
    };
    //@line
    struct ExpAnnLine : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpAnnLine() : IAstExp(ExpKind::AnnLine), line(0) {}
        uint32_t line;
    };
    // bool 常量表达式
    struct ExpBool : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpBool(bool val) : IAstExp(ExpKind::Bool), value(val) {}
        bool value;
    };
    // null 常量表达式
    struct ExpNull : public IAstExp
    {
        ExpNull() : IAstExp(ExpKind::Null) {}
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // sint 常量表达式
    struct ExpSInt : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpSInt(int64_t val) : IAstExp(ExpKind::Int), value(val) {}
        int64_t value;
    };
    // uint 常量表达式
    struct ExpUInt : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpUInt(uint64_t val) : IAstExp(ExpKind::Uint), value(val) {}
        uint64_t value;
    };
    // flt32 常量表达式
    struct ExpFlt32 : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpFlt32(flt32_t val) : IAstExp(ExpKind::Float), value(val) {}
        flt32_t value;
    };
    // flt64 常量表达式
    struct ExpFlt64 : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpFlt64(flt64_t val) : IAstExp(ExpKind::Float), value(val) {}
        flt64_t value;
    };
    // 字符 常量表达式
    struct ExpChar : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpChar(uint32_t val) : IAstExp(ExpKind::Char), value(val) {}
        uint32_t value;
    };
    // 字符串 常量表达式
    struct ExpString : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpString(const std::string &val) : IAstExp(ExpKind::CString), value(val) {}
        std::string value;
    };
    // this 表达式
    struct ExpThis : public IAstExp
    {
        ExpThis() : IAstExp(ExpKind::This) {}
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // super 表达式
    struct ExpSuper : public IAstExp
    {
        ExpSuper() : IAstExp(ExpKind::Super) {}
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 标识符 表达式
    struct ExpID : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpID(StringRef &name) : IAstExp(ExpKind::Identity), name(name) {}
        StringRef name;
    };
    // 函数调用 表达式
    struct ExpFuncCall : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpFuncCall(StringRef &name) : IAstExp(ExpKind::FunCall), name(name) {}
        StringRef name;
        std::list<AstExpRef> args; // 函数参数
    };
    // 数组索引 表达式
    struct ExpArrayIndex : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpArrayIndex(StringRef &name) : IAstExp(ExpKind::Array), name(name) {}
        StringRef name;
        std::list<AstExpRef> indexs; // 数组索引
    };
    // 成员调用 表达式
    struct ExpMemberCall : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpMemberCall() : IAstExp(ExpKind::Dot) {}
        std::list<AstExpRef> items;
    };
    // 一元 表达式
    struct ExpUnary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpUnary(AstExpRef exp, TkOpEnum op, bool preop)
            : IAstExp(ExpKind::Unary), exp(exp), op(op), preop(preop) {}
        AstExpRef exp;
        TkOpEnum op; // 操作符
        bool preop;  // 前置一元操作符
    };
    // 二元 表达式
    struct ExpBinary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        ExpBinary(AstExpRef left, AstExpRef right, TkOpEnum op)
            : IAstExp(ExpKind::Binary), left(left), right(right), op(op) {}
        AstExpRef left;
        AstExpRef right;
        TkOpEnum op; // 操作符
    };
    // 三元 表达式
    struct ExpTernary : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpTernary(AstExpRef cond) : IAstExp(ExpKind::Ternary), cond(cond) {}
        AstExpRef cond;    // 条件表达式
        AstExpRef result;  // 分支结果1
        AstExpRef result2; // 分支结果2
    };
    // 括号 表达式
    struct ExpParen : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpParen(AstExpRef exp)
            : IAstExp(ExpKind::Paren), exp(exp) {}
        AstExpRef exp;
    };
    // new 表达式
    struct ExpNew : public IAstExp
    {
        ExpNew() : IAstExp(ExpKind::New) {}
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // cast 表达式
    struct ExpCast : public IAstExp
    {
        ExpCast() : IAstExp(ExpKind::Cast) {}
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 范围 表达式
    struct ExpRang : public IAstExp
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        ExpRang(AstExpRef left, AstExpRef right,
                bool loc, bool roc, bool neg)
            : IAstExp(ExpKind::Rang), left(left), right(right),
              loc(loc), roc(roc), neg(neg) {}

        AstExpRef left;
        AstExpRef right;
        bool loc; // 左开？左闭？
        bool roc; // 右开？右闭？
        bool neg; // 不在范围内
    };
    // 块 表达式
    struct ExpBlock : public IAstExp
    {
        ExpBlock() : IAstExp(ExpKind::Block) {}
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
}

#endif // __ASTNODEEXP_INC__