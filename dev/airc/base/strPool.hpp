#ifndef __STRPOOL_INC__
#define __STRPOOL_INC__
#include "utils/pch.hpp"
namespace air
{
    using StringRef = const std::string *;
    // 字符串引用池
    class StringPool
    {
    private:
        // map<字符串 ,引用次数>
        using Pool = std::map<std::string, uint32_t>;
        using Item = std::pair<std::string, uint32_t>;

        Pool mPools;

    public:
        StringPool() {}
        ~StringPool() { mPools.clear(); }

        // 添加一个字符串引用,不存在就插入，存在就引用次数+1
        inline const StringRef refString(const std::string &szRefs);
        // 释放一个字符串引用，存在就引用次数-1,引用次数为0时释放字符串,返回释放后引用次数
        inline void unrefString(const StringRef szRefs);
    };

    inline const StringRef StringPool::refString(const std::string &szRefs)
    {
        auto res = mPools.insert(Item(szRefs, 1));

        if (res.second == false)
            res.first->second += 1;

        return (StringRef) & (res.first->first);
    }

    inline void StringPool::unrefString(const StringRef szRefs)
    {
        if (szRefs == nullptr)
            return;
        auto it = mPools.find(*szRefs);
        if (it != mPools.end())
        {
            --it->second;
            if (it->second == 0)
                mPools.erase(it);
        }
    }
}

#endif // __STRPOOL_INC__