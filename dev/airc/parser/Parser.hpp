#ifndef __PARSER_INC__
#define __PARSER_INC__

#include "airc/base/fileUnit.hpp"
#include "airc/lexer/Lexer.hpp"

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

        // 解析包名
        void getPackage();
        // 解析依赖
        void getRequire();
    };
}

#endif // __PARSER_INC__