#ifndef __ASTNODEDEC_INC__
#define __ASTNODEDEC_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstDecl : public IAstNode
    {
    };
    struct DeclFile;      // 文件依赖声明
    struct DeclVar;       // 变量声明
    struct DeclFunc;      // 函数声明
    struct DeclEnum;      // 枚举声明
    struct DeclStruct;    // 结构体声明
    struct DeclInterface; // 接口声明
    struct DeclEntrust;   // 委托声明
    struct DeclClass;     // 类声明
}
#endif // __ASTNODEDEC_INC__