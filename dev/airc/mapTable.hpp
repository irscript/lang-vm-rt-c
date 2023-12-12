#ifndef __MAPTABLE_INC__
#define __MAPTABLE_INC__
#include "lexer/TkEnum.hpp"
#include "utils/pch.hpp"
namespace air
{

    struct MapTable
    {
        // 初始化信息
        static void init();
        // 查找关键字
        static TkKeyWord findKeyword(const std::string &szTok)
        {
            auto find = mapKey.find(szTok);
            if (find == mapKey.end())
                return TkKeyWord::Unknown;
            return find->second;
        }
        // 查找标注关键字
        static TkAnnotate findAnnword(const std::string &szTok)
        {
            auto find = mapAnn.find(szTok);
            if (find == mapAnn.end())
                return TkAnnotate::Unknown;
            return find->second;
        }
        // 查找操作符优先级
        static int32_t findOpPriority(TkOpEnum op)
        {
            auto find = mapOp.find(op);
            if (find == mapOp.end())
                return INT32_MAX;
            return find->second;
        }

    private:
        static std::map<std::string, TkKeyWord> mapKey;  // 普通关键字映射表
        static std::map<std::string, TkAnnotate> mapAnn; // 注解关键字映射表
        static std::map<TkOpEnum, int32_t> mapOp;        // 操作符优先级映射

        static void initMapKey(); // 初始化普通关键字映射表
        static void initMapAnn(); // 初始化注解关键字映射表
        static void initMapOp();  // 初始化操作符优先级映射
    };
}

#endif // __MAPTABLE_INC__