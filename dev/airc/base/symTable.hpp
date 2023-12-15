#ifndef __SYMTABLE_INC__
#define __SYMTABLE_INC__

#include "strPool.hpp"
#include "utils/pch.hpp"
namespace air
{
    enum class SymbolKind
    {
        Unkonwn,
        Type,     // 类型
        Function, // 函数
        Variable, // 变量
    };
    // 符号定义
    struct ISymbol
    {
        StringRef &name; // 符号的短名称
        StringRef &full; // 符号的全名称
        SymbolKind kind; // 符号类别

        ISymbol(StringRef &full, StringRef &name, SymbolKind kind = SymbolKind::Unkonwn) : name(name), full(full), kind(kind) {}

        inline bool isType() const { return kind == SymbolKind::Type; }
        inline bool isFunction() const { return kind == SymbolKind::Function; }
        inline bool isVariable() const { return kind == SymbolKind::Variable; }
    };
    // 符号引用
    using SymbolRef = std::shared_ptr<ISymbol>;

    // 类型符号
    struct ISymbolType : ISymbol
    {
        uintptr_t size;  // 内存大小
        uintptr_t align; // 对齐大小

        ISymbolType(StringRef &full, StringRef &name, uintptr_t size, uintptr_t align)
            : ISymbol(full, name, SymbolKind::Type), size(size), align(align) {}
    };

    // 符号表定义
    struct SymbolTable
    {
        SymbolTable(SymbolTable *super = nullptr) : super(super) {}

        using Result = std::pair<bool, SymbolRef>; // 操作结果
        // 插入符号
        inline Result insert(const std::string *name, SymbolRef sym)
        {
            auto res = map.insert({name, sym});
            return Result(res.second, res.first->second);
        }
        // 查找符号
        inline Result find(const std::string *name)
        {
            auto res = map.find(name);
            if (res == map.end() && super != nullptr)
            {
                return super->find(name);
            }
            return Result(true, res->second);
        }

        // 是顶层符号表？
        inline bool isTop() const { return super == nullptr; }

    private:
        SymbolTable *super;                            // 上层符号表
        std::map<const std::string *, SymbolRef> map; // 符号映射表
    };

    // 符号名称重名规则:同一符号表内部,名称不得重复

}
#endif // __SYMTABLE_INC__