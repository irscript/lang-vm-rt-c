#ifndef __STRPOOL_INC__
#define __STRPOOL_INC__
#include "utils/pch.hpp"
namespace air
{
    struct StringRef;
    // 字符串引用池
    class StringPool
    {
    private:
        // map<字符串 ,引用次数>
        using Pool = std::map<std::string, StringRef>;
        using Item = std::pair<std::string, StringRef>;

        Pool mPools;

    public:
        StringPool() {}
        ~StringPool() { mPools.clear(); }

        // 添加一个字符串引用,不存在就插入，存在就引用次数+1
        inline const StringRef &refString(const std::string &szRefs);

    private:
        friend struct StringRef;
        // 释放一个字符串引用，存在就引用次数-1,引用次数为0时释放字符串,返回释放后引用次数
        inline void unrefString(const std::string *szRefs);
    };
    struct StringRef
    {
        ~StringRef() { pool->unrefString(str); }
        // 获取名称
        const std::string &get() const { return *str; }

    private:
        friend class StringPool;
        StringRef(StringPool *pool, std::string *str) : pool(pool), str(str), count(1) {}

        StringPool *pool;       // 所归属的字符串池
        const std::string *str; // 字符串
        uint32_t count;         // 引用计数
    };

    inline const StringRef &StringPool::refString(const std::string &szRefs)
    {
        auto res = mPools.insert(Item(szRefs, StringRef(this, nullptr)));
        if (res.second == true)
        {
            res.first->second.str = &res.first->first;
        }
        else
        {
            res.first->second.count += 1;
        }

        return res.first->second;
    }

    inline void StringPool::unrefString(const std::string *szRefs)
    {
        if (szRefs == nullptr)
            return;
        auto res = mPools.find(*szRefs);
        if (res != mPools.end())
        {
            --res->second.count;
            if (res->second.count == 0)
                mPools.erase(res);
        }
    }
}

#endif // __STRPOOL_INC__