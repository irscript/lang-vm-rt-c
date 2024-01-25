#include "Symbolization.hpp"
#include "utils/errorWhat.hpp"
#include "utils/print.hpp"
namespace air
{
    struct SymTabInfo
    {
        // 分析阶段
        enum Stage
        {
            Symbolization, // 插入符号：插入符号、验证全局符号重复
            Resolution,    // 引用消解:解决符号接引用、同时连接符号表层次
            TypeCalculate, // 类型计算:计算enum、struct、class等类型大小
            VariableCal,   // 变量计算：计算变量占用的内存大小，和初始值表达式
            ExpCalculate,  // 表达式计算：只对表达式有用
        };
        SymTabInfo(SymbolTable &symtab, bool need, Stage stage)
            : symtab(symtab), needfull(need), stage(stage) {}
        SymbolTable &symtab; // 插入的符号表
        bool needfull;       // 是否需要全名
        Stage stage;         // 只插入符号
    };

    // 表达式的值
    struct ExpValue
    {
        bool flt;  // 浮点
        bool sign; // 有符号

        uint64_t int64;
        flt64_t flt64;
    };

    void Symbolization::start()
    {
        SymTabInfo symbols(funit.symbols, true, SymTabInfo::Symbolization);
        // 符号生成
        for (auto item : funit.declist)
        {
            item->visit(*this, symbols);
        }
        // 引用消解
        symbols.stage = SymTabInfo::Resolution;
        for (auto item : funit.declist)
        {
            item->visit(*this, symbols);
        }
        // 类型计算
        symbols.stage = SymTabInfo::TypeCalculate;
        for (auto item : funit.declist)
        {
            item->visit(*this, symbols);
        }
        // 变量计算
        symbols.stage = SymTabInfo::VariableCal;
        for (auto item : funit.declist)
        {
            item->visit(*this, symbols);
        }
    }
    void Symbolization::repeatSymbol(ISymbol *cur, ISymbol *pre)
    {
        std::string src = funit.stream.getLineTxt(cur->startpos.line,
                                                       cur->startpos.pos,
                                                       cur->endpos.pos);
        Printer::lock();
        Printer::print(Printer::Yellow, "\n当前定义：\n");
        Printer::print(Printer::Aqua, "%s\n", src.c_str());

        throw ErrorWhat::fmt("符号名称( %s )冲突！\n", pre->getName().get().c_str());
    }

    void Symbolization::semanticError(TokPos &start, TokPos &end, const char *msg)
    {
        std::string src = funit.stream.getLineTxt(start.line,
                                                       start.pos,
                                                       end.pos);
        Printer::lock();
        Printer::print(Printer::BrightWhite, "\n%s：\n", funit.file->c_str());
        Printer::print(Printer::Yellow, "\n当前定义：\n");
        Printer::print(Printer::Aqua, "%s\n", src.c_str());

        throw ErrorWhat::fmt("语义错误：%s！\n", msg);
    }

    void Symbolization::resolType(AstType &type)
    {
        // 查看是否是基本类型
        if (type.name.size() == 1)
        {
            auto name = type.name.front();
            auto result = project.symbols.find(&name.get());
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
    void Symbolization::genFullName(SymbolRef sym)
    {
        std::string full = sym->getName().get() == "main" ? sym->getName().get() : funit.package.get() + "." + sym->getName().get();
        auto fullname = project.strings.refString(full);
        sym->setFull(fullname);
        auto result = project.symbols.insert(&fullname.get(), sym);
        if (result.first == false)
            throw ErrorWhat::fmt("符号( %s )已经定义！\n", full.c_str());
    }
    std::any Symbolization::visit(DeclFile &dec, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::Symbolization:
        {
            FileSymbol *sym;
            // 插入符号
            auto symref = genSymbol(sym, dec);
            sym->startpos = dec.startpos;
            sym->endpos = dec.endpos;
            auto res = funit.symbols.insert(&dec.name.get(), symref);
            // 符号重复
            if (res.first == false)
                repeatSymbol(sym, res.second.get());
        }
        break;
        }

        return {};
    }

    std::any Symbolization::visit(DeclVar &dec, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::Symbolization:
        { // 加入符号表
            VarSymbol *sym;
            auto symref = genSymbol(sym, dec, project.getVarSerial());
            sym->startpos = dec.startpos;
            sym->endpos = dec.endpos;
            auto res = symtab.symtab.insert(&dec.name.get(), symref);
            // 符号重复
            if (res.first == false)
                repeatSymbol(sym, res.second.get());

            // 生成全名符号
            if (symtab.needfull == true)
                genFullName(symref);

            // 同行定义的变量
            if (dec.nextvar.get() != nullptr)
                dec.nextvar->visit(*this, opt);
        }
        break;
        case SymTabInfo::Resolution:
        {
            // 查找变量类型
            resolType(dec.type);

            // 同行定义的变量
            if (dec.nextvar.get() != nullptr)
                dec.nextvar->visit(*this, opt);
        }
        break;
        case SymTabInfo::VariableCal:
        {
            auto symtabexp = symtab;
            symtabexp.stage = SymTabInfo::ExpCalculate;
            // 是否是静态数组
            for (auto item : dec.arrcols)
            {
                auto anyret = item->visit(*this, symtabexp);
            }
            // 检查初始值表达式
            if (dec.init.get() != nullptr)
            {
                auto anyret = dec.init->visit(*this, symtabexp);
                auto val = std::any_cast<uint64_t>(anyret);
            }

            // 同行定义的变量
            if (dec.nextvar.get() != nullptr)
                dec.nextvar->visit(*this, opt);
        }
        break;
        }

        return {};
    }

