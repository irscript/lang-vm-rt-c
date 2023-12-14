#ifndef __SYMTABLE_INC__
#define __SYMTABLE_INC__

#include "strPool.hpp"
#include "utils/pch.hpp"
namespace air
{
    enum class SymbolKind
    {
        Unkonwn,
        Type, // 类型
        Func, // 函数
        Var,  // 变量
    };
    // 符号定义
    struct ISymbol
    {
        StringRef name;  // 符号的名称
        SymbolKind kind; // 符号类别

        ISymbol(StringRef name, SymbolKind kind = SymbolKind::Unkonwn) : name(name), kind(kind) {}
    };
    // 符号引用
    using SymbolRef = std::shared_ptr<ISymbol>;

    // 类型符号
    struct ISymbolType : ISymbol
    {
        uintptr_t size;  // 内存大小
        uintptr_t align; // 对齐大小

        ISymbolType(StringRef name, uintptr_t size, uintptr_t align)
            : ISymbol(name, SymbolKind::Type), size(size), align(align) {}
    };

    // 符号表定义
    struct SybolTable
    {
        SybolTable(SybolTable *super = nullptr) : super(super) {}

        // 插入符号
        inline bool insert(ISymbol *sym)
        {
            auto res = map.insert({sym->name, SymbolRef(sym)});
            return res.second;
        }
        // 查找符号
        inline SymbolRef find(const StringRef name)
        {
            auto res = map.find(name);
            if (res == map.end())
            {
                if (super != nullptr)
                    return super->find(name);
                return SymbolRef();
            }
            return res->second;
        }

    private:
        SybolTable *super;                  // 上层符号表
        std::map<StringRef, SymbolRef> map; // 符号映射表
    };

    // 符号名称重名规则
    /*
     * 在同一作用域下不得出现符号名称相同
     */
}
#endif // __SYMTABLE_INC__