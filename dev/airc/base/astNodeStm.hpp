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

        Exp, // 表达式语句
        Var, // 变量声明语句

        Label,    // 标签语句
        Goto,     // goto语句
        Break,    // break语句
        Continue, // continue语句
        Return,   // return语句

        Throw, // trow语句

        // 以下语句都是块语句的子类
        /*
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

        Catch,   // catch语句
        Finally, // finally语句
        */
    };

    struct IAstStm : public IAstNode
    {

        IAstStm(StmKind kind) : kind(kind) {}
        inline StmKind getKind() const { return kind; }

    private:
        StmKind kind;
    };
    // 块语句类型
    enum class BlockKind : uint32_t
    {
        Unknown, // 未知

        Function, // 函数块
        Normal,   // 普通块

        If,
        Elsif,
        Else,

        Switch,
        Case,
        Default,

        For,
        Foreach,
        While,
        DoWhile,

        Try,
        Catch,
        Finally,

    };

    // 块语句
    struct StmBlock : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        StmBlock(BlockKind block = BlockKind::Function) : IAstStm(StmKind::Block), block(block), prev(nullptr) {}

        std::list<AstStmRef> stms; // 块内的语句列表
        SymbolTable symbols;       // 局部符号表
        BlockKind block;           // 语句块类型
        StmBlock *prev;            // 前一个块
    };

    // var 语句

    struct StmVar : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmVar() : IAstStm(StmKind::Var) {}
        std::shared_ptr<DeclVar> def; // 定义
    };
    // exp 语句
    struct StmExp : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmExp() : IAstStm(StmKind::Exp) {}

        AstExpRef exp;
    };
    // 标签 语句

    struct StmLabel : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmLabel(StringRef &name) : IAstStm(StmKind::Label), label(name) {}

        StringRef label; // 标签名
    };
    // goto 语句
    struct StmGoto : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmGoto(StringRef &name) : IAstStm(StmKind::Goto), label(name) {}

        StringRef label; // 标签名
    };
    // break 语句
    struct StmBreak : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmBreak() : IAstStm(StmKind::Break) {}
    };
    // continue 语句
    struct StmContinue : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmContinue() : IAstStm(StmKind::Continue) {}
    };
    // return 语句
    struct StmReturn : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmReturn() : IAstStm(StmKind::Return) {}
    };
    // if 语句
    struct StmIf : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        StmIf() : StmBlock(BlockKind::If) {}

        AstExpRef cond; // 条件表达式
    };
    // elsif 语句
    struct StmElsif : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        StmElsif() : StmBlock(BlockKind::Elsif) {}

        AstExpRef cond; // 条件表达式
    };
    // else 语句
    struct StmElse : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmElse() : StmBlock(BlockKind::Else) {}
    };
    // switch 语句
    struct StmSwitch : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmSwitch() : StmBlock(BlockKind::Switch) {}

        AstExpRef cond; // 条件表达式
    };
    // case 语句
    struct StmCase : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmCase() : StmBlock(BlockKind::Case) {}

        AstExpRef cond; // 条件表达式
    };
    // default 语句
    struct StmDefault : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmDefault() : StmBlock(BlockKind::Default) {}
    };
    // for(;;) 语句
    struct StmFor : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmFor() : StmBlock(BlockKind::For) {}
        AstStmRef init;   // 初始语句
        AstStmRef cond;   // 条件语句
        AstStmRef finish; // 完成语句
    };
    // do{}while() 语句
    struct StmDoWhile : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmDoWhile() : StmBlock(BlockKind::DoWhile) {}

        AstExpRef cond; // 条件表达式
    };
    // while 语句
    struct StmWhile : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmWhile() : StmBlock(BlockKind::While) {}

        AstExpRef cond; // 条件表达式
    };
    // try 语句

    struct StmTry : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmTry() : StmBlock(BlockKind::Try) {}
    };
    // catch 语句
    struct StmCatch : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmCatch() : StmBlock(BlockKind::Catch) {}
    };
    // finally 语句
    struct StmFinally : public StmBlock
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmFinally() : StmBlock(BlockKind::Finally) {}
    };
    // throw 语句
    struct StmThrow : public IAstStm
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
        StmThrow() : IAstStm(StmKind::Throw) {}
    };

    // 语句
}
#endif // __ASTNODESTM_INC__