    std::any Symbolization::visit(DeclFunc &dec, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::Symbolization:
        { // 加入符号表
            FuncSymbol *sym;
            auto symref = genSymbol(sym, dec, project.getFuncSerial());
            sym->startpos = dec.startpos;
            sym->endpos = dec.endpos;
            auto res = symtab.symtab.insert(&dec.name.get(), symref);
            // 符号重复
            if (res.first == false)
                repeatSymbol(sym, res.second.get());

            // 生成全名符号
            if (symtab.needfull == true)
                genFullName(symref);
        }
        break;
        case SymTabInfo::Resolution:
        {
            // 查找返回值类型
            resolType(dec.retType);

            // 检查参数类型
            for (auto item : dec.args)
            {
                // 查找类型
                resolType(dec.retType);
                // 添加参数符号
                item->visit(*this, SymTabInfo(dec.argsyms, false, SymTabInfo::Resolution));
            }
            // 检查语句体
            if (dec.body.get() != nullptr)
            {
                StmBlock *stm = (StmBlock *)dec.body.get();
                stm->symbols.setSuper(dec.argsyms);
                dec.body->visit(*this, SymTabInfo(stm->symbols, false, SymTabInfo::Resolution));
            }
        }
        break;
        case SymTabInfo::VariableCal:
        {
        }
        break;
        }

        return {};
    }

    std::any Symbolization::visit(DeclEnum &dec, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::Symbolization:
        {
        }
        break;
        case SymTabInfo::Resolution:
        {
        }
        break;
        case SymTabInfo::TypeCalculate:
        {
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(DeclStruct &dec, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::Symbolization:
        {
        }
        break;
        case SymTabInfo::Resolution:
        {
        }
        break;
        case SymTabInfo::TypeCalculate:
        {
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(DeclInterface &dec, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::Symbolization:
        {
        }
        break;
        case SymTabInfo::Resolution:
        {
        }
        break;
        case SymTabInfo::TypeCalculate:
        {
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(DeclEntrust &dec, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(DeclClass &dec, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmBlock &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmIf &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmElsif &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmElse &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmSwitch &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmCase &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmDefault &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmFor &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmDoWhile &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmWhile &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmTry &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmCatch &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmFinally &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmThrow &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmLabel &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmGoto &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmBreak &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmContinue &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmReturn &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmVar &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(StmExp &stm, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpAnnFile &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpAnnFunc &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpAnnLine &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpBool &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(exp.value);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpNull &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(nullptr);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpSInt &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(exp.value);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpUInt &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(exp.value);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpFlt32 &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(exp.value);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpFlt64 &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(exp.value);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpChar &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            return std::any(exp.value);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpString &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpThis &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpSuper &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpID &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpFuncCall &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpMemberCall &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpUnary &exp, std::any opt)
    {

        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            auto val = exp.exp->visit(*this, opt);
            // 前置一元操作
            if (exp.preop == true)
            {
                switch (exp.op)
                {
                case TkOpEnum::Plus: //+
                {
                    if (val.type() == typeid(int64_t))
                        return std::abs(std::any_cast<int64_t>(val));
                    if (val.type() == typeid(flt32_t))
                        return std::abs(std::any_cast<flt32_t>(val));
                    if (val.type() == typeid(flt64_t))
                        return std::abs(std::any_cast<flt64_t>(val));
                    return val;
                }
                break;
                case TkOpEnum::Minus: //-
                {
                    if (val.type() == typeid(bool))
                        return -(uint32_t)std::any_cast<bool>(val);
                    if (val.type() == typeid(int32_t))
                        return -std::any_cast<int32_t>(val);
                    if (val.type() == typeid(uint32_t))
                        return -std::any_cast<uint32_t>(val);
                    if (val.type() == typeid(int64_t))
                        return -std::any_cast<int64_t>(val);
                    if (val.type() == typeid(uint64_t))
                        return -std::any_cast<uint64_t>(val);
                    if (val.type() == typeid(flt32_t))
                        return -std::any_cast<flt32_t>(val);
                    if (val.type() == typeid(flt64_t))
                        return -std::any_cast<flt64_t>(val);
                    semanticError(exp.startpos, exp.endpos, "错误的类型");
                }
                break;
                case TkOpEnum::BitNot: //~
                {
                    if (val.type() == typeid(bool))
                        return ~(uint32_t)std::any_cast<bool>(val);
                    if (val.type() == typeid(int32_t))
                        return ~(uint32_t)std::any_cast<int32_t>(val);
                    if (val.type() == typeid(uint32_t))
                        return ~(uint32_t)std::any_cast<uint32_t>(val);
                    if (val.type() == typeid(int64_t))
                        return ~(uint32_t)std::any_cast<int64_t>(val);
                    if (val.type() == typeid(uint64_t))
                        return ~(uint32_t)std::any_cast<uint64_t>(val);

                    semanticError(exp.startpos, exp.endpos, "错误的类型");
                    return val;
                }
                break;
                case TkOpEnum::LogicalNot: //!
                {
                    if (val.type() == typeid(bool))
                        return !(uint32_t)std::any_cast<bool>(val);
                    if (val.type() == typeid(int32_t))
                        return !std::any_cast<int32_t>(val);
                    if (val.type() == typeid(uint32_t))
                        return !std::any_cast<uint32_t>(val);
                    if (val.type() == typeid(int64_t))
                        return !std::any_cast<int64_t>(val);
                    if (val.type() == typeid(uint64_t))
                        return !std::any_cast<uint64_t>(val);
                    if (val.type() == typeid(flt32_t))
                        return !std::any_cast<flt32_t>(val);
                    if (val.type() == typeid(flt64_t))
                        return !std::any_cast<flt64_t>(val);
                    semanticError(exp.startpos, exp.endpos, "错误的类型");
                }
                break;

                default:
                    break;
                }
            }
        }
        }
        return {};
    }
    std::any Symbolization::visit(ExpBinary &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::ExpCalculate:
        {
            auto left = exp.left->visit(*this, opt);
            auto right = exp.right->visit(*this, opt);
            switch (exp.op)
            {
            case TkOpEnum::Plus:
            {
                return std::any_cast<uint64_t>(left) + std::any_cast<uint64_t>(right);
            }
            break;
            case TkOpEnum::Minus:
            {
            }
            break;
            case TkOpEnum::Multiply:
            {
                return std::any_cast<uint64_t>(left) * std::any_cast<uint64_t>(right);
            }
            break;
            case TkOpEnum::Divide:
            {
            }
            break;
            case TkOpEnum::Modulus:
            {
            }
            break;

            default:
                break;
            }
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpTernary &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpParen &exp, std::any opt)
    {
        assert(opt.type() == typeid(SymTabInfo));

        auto symtab = std::any_cast<SymTabInfo>(opt);
        switch (symtab.stage)
        {
        case SymTabInfo::TypeCalculate:
        {
            return exp.exp->visit(*this, opt);
        }
        break;
        case SymTabInfo::ExpCalculate:
        {
            return exp.exp->visit(*this, opt);
        }
        break;
        }
        return {};
    }

    std::any Symbolization::visit(ExpBlock &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpInRange &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpRange &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpArrayIndex &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpCast &exp, std::any opt)
    {
        return {};
    }

    std::any Symbolization::visit(ExpNew &exp, std::any opt)
    {
        return {};
    }
}