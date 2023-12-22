#ifndef __ASTNODEDEC_INC__
#define __ASTNODEDEC_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 声明类别
    enum class DeclKind : uint32_t
    {
        Unknown,   // 未知声明
        File,      // 文件声明
        Var,       // 变量声明
        Func,      // 函数声明
        Enum,      // 枚举声明
        Struct,    // 结构体声明
        Union,     // 联合体声明
        Class,     // 类声明
        Interface, // 接口声明
        Entrust,   // 函数指针声明

    };

    struct IAstDecl : public IAstNode
    {
        IAstDecl(StringRef &name, DeclKind kind) : name(name), kind(kind) {}

        inline DeclKind getKind() const { return kind; }

        StringRef name;             // 声明名称
        std::vector<AstAnnRef> anns; // 注解列表
    private:
        DeclKind kind;
    };

    struct FileUnit; // 文件单元
    // 文件依赖声明
    struct DeclFile : public IAstDecl
    {
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

        DeclFile(StringRef &name, StringRef file)
            : IAstDecl(name, DeclKind::File), file(file), unit(nullptr) {}
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

        AstFlag flag;                   // 变量标志
        AstType type;                   // 变量类型
        std::list<AstExpRef> arrcols;   // 静态数组维度表达式
        std::vector<uintptr_t> arrcolv; // 静态数组维度表达式计算后的值
        AstExpRef init;                 // 变量初始化表达式

        DeclVar(StringRef &name) : IAstDecl(name, DeclKind::Var) {}
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
        AstFlag flag;                // 函数标志
        AstType retType;             // 函数返回类型
        std::vector<AstDeclRef> args; // 函数参数
        AstStmRef body;              // 函数体

        DeclFunc(StringRef &name) : IAstDecl(name, DeclKind::Func) {}

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

        StringRef base;                // 基础类型
        std::vector<AstDeclRef> items; // 枚举定义列表

        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;
    };
    struct EnumType : public ISymbolType
    {
        DeclEnum &decl;

        // EnumType(DeclEnum &decl) : ITypeSymbol(decl.name), decl(decl) {}
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