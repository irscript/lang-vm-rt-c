#ifndef __IRNODE_INC__
#define __IRNODE_INC__

#include "airc/base/astNode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IIRNode;
    using IRNodeRef = std::shared_ptr<IIRNode>;

    // IR节点类型和指令
    enum class IRNodeKind : uint32_t
    {
        Unknown,
        // 基本块节点
        Block,

        // 基本块子类别
        FunctionBlock, // 函数块
        NormalBlock,   // 普通块
        LoopBlock,     // 循环块

        // IR指令节点
        Node,
        // 一元节点
        Assign, // 赋值=
        Neg,    // 符号取反 -
        Not,    // 按位取反 ~
        Abs,    // 去绝对值

        // 二元节点
        Add, // +
        Sub, // -
        Mul, // *
        Div, // /
        Mod, // %

        And, // &
        Or,  // |
        Xor, // ^

        Shl,  // >> 左移
        Lshl, // << 逻辑右移
        Ashr, // <<< 算术右移
        Rshl, // << 循环左移
        Rshr, // <<< 循环右移

        // 函数调用节点

        Max
    };

    // IR 节点访问者
    struct IIRVisit;

    // IR节点基类
    struct IIRNode
    {

        IIRNode(IRNodeKind kind) : kind(kind) {}

        std::vector<IRNodeRef> used; // 被哪些节点使用

        // 基本块？
        bool isBlock() const { return IRNodeKind::Block < kind && kind < IRNodeKind::Node; }

        // 指令？
        bool isIns() const { return IRNodeKind::Node < kind && kind < IRNodeKind::Max; }

        // 未被使用?
        bool isNotUsed() const { return kind != IRNodeKind::FunctionBlock && used.size() == 0; }

        // 节点访问
        virtual void visit(IIRVisit &vist) = 0;

        inline IRNodeKind getKind() const { return kind; }

    private:
        IRNodeKind kind; // 类别
    };
    // 符号
    struct IRSymbol
    {
        uint32_t mIsArg : 1; // 是否是参数
        AstType mType;       // 类型
        StringRef mName;     // 名称
    };
    using IRSymbolRef = std::shared_ptr<IRSymbol>;
    enum class IRValueKind
    {
        Unknown,
        Bool,
        Int32,
        Uint32,
        Int64,
        Uint64,
        Flt32,
        Flt64,
        Char,
        String,
        Symbol,
    };
    // 值
    struct IIRValue
    {
        IIRValue(IRValueKind kind) : kind(kind) {}
        inline IRValueKind getKind() const { return kind; }

    private:
        IRValueKind kind;
    };
    using IRValueRef = std::shared_ptr<IIRValue>;
    // IR块
    struct IRBlock : public IIRNode
    {
        IRBlock(IRNodeKind kind) : IIRNode(kind) {}

        inline void addNode(IRNodeRef node) { nodes.push_back(node); }

        std::list<IRNodeRef> nodes;            // 块的内部节点
        std::map<std::string, IRNodeRef> maps; // 名称到节点的映射

        virtual void visit(IIRVisit &vist) override;
    };

    // 一元
    struct IRUnary : public IIRNode
    {
        IRUnary(IRNodeKind kind, IRValueRef vaule, IRSymbol &symbol)
            : IIRNode(kind), vaule(vaule), symbol(symbol) {}

        IRValueRef vaule; // 所操作的值
        IRSymbol &symbol; // 结果符号
        virtual void visit(IIRVisit &vist) override;
    };
    // 二元
    struct IRBinary : public IIRNode
    {
        IRBinary(IRNodeKind kind, IRValueRef vaule, IRValueRef vaule2, IRSymbol &symbol)
            : IIRNode(kind), vaule(vaule), vaule2(vaule2), symbol(symbol) {}

        IRValueRef vaule;  // 所操作的值
        IRValueRef vaule2; // 所操作的值
        IRSymbol &symbol;  // 结果符号
        virtual void visit(IIRVisit &vist) override;
    };

    // IR 节点访问者
    struct IIRVisit
    {
        virtual void visit(IRBlock &block) = 0;
        virtual void visit(IRUnary &unary) = 0;
        virtual void visit(IRBinary &binary) = 0;
    };
}
#endif // __IRNODE_INC__