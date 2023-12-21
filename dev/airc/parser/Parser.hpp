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
        AstExpRef getExpTer(AstExpRef &cond);  // 解析三元表达式          // 解析三元表达式

        //----------------------------解析声明-------------------------
        AstDeclRef getDeclEnum(ScopeEnum scope, TokPos &startpos);
        AstDeclRef getDeclStruct(ScopeEnum scope, TokPos &startpos);
        AstDeclRef getDeclUnion(ScopeEnum scope, TokPos &startpos);
        AstDeclRef getDeclEntrust(ScopeEnum scope, TokPos &startpos);
        AstDeclRef getDeclInterface(ScopeEnum scope, TokPos &startpos);
        AstDeclRef getDeclClass(ScopeEnum scope, TokPos &startpos);

        //----------------------------解析语句-----------------------------
        AstStmRef getStmBlock();

        AstStmRef getStmIf(TokPos &startpos);
        AstStmRef getStmElsif(TokPos &startpos);
        AstStmRef getStmElse(TokPos &startpos);

        AstStmRef getStmSwitch(TokPos &startpos);
        AstStmRef getStmCase(TokPos &startpos);
        AstStmRef getStmDefault(TokPos &startpos);

        AstStmRef getStmFor(TokPos &startpos);
        AstStmRef getStmDoWhile(TokPos &startpos);
        AstStmRef getStmWhile(TokPos &startpos);

        AstStmRef getStmTry(TokPos &startpos);
        AstStmRef getStmCatch(TokPos &startpos);
        AstStmRef getStmFinally(TokPos &startpos);
        AstStmRef getStmThrow(TokPos &startpos);

        AstStmRef getStmLable(TokPos &startpos);
        AstStmRef getStmGoto(TokPos &startpos);
        AstStmRef getStmBreak(TokPos &startpos);
        AstStmRef getStmContinue(TokPos &startpos);
        AstStmRef getStmReturn(TokPos &startpos);
        AstStmRef getStmVar(TokPos &startpos);
        AstStmRef getStmExp(TokPos &startpos);
    };
}

#endif // __PARSER_INC__