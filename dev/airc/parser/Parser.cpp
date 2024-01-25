#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    // 开始解析
    void Parser::start()
    {
        unit.parsed=1;
        // 解析包名
        getPackage();
        // 解析依赖
        getRequire();
        // 解析声明
        Token tok;
        std::vector<AstAnnRef> anns;
        while (true)
        {

            tok = lexer.getNext();
            // 流结束
            if (tok.kind == TkKind::EOS)
                break;
            // 多余的分号
            if (tok.isSeparator(TkSpEnum::SemiColon) == true)
                continue;
            // 注解
            while (tok.isAnnotate() == true)
            {
                anns.push_back(getAnn(tok));
                tok = lexer.getNext();
            }
            lexer.backToken(tok);
            // 获取声明
            auto decl = getDecl();
            decl->anns = anns; // 记录标注
            unit.declist.push_back(decl);
            anns.clear();
        }
    }

    void Parser::repeatSymbol(ISymbol *cur, ISymbol *pre)
    {
        std::string src = lexer.getLineTxt(cur->startpos.line,
                                           cur->startpos.pos,
                                           cur->endpos.pos);
        Printer::lock();
        Printer::print(Printer::Yellow, "\n当前定义：\n");
        Printer::print(Printer::Aqua, "%s\n", src.c_str());

        src = lexer.getLineTxt(pre->startpos.line,
                               pre->startpos.pos,
                               pre->endpos.pos);

        Printer::print(Printer::FaintYellow, "\n前一个定义：\n");
        Printer::print(Printer::Aqua, "%s\n", src.c_str());
        Printer::unlock();
        throw ErrorWhat::fmt("符号名称( %s )冲突！\n", pre->getName().get().c_str());
    }
    void Parser::syntaxError(Token &tok, const char *msg)
    {
        std::string src = lexer.getLineTxt(tok.pos.line,
                                           tok.pos.pos,
                                           tok.pos.pos + tok.txt.size());
        Printer::lock();
        Printer::print(Printer::FaintYellow, "\n当前位置：\n");
        Printer::print(Printer::Aqua, "%s\n", src.c_str());
        Printer::unlock();
        throw ErrorWhat::fmt("%s\n", msg);
    }
    // 解析包名
    // 语法 package id [.id]*;
    void Parser::getPackage()
    {
        auto tok = lexer.getNext();
        if (tok.isKeyword(TkKeyWord::Package) == false)
            syntaxError(tok, "缺少包声明！");

        std::string szPkg;
        while (true)
        {
            tok = lexer.getNext();
            if (tok.isIdentity() == false)
                syntaxError(tok, "缺少包名！");

            szPkg += tok.txt;
            tok = lexer.getNext();
            if (tok.isOperator(TkOpEnum::Dot) == true)
            {
                szPkg.push_back('.');
                continue;
            }
            if (tok.isSeparator(TkSpEnum::SemiColon) == true)
                break;
            syntaxError(tok, "缺少符号“ ; ”！");
        }
        unit.package = pool.refString(szPkg);
    }
    // 解析依赖
    // 语法1 require "file.ext";
    // 语法2 require{ "file.ext"; }
    void Parser::getRequire()
    {
        while (true)
        {
            auto tok = lexer.getNext();
            if (tok.isKeyword(TkKeyWord::Require) == false)
            {
                lexer.backToken(tok);
                return;
            }
            tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::OpenBrace) == true)
            {
                while (true)
                {
                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                        break;
                    lexer.backToken(tok);
                    getRequireItem();
                }
                continue;
            }
            lexer.backToken(tok);
            getRequireItem();
            continue;
        }
    }
    // 语法 "string";
    void Parser::getRequireItem()
    {
        // 跳过空白字符
        lexer.SkipWhiteSpaces();

        auto startpos = lexer.getPos(); // 起始位置
        std::string szFile, szName;

        auto tok = lexer.getNext();
        
        if (tok.isString() == false)
            syntaxError(tok, "缺少文件路径！");
        szFile = tok.txt;
        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");

        // 生成声明
        DeclFile *decl = nullptr;
        auto fileRef = pool.refString(szFile);
        deps.insert(fileRef);
        auto node = genDecl(decl, fileRef);
        unit.declist.push_back(node);
        decl->startpos = startpos;
        decl->endpos = tok.pos; // lexer.getPos();

        unit.depset.insert(fileRef);
        /* FileSymbol *sym;
         // 插入符号
         auto symref = genSymbol(sym, *decl);
         sym->startpos = decl->startpos;
         sym->endpos = decl->endpos;
         auto res = unit.symbols.insert(&decl->name.get(), symref);
         // 符号重复
         if (res.first == false)
             repeatSymbol(sym, res.second.get());*/
    }
}