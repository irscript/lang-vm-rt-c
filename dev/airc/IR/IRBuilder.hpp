#ifndef __IRBUILDER_INC__
#define __IRBUILDER_INC__

#include "IRNode.hpp"
#include "airc/base/astNode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IRBuilder
    {
        // 构建基本块
        inline IRBlock *Block(IRNodeKind kind) { return new IRBlock(kind); }
        // 构建值
        inline IRValueRef Value();

        // 构建一元表达式
        inline IRSymbolRef Unary(IRNodeKind op, IRValueRef val);
        // 构建二元表达式
        inline IRSymbolRef Binary(IRNodeKind op, IRValueRef val, IRValueRef val2);
    };
}

#endif // __IRBUILDER_INC__