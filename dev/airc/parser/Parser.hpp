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
        // 处理缺少词元
        void missingToken(Token &tok, const char *fmt);

        // 解析包名
        void getPackage();
        // 解析依赖
        void getRequire();
        void getRequireItem();

        // 开始解析声明
        void getDecl();
        // 解析作用域
        ScopeEnum getScope();

        // 解析表达式
        inline AstExpRef getExp()
        {
            return getBinExp();
        }
        AstExpRef getBaseExp(); // 解析基础表达式
        AstExpRef getFuncExp(); // 解析函数调用
        AstExpRef getUnaExp();  // 解析一元表达式
        AstExpRef getBinExp();  // 解析二元表达式
        AstExpRef getTerExp();  // 解析三元表达式
    };
}

#endif // __PARSER_INC__