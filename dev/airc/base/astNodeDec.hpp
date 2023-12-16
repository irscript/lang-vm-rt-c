#ifndef __ASTNODEDEC_INC__
#define __ASTNODEDEC_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstDecl : public IAstNode
    {
    };
    // 文件依赖声明
    struct DeclFile: public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };;
    // 变量声明
    struct DeclVar : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 函数声明
    struct DeclFunc : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 枚举声明
    struct DeclEnum : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 结构体声明
    struct DeclStruct : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 接口声明
    struct DeclInterface : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 委托声明
    struct DeclEntrust : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 类声明
    struct DeclClass : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
}
#endif // __ASTNODEDEC_INC__