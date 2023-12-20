#ifndef __ASTNODEDEC_INC__
#define __ASTNODEDEC_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstDecl : public IAstNode
    {
        IAstDecl(StringRef &name) : name(name) {}
        StringRef name; // 声明名称
    };

    struct FileUnit; // 文件单元
    // 文件依赖声明
    struct DeclFile : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        DeclFile(StringRef &name, StringRef file)
            : IAstDecl(name), file(file), unit(nullptr) {}
        StringRef file; // 声明名称
        FileUnit *unit; // 对应的文件单元
    };
    // 文件符号
    struct FileSymbol : public IFileSymbol
    {
        FileSymbol(DeclFile &decl) : IFileSymbol(decl.name), decl(decl) {}
        DeclFile &decl; // 对应的声明
    };
    // 变量声明
    struct DeclVar : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        AstFlag flag;   // 变量标志
        AstType type;   // 变量类型
        AstExpRef init; // 变量初始化表达式
    };
    // 变量符号
    struct VarSymbol : public IVarSymbol
    {
        VarSymbol(DeclVar &decl) : IVarSymbol(decl.name), decl(decl) {}
        DeclVar &decl;
    };
    // 函数声明
    struct DeclFunc : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    // 函数符号
    struct FuncSymbol : public IFuncSymbol
    {
        FuncSymbol(DeclFunc &decl)
            : IFuncSymbol(decl.name, decl.name), decl(decl) {}
        DeclFunc &decl;
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