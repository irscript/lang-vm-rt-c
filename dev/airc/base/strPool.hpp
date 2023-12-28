#ifndef __STRPOOL_INC__
#define __STRPOOL_INC__
#include "utils/pch.hpp"
namespace air
{
    struct StringItem; // 字符串项定义
    struct StringRef;  // 字符串项引用
    // 字符串引用池
    class StringPool
    {
    private:
        // map<字符串 ,引用次数>
        using Pool = std::map<std::string, StringItem>;
        using Item = std::pair<std::string, StringItem>;

        Pool mPools;

    public:
        inline StringPool() {}
        inline ~StringPool() { mPools.clear(); }

        // 添加一个字符串引用,不存在就插入，存在就引用次数+1
        inline StringRef refString(const std::string &szRefs);

    private:
        friend struct StringItem;
        friend struct StringRef;
        // 释放一个字符串引用，存在就引用次数-1,引用次数为0时释放字符串,返回释放后引用次数
        inline void unrefString(const std::string &szRefs);
    };
    struct StringItem
    {
        inline ~StringItem() {}
        // 获取名称
        inline const std::string &get() const { return *str; }
        // 引用一次
        inline void ref()
        {
            std::atomic_uint32_t &at = *(std::atomic_uint32_t *)&count;
            ++at;
            //__sync_add_and_fetch(&count, 1);
        }
        // 释放一次
        inline uint32_t unref()
        {
            std::atomic_uint32_t &at = *(std::atomic_uint32_t *)&count;
            return --at;
            // return __sync_sub_and_fetch(&count, 1);
        }

    private:
        friend struct StringPool;
        inline StringItem(std::string *str) : str(str), count(1) {}

        const std::string *str;  // 字符串
        volatile uint32_t count; // 引用计数
    };
    struct StringRef
    {
        inline ~StringRef()
        {
            if (pool)
                pool->unrefString(get());
        }
        // 获取名称
        const std::string &get() const { return item->get(); }
        StringRef() : StringRef(nullptr, nullptr) {}
        inline StringRef(const StringRef &rhs) : StringRef(rhs.pool, rhs.item)
        {
            if (item)
                item->ref();
        }

        inline StringRef &operator=(const StringRef &rhs)
        {
            if (item)
                item->unref();
            pool = rhs.pool;
            item = rhs.item;
            item->ref();
            return *this;
        }

        inline bool operator==(const StringRef &rhs) const { return rhs.pool == pool && rhs.item == item; }
        inline bool operator<(const StringRef &rhs) const { return item->get() < rhs.item->get(); }

    private:
        friend struct StringPool;
        inline StringRef(StringPool *pool, StringItem *str) : pool(pool), item(str) {}

        StringPool *pool; // 所归属的字符串池
        StringItem *item; // 字符串
    };

    inline StringRef StringPool::refString(const std::string &szRefs)
    {
        auto res = mPools.insert(Item(szRefs, StringItem(nullptr)));
        if (res.second == true)
        {
            res.first->second.str = &res.first->first;
        }
        else
        {
            res.first->second.ref();
        }

        StringRef ret(this, &res.first->second);
        return ret;
    }

    inline void StringPool::unrefString(const std::string &szRefs)
    {
        auto res = mPools.find(szRefs);
        if (res != mPools.end())
        {
            if (res->second.unref() == 0)
                mPools.erase(res);
        }
    }
}

#endif // __STRPOOL_INC__