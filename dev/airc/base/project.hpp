#ifndef __PROJECT_INC__
#define __PROJECT_INC__

#include "strPool.hpp"
#include "symTable.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 项目单元
    struct Project
    {
        StringPool pool;   // 字符串池
        SymbolTable table; // 全局符号表

        std::set<std::string> mDirs;  // 搜索的目录
        std::set<std::string> mFiles; // 编译的文件
    };
}

#endif // __PROJECT_INC__