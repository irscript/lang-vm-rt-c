#ifndef __PARSER_INC__
#define __PARSER_INC__

#include "airc/base/fileUnit.hpp"
#include "airc/lexer/Lexer.hpp"
#include "utils/errorWhat.hpp"
#include "utils/pch.hpp"
#include "utils/print.hpp"
namespace air
{
    // 语法解析器
    struct Parser
    {
        inline Parser(StringPool &pool, Lexer &lexer, FileUnit &unit)
            : pool(pool), lexer(lexer), unit(unit) { start(); }

    protected:
        Lexer &lexer;     // 词法分析器
        FileUnit &unit;   // 文件单元
        StringPool &pool; // 字符串池
        // 开始解析
        void start();
        // 处理重复的符号
        void repeatSymbol(ISymbol *cur, ISymbol *pre);
        // 处理语法错误
        void syntaxError(Token &tok, const char *fmt);

        // 解析包名
        void getPackage();
        // 解析依赖
        void getRequire();
        void getRequireItem();
        // 解析作用域
        ScopeEnum getScope();
        // 开始解析声明
        AstDeclRef getDecl();

        // 解析类型
        void getType(AstType &type);

        // 解析标注
        AstAnnRef getAnn(Token &tok);

        // ---------------------------解析表达式------------------------
        inline AstExpRef getExp()
        {
            return getExpBin(0);
        }
        AstExpRef getExpBase();                // 解析基础表达式
        void getExpArray(ExpArrayIndex &exp);  // 数组
        void getExpFunc(ExpFuncCall &exp);     // 函数调用
        AstExpRef getExpUna();                 // 解析一元表达式
        AstExpRef getExpBin(int32_t priority); // 解析二元表达式
        AstExpRef getExpTer(AstExpRef &cond);  // 解析三元表达式

        //----------------------------解析声明-------------------------
        AstDeclRef getDeclVar(ScopeEnum scope, TokPos &startpos, AstType &type, StringRef &name, bool array); // 解析 变量 声明
        AstDeclRef getDeclFunc(ScopeEnum scope, TokPos &startpos, AstType &type, StringRef &name);            // 解析 函数 声明
        void getDeclFunParam(DeclFunc &func);                                                                 // 解析 函数参数 声明
        AstDeclRef getDeclEnum(ScopeEnum scope, TokPos &startpos);                                            // 解析 枚举 声明
        AstDeclRef getDeclStruct(ScopeEnum scope, TokPos &startpos);                                          // 解析 结构体 声明
        AstDeclRef getDeclUnion(ScopeEnum scope, TokPos &startpos);                                           // 解析 联合体 声明
        AstDeclRef getDeclEntrust(ScopeEnum scope, TokPos &startpos);                                         // 解析 委托 声明
        AstDeclRef getDeclInterface(ScopeEnum scope, TokPos &startpos);                                       // 解析 接口 声明
        AstDeclRef getDeclClass(ScopeEnum scope, TokPos &startpos);                                           // 解析 类 声明

        //----------------------------解析语句-----------------------------
        AstStmRef getStmBlock(); // 解析 块 语句

        AstStmRef getStmVar(TokPos &startpos);   // 解析 变量声明 语句
        AstStmRef getStmExp(TokPos &startpos);   // 解析 表达式 语句
        AstStmRef getStmLable(TokPos &startpos); // 解析 标签声明 语句

        AstStmRef getStmGoto(TokPos &startpos);     // 解析 goto lable; 语句
        AstStmRef getStmBreak(TokPos &startpos);    // 解析 break; 语句
        AstStmRef getStmContinue(TokPos &startpos); // 解析 continue; 语句
        AstStmRef getStmReturn(TokPos &startpos);   // 解析 return exp;语句

        AstStmRef getStmIf(TokPos &startpos);    // 解析 if 语句
        AstStmRef getStmElsif(TokPos &startpos); // 解析 elsif 语句
        AstStmRef getStmElse(TokPos &startpos);  // 解析 else 语句

        AstStmRef getStmSwitch(TokPos &startpos);  // 解析 switch 语句
        AstStmRef getStmCase(TokPos &startpos);    // 解析 case 语句
        AstStmRef getStmDefault(TokPos &startpos); // 解析 default 语句

        AstStmRef getStmFor(TokPos &startpos);     // 解析 for 语句
        AstStmRef getStmDoWhile(TokPos &startpos); // 解析 do{}while() 语句
        AstStmRef getStmWhile(TokPos &startpos);   // 解析 while 语句

        AstStmRef getStmTry(TokPos &startpos);     // 解析 try 语句
        AstStmRef getStmCatch(TokPos &startpos);   // 解析 catch 语句
        AstStmRef getStmFinally(TokPos &startpos); // 解析 finally 语句
        AstStmRef getStmThrow(TokPos &startpos);   // 解析 throw 语句
    };
}

#endif // __PARSER_INC__