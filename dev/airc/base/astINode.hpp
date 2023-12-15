#ifndef __ASTINODE_INC__
#define __ASTINODE_INC__
#include "utils/pch.hpp"
namespace air
{
    // 语法节点访问者
    struct IAstVisitor;
    // 语法节点基类
    struct IAstNode
    {
        uint32_t startpos; // 开始位置
        uint32_t endpos;   // 结束文字
        bool mIsErr;       // 是否是错误节点
        // 接收访问者访问
        virtual std::any visit(IAstVisitor &visitor, std::any opt) = 0;
    };
    // 表达式节点
    struct IAstExp;
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
    struct ExpMemberCall; // 成员调用 表达式
    struct ExpUnary;      // 一元 表达式
    struct ExpBinary;     // 二元 表达式
    struct ExpTernary;    // 三元 表达式
    struct ExpParen;      // 括号 表达式
    struct ExpNew;        // new 表达式
    struct ExpCast;       // cast 表达式
    struct ExpArrayIndex; // 数组索引 表达式
    struct ExpRang;       // 范围 表达式
    struct ExpBlock;      // 块 表达式

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
        virtual std::any visit(StmElse &stm, std::any opt) = 0;
        virtual std::any visit(StmSwitch &stm, std::any opt) = 0;
        virtual std::any visit(StmCase &stm, std::any opt) = 0;
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

}

#endif // __ASTNODE_INC__