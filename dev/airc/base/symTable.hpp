#ifndef __SYMTABLE_INC__
#define __SYMTABLE_INC__

#include "strPool.hpp"
#include "utils/pch.hpp"
namespace air
{
    enum class SymbolKind
    {
        Unkonwn,
        File,      // 文件
        Type,      // 基本类型
        Struct,    // 结构类型
        Union,     // 联合类型
        Entrust,   // 委托类型
        Interface, // 接口类型
        Class,     // 类类型
        Variable,  // 变量
        Function,  // 函数

    };
    // 符号定义
    struct ISymbol;

    // 符号引用
    using SymbolRef = std::shared_ptr<ISymbol>;
    inline SymbolRef makeSymbol(ISymbol *symbol) { return SymbolRef(symbol); }
    template <typename Symbol, typename... Arg>
    inline SymbolRef genSymbol(Symbol *&instance, Arg... arg)
    {
        instance = new Symbol(arg...);
        return SymbolRef(instance);
    }
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
        inline Result find(const std::string *name) const
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
        // 设置生成符号表
        inline void setSuper(SymbolTable &sup) { super = &sup; }

        // 获取符号表大小
        inline auto getSize() const { return map.size(); }

    private:
        SymbolTable *super;                           // 上层符号表
        std::map<const std::string *, SymbolRef> map; // 符号映射表
    };

    // 符号名称重名规则:同一符号表内部,名称不得重复
    struct ISymbol
    {
        inline ISymbol(StringRef &full, StringRef &name, SymbolKind kind = SymbolKind::Unkonwn)
            : name(name), full(full), kind(kind) {}

        inline bool isType() const { return kind == SymbolKind::Type; }
        inline bool isFunction() const { return kind == SymbolKind::Function; }
        inline bool isVariable() const { return kind == SymbolKind::Variable; }

        inline const StringRef &getName() const { return name; }
        inline const StringRef &getFull() const { return full; }
        inline SymbolKind getKind() const { return kind; }

        inline void setFull(StringRef &fullname) { full = fullname; }

        inline SymbolTable &getSymbols() { return symbols; }
        inline SymbolTable::Result insert(const std::string *subname, SymbolRef sym) { return symbols.insert(subname, sym); }
        inline SymbolTable::Result find(const std::string *subname) const { return symbols.find(subname); }

        TokPos startpos;
        TokPos endpos;

    protected:
        StringRef name;      // 符号的短名称
        StringRef full;      // 符号的全名称
        SymbolKind kind;     // 符号类别
        SymbolTable symbols; // 内部符号表
    };
    // 文件符号
    struct IFileSymbol : public ISymbol
    {
        IFileSymbol(StringRef &name) : ISymbol(name, name, SymbolKind::File) {}
    };
    //  类型符号
    struct ISymbolType : public ISymbol
    {

        inline ISymbolType(SymbolKind kind, StringRef &full, StringRef &name,
                           uintptr_t size, uintptr_t align,
                           bool sign, bool buildin = false)
            : ISymbol(full, name, kind),
              size(size), align(align),
              sign(sign), buildin(buildin), clas(false) {}

        inline uintptr_t getSize() const { return size; }
        inline uintptr_t getAlign() const { return align; }
        inline bool getSigned() const { return sign; }

    protected:
        uintptr_t size;  // 内存大小,单位：字节
        uintptr_t align; // 对齐大小,单位：字节
        bool sign;       // 有符号？
        bool buildin;    // 内建类型？
        bool clas;       // 类？
    };
    // 内建类型符号
    struct BuildinTypeSymbol : public ISymbolType
    {
        inline BuildinTypeSymbol(StringRef &name, uintptr_t size, uintptr_t align, bool sign)
            : ISymbolType(SymbolKind::Type, name, name, size, align, sign, true) {}
    };

    // 变量符号
    struct IVarSymbol : public ISymbol
    {
        IVarSymbol(StringRef &name) : ISymbol(name, name, SymbolKind::Variable) {}
    };
    // 函数符号
    struct IFuncSymbol : public ISymbol
    {
        IFuncSymbol(StringRef &full, StringRef &name, bool buildin = false)
            : ISymbol(full, name, SymbolKind::Function), buildin(buildin) {}
        bool buildin; // 内建函数？
    };

}
#endif // __SYMTABLE_INC__