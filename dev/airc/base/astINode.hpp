#ifndef __ASTINODE_INC__
#define __ASTINODE_INC__
#include "airc/lexer/Token.hpp"
#include "symTable.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 语法节点访问者
    struct IAstVisitor;
    // 语法节点基类
    struct IAstNode
    {
        TokPos startpos; // 开始位置
        TokPos endpos;   // 结束文字
        bool mIsErr;     // 是否是错误节点

        IAstNode() : mIsErr(false) {}
        // 接收访问者访问
        virtual std::any visit(IAstVisitor &visitor, std::any opt) = 0;
    };

    // 标注节点
    struct IAstAnn;

    struct AnnBuildin;  //@buildin
    struct AnnAsync;    //@async
    struct AnnVolatile; //@volatile
    struct AnnInline;   //@inline
    struct AnnVirtual;  //@virtual
    struct AnnOverride; //@override
    struct AnnOperator; //@operator

    // struct Ann;         //@

    // 表达式节点
    struct IAstExp;
    struct ExpAnnFile;    //@file 常量表达式
    struct ExpAnnFunc;    //@func 常量表达式
    struct ExpAnnLine;    //@line 常量表达式
    struct ExpBool;       // bool 常量表达式
    struct ExpNull;       // null 常量表达式
    struct ExpSInt;       // sint 常量表达式
    struct ExpUInt;       // uint 常量表达式
    struct ExpFlt32;      // flt32 常量表达式
    struct ExpFlt64;      // flt64 常量表达式
    struct ExpChar;       // 字符 常量表达式
    struct ExpString;     // 字符串 常量表达式
    struct ExpThis;       // this 表达式
    struct ExpSuper;      // super 表达式
    struct ExpID;         // 标识符 表达式
    struct ExpFuncCall;   // 函数调用 表达式
    struct ExpArrayIndex; // 数组索引 表达式
    struct ExpMemberCall; // 成员调用 表达式
    struct ExpUnary;      // 一元 表达式
    struct ExpBinary;     // 二元 表达式
    struct ExpTernary;    // 三元 表达式
    struct ExpParen;      // 括号 表达式
    struct ExpNew;        // new 表达式
    struct ExpCast;       // cast 表达式

    struct ExpRang;  // 范围 表达式
    struct ExpBlock; // 块 表达式

    // 声明节点
    struct IAstDecl;
    struct DeclFile;      // 文件依赖声明
    struct DeclVar;       // 变量声明
    struct DeclFunc;      // 函数声明
    struct DeclEnum;      // 枚举声明
    struct DeclStruct;    // 结构体声明
    struct DeclInterface; // 接口声明
    struct DeclEntrust;   // 委托声明
    struct DeclClass;     // 类声明

    // 语句节点
    struct IAstStm;
    struct StmBlock; // 块语句

    struct StmIf;    // if 语句
    struct StmElsif; // elsif 语句
    struct StmElse;  // else 语句

    struct StmSwitch;  // switch 语句
    struct StmCase;    // case 语句
    struct StmDefault; // default 语句

    struct StmFor;     // 语句
    struct StmDoWhile; // 语句
    struct StmWhile;   // 语句

    struct StmTry;     // 语句
    struct StmCatch;   // 语句
    struct StmFinally; // 语句
    struct StmThrow;   // 语句

    struct StmLable;    // 语句
    struct StmGoto;     // 语句
    struct StmBreak;    // 语句
    struct StmContinue; // 语句
    struct StmReturn;   // 语句

    struct StmVar; // 语句
    struct StmExp; // 语句

    // 访问者接口
    struct IAstVisitor
    {
        inline virtual ~IAstVisitor() {}
        // 访问声明
        virtual std::any visit(DeclFile &dec, std::any opt) = 0;
        virtual std::any visit(DeclVar &dec, std::any opt) = 0;
        virtual std::any visit(DeclFunc &dec, std::any opt) = 0;
        virtual std::any visit(DeclEnum &dec, std::any opt) = 0;
        virtual std::any visit(DeclStruct &dec, std::any opt) = 0;
        virtual std::any visit(DeclInterface &dec, std::any opt) = 0;
        virtual std::any visit(DeclEntrust &dec, std::any opt) = 0;
        virtual std::any visit(DeclClass &dec, std::any opt) = 0;
        // 访问语句
        virtual std::any visit(StmBlock &stm, std::any opt) = 0;
        virtual std::any visit(StmIf &stm, std::any opt) = 0;
        virtual std::any visit(StmElsif &stm, std::any opt) = 0;
        virtual std::any visit(StmElse &stm, std::any opt) = 0;
        virtual std::any visit(StmSwitch &stm, std::any opt) = 0;
        virtual std::any visit(StmCase &stm, std::any opt) = 0;
        virtual std::any visit(StmDefault &stm, std::any opt) = 0;
        virtual std::any visit(StmFor &stm, std::any opt) = 0;
        virtual std::any visit(StmDoWhile &stm, std::any opt) = 0;
        virtual std::any visit(StmWhile &stm, std::any opt) = 0;
        virtual std::any visit(StmTry &stm, std::any opt) = 0;
        virtual std::any visit(StmCatch &stm, std::any opt) = 0;
        virtual std::any visit(StmFinally &stm, std::any opt) = 0;
        virtual std::any visit(StmThrow &stm, std::any opt) = 0;
        virtual std::any visit(StmLable &stm, std::any opt) = 0;
        virtual std::any visit(StmGoto &stm, std::any opt) = 0;
        virtual std::any visit(StmBreak &stm, std::any opt) = 0;
        virtual std::any visit(StmContinue &stm, std::any opt) = 0;
        virtual std::any visit(StmReturn &stm, std::any opt) = 0;
        virtual std::any visit(StmVar &stm, std::any opt) = 0;
        virtual std::any visit(StmExp &stm, std::any opt) = 0;

        // 访问表达式
        virtual std::any visit(ExpAnnFile &exp, std::any opt) = 0;
        virtual std::any visit(ExpAnnFunc &exp, std::any opt) = 0;
        virtual std::any visit(ExpAnnLine &exp, std::any opt) = 0;
        virtual std::any visit(ExpBool &exp, std::any opt) = 0;
        virtual std::any visit(ExpNull &exp, std::any opt) = 0;
        virtual std::any visit(ExpSInt &exp, std::any opt) = 0;
        virtual std::any visit(ExpUInt &exp, std::any opt) = 0;
        virtual std::any visit(ExpFlt32 &exp, std::any opt) = 0;
        virtual std::any visit(ExpFlt64 &exp, std::any opt) = 0;
        virtual std::any visit(ExpChar &exp, std::any opt) = 0;
        virtual std::any visit(ExpString &exp, std::any opt) = 0;
        virtual std::any visit(ExpThis &exp, std::any opt) = 0;
        virtual std::any visit(ExpSuper &exp, std::any opt) = 0;
        virtual std::any visit(ExpID &exp, std::any opt) = 0;
        virtual std::any visit(ExpFuncCall &exp, std::any opt) = 0;
        virtual std::any visit(ExpMemberCall &exp, std::any opt) = 0;
        virtual std::any visit(ExpUnary &exp, std::any opt) = 0;
        virtual std::any visit(ExpBinary &exp, std::any opt) = 0;
        virtual std::any visit(ExpTernary &exp, std::any opt) = 0;
        virtual std::any visit(ExpParen &exp, std::any opt) = 0;
        virtual std::any visit(ExpNew &exp, std::any opt) = 0;
        virtual std::any visit(ExpCast &exp, std::any opt) = 0;
        virtual std::any visit(ExpArrayIndex &exp, std::any opt) = 0;
        virtual std::any visit(ExpRang &exp, std::any opt) = 0;
        virtual std::any visit(ExpBlock &exp, std::any opt) = 0;
    };

    // 智能指针
    using AstAnnRef = std::shared_ptr<IAstAnn>;
    using AstDeclRef = std::shared_ptr<IAstDecl>;
    using AstStmRef = std::shared_ptr<IAstStm>;
    using AstExpRef = std::shared_ptr<IAstExp>;

    template <typename Ann, typename... Arg>
    inline AstAnnRef genAnn(Ann *&instance, Arg... arg)
    {
        instance = new Ann(arg...);
        return AstAnnRef(instance);
    }
    template <typename Decl, typename... Arg>
    inline AstDeclRef genDecl(Decl *&instance, Arg... arg)
    {
        instance = new Decl(arg...);
        return AstDeclRef(instance);
    }
    template <typename Stm, typename... Arg>
    inline AstStmRef genStm(Stm *&instance, Arg... arg)
    {
        instance = new Stm(arg...);
        return AstStmRef(instance);
    }
    template <typename Exp, typename... Arg>
    inline AstExpRef genExp(Exp *&instance, Arg... arg)
    {
        instance = new Exp(arg...);
        return AstExpRef(instance);
    }

    // 作用域
    enum class ScopeEnum : uint32_t
    {
        Unknown,
        Public,
        Protected,
        Private,
    };
    // 声明标志
    union AstFlag
    {
        AstFlag() : flag(0) {}

        uint32_t flag;
        struct
        {
            // 通用标记
            ScopeEnum scope : 2;  // 3P 作用域
            uint32_t staticv : 1; // 静态 static 标识
            // uint32_t mConst : 1;  // 常量标识

            // 变量标记
            uint32_t arg : 1; // 参数变量

            // 函数标记
            uint32_t inlinev : 1;   // 内联标识
            uint32_t virtualv : 1;  // 虚函数
            uint32_t pureVir : 1;   // 纯虚函数
            uint32_t overridev : 1; // 函数重写
            uint32_t finalv : 1;    // 子类不再重写虚函数函数
            uint32_t noRet : 1;     // 无返回值
        };
    };

    // 类型元描述
    struct AstType
    {
        AstType() : size(0), offset(0), flag(0) {}
        union
        {
            uint32_t flag; // 类型信息标注
            struct
            {
                uint32_t constv : 1; // 具有 const 修饰 ？

                uint32_t array : 1; // 数组 ？
                uint32_t block : 1; // 块数组 ？
                uint32_t cols : 4;  // 数组维度值

                uint32_t pointer : 1; // 指针？
                uint32_t ptrs : 4;    // 指针维度值
            };
        };

        std::list<StringRef> name; // 类型名称
        SymbolRef type;            // 类型符号
        uintptr_t size;            // 变量大小
        uintptr_t offset;          // 变量偏移量
    };

}

#endif // __ASTNODE_INC__