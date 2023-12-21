#ifndef __ASTNODESTM_INC__
#define __ASTNODESTM_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 语句类别
    enum class StmKind : uint32_t
    {
        Unknown, // 未知语句
        Block,   // 块语句

        If,    // if语句
        Else,  // else语句
        Elsif, // elsif语句

        Switch,  // switch语句
        Case,    // case语句
        Default, // default语句

        For,     // for语句
        Foreach, // foreach语句
        While,   // while语句
        DoWhile, // do{}while语句

        Try,     // try语句
        Trow,    // trow语句
        Catch,   // catch语句
        Finally, // finally语句

        Label,    // 标签语句
        Goto,     // goto语句
        Break,    // break语句
        Continue, // continue语句
        Return,   // return语句

        Exp, // 表达式语句
        Var, // 变量声明语句

    };

    struct IAstStm : public IAstNode
    {
    };
    // 块语句
    struct StmBlock : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // if 语句
    struct StmIf : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // elsif 语句
    struct StmElsif : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // else 语句
    struct StmElse : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // switch 语句
    struct StmSwitch : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // case 语句
    struct StmCase : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // default 语句
    struct StmDefault : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // for(;;) 语句
    struct StmFor : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // do{}while() 语句
    struct StmDoWhile : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // while 语句
    struct StmWhile : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // try 语句

    struct StmTry : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // catch 语句
    struct StmCatch : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // finally 语句
    struct StmFinally : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // throw 语句
    struct StmThrow : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 标签 语句

    struct StmLable : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // goto 语句
    struct StmGoto : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // break 语句
    struct StmBreak : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // continue 语句
    struct StmContinue : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // return 语句
    struct StmReturn : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // var 语句

    struct StmVar : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // exp 语句
    struct StmExp : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 语句
}
#endif // __ASTNODESTM_INC__