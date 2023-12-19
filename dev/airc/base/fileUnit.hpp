#ifndef __FILEUNIT_INC__
#define __FILEUNIT_INC__

#include "astNode.hpp"
#include "strPool.hpp"
#include "symTable.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 编译的文件单元
    struct FileUnit
    {
        FileUnit() : state(0) {}
        // 文件状态
        union
        {
            uint32_t state;
            struct
            {
                uint32_t error : 1; // 错误？
            };
        };
        SymbolTable symbols; // 文件内符号表
    };
}
#endif // __FILEUNIT_INC__