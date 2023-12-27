#ifndef __FILEUNIT_INC__
#define __FILEUNIT_INC__

#include "astNode.hpp"
#include "strPool.hpp"
#include "symTable.hpp"
#include "utils/pch.hpp"
#include "airc/lexer/Lexer.hpp"
namespace air
{
    // 编译的文件单元
    struct FileUnit
    {
        FileUnit() : state(0), file(nullptr) {}
        // 文件状态
        union
        {
            uint32_t state;
            struct
            {
                uint32_t error : 1; // 错误？
            };
        };

        const std::string *file; // 文件路径

        SymbolTable symbols;           // 文件内符号表
        StringRef package;             // 包名
        std::list<AstDeclRef> declist; // 声明列表
    };
}
#endif // __FILEUNIT_INC__