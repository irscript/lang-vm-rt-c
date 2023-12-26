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
        inline IRBlock *IRBlock(IRNodeKind kind) { return new IRBlock(kind); }
    };
}

#endif // __IRBUILDER_INC__