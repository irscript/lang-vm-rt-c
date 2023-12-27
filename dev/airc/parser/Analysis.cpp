#include "Analysis.hpp"
#include "utils/errorWhat.hpp"
#include "utils/print.hpp"
namespace air
{
    void CitationResolution::start()
    {
        // 引用消解
        for (auto item : unit.declist)
        {
            item->visit(*this, {});
        }
    }
    void CitationResolution::repeatSymbol(ISymbol *cur, ISymbol *pre)
    {
        std::string src = lexer.getLineTxt(cur->startpos.line,
                                           cur->startpos.pos,
                                           cur->endpos.pos);
        Printer::lock();
        Printer::print(Printer::Yellow, "\n当前定义：\n");
        Printer::print(Printer::Aqua, "%s\n", src.c_str());

        throw ErrorWhat::fmt("符号名称( %s )冲突！\n", pre->getName().get().c_str());
    }

    void CitationResolution::resolType(AstType &type)
    {
        // 查看是否是基本类型
        if (type.name.size() == 1)
        {
            auto name = type.name.front();
            auto result = gsymbol.find(&name.get());
            if (result.first == true)
            {
                auto &sym = result.second;
                if (sym->getKind() != SymbolKind::Type)
                    throw ErrorWhat::fmt("符号( %s )非类型！\n", name.get().c_str());
                type.type = sym;
                return;
            }
        }
        // 自定义类型
        throw ErrorWhat::fmt("暂不支持自定义类型！\n");
    }

    // 生成全名
    void CitationResolution::genFullName(SymbolRef sym)
    {
        std::string full = sym->getName().get() == "main" ? sym->getName().get() : unit.package.get() + "." + sym->getName().get();
        auto fullname = pool.refString(full);
        sym->setFull(fullname);
        auto result = gsymbol.insert(&fullname.get(), sym);
        if (result.first == false)
            throw ErrorWhat::fmt("符号( %s )已经定义！\n", full.c_str());
    }
    std::any CitationResolution::visit(DeclFile &dec, std::any opt)
    {
        FileSymbol *sym;
        // 插入符号
        auto symref = genSymbol(sym, dec);
        sym->startpos = dec.startpos;
        sym->endpos = dec.endpos;
        auto res = unit.symbols.insert(&dec.name.get(), symref);
        // 符号重复
        if (res.first == false)
            repeatSymbol(sym, res.second.get());
        return {};
    }

    std::any CitationResolution::visit(DeclVar &dec, std::any opt)
    {
        // 加入符号表
        VarSymbol *sym;
        auto symref = genSymbol(sym, dec, project.getVarSerial());
        sym->startpos = dec.startpos;
        sym->endpos = dec.endpos;
        auto res = unit.symbols.insert(&dec.name.get(), symref);
        // 符号重复
        if (res.first == false)
            repeatSymbol(sym, res.second.get());

        // 生成全名符号
        genFullName(symref);

        // 查找变量类型
        resolType(dec.type);

        // 是否是静态数组

        // 检查初始值表达式

        // 同行定义的变量
        if (dec.nextvar.get() != nullptr)
            dec.nextvar->visit(*this, {});

        return {};
    }

    std::any CitationResolution::visit(DeclFunc &dec, std::any opt)
    {
        // 加入符号表
        FuncSymbol *sym;
        auto symref = genSymbol(sym, dec, project.getFuncSerial());
        sym->startpos = dec.startpos;
        sym->endpos = dec.endpos;
        auto res = unit.symbols.insert(&dec.name.get(), symref);
        // 符号重复
        if (res.first == false)
            repeatSymbol(sym, res.second.get());

        // 生成全名符号
        genFullName(symref);

        // 查找返回值类型
        resolType(dec.retType);
        // 检查参数类型
        for (auto item : dec.args)
        {
            resolType(dec.retType);
        }

        return {};
    }

    std::any CitationResolution::visit(DeclEnum &dec, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(DeclStruct &dec, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(DeclInterface &dec, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(DeclEntrust &dec, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(DeclClass &dec, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmBlock &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmIf &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmElsif &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmElse &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmSwitch &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmCase &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmDefault &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmFor &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmDoWhile &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmWhile &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmTry &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmCatch &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmFinally &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmThrow &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmLabel &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmGoto &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmBreak &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmContinue &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmReturn &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmVar &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(StmExp &stm, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpAnnFile &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpAnnFunc &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpAnnLine &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpBool &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpNull &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpSInt &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpUInt &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpFlt32 &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpFlt64 &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpChar &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpString &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpThis &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpSuper &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpID &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpFuncCall &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpMemberCall &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpUnary &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpBinary &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpTernary &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpParen &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpBlock &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpInRange &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpRange &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpArrayIndex &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpCast &exp, std::any opt)
    {
        return {};
    }

    std::any CitationResolution::visit(ExpNew &exp, std::any opt)
    {
        return {};
    }
}