#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    // 开始解析
    void Parser::start()
    {
        // 获取包名
        getPackage();
        // 获取依赖
        getRequire();
    }

    // 解析包名
    // 语法 package id [.id]*;
    void Parser::getPackage()
    {
        auto tok = lexer.getNext();
        if (tok.isKeyword(TkKeyWord::Package) == false)
            throw ErrorWhat::fmt("缺少包声明！\n%s\n", tok.toString().c_str());
        std::string szPkg;
        while (true)
        {
            tok = lexer.getNext();
            if (tok.isIdentity() == false)
                throw ErrorWhat::fmt("缺少包名！\n%s\n", tok.toString().c_str());
            szPkg += tok.txt;
            tok = lexer.getNext();
            if (tok.isOperator(TkOpEnum::Dot) == true)
            {
                szPkg.push_back('.');
                continue;
            }
            if (tok.isSeparator(TkSpEnum::SemiColon) == true)
                break;
            throw ErrorWhat::fmt("缺少符号“ ; ”！\n%s\n", tok.toString().c_str());
        }
        unit.package = pool.refString(szPkg);
    }
    // 解析依赖
    // 语法1 require id="file.ext";
    // 语法2 require{ id="file.ext"; }
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
            if (tok.isIdentity() == true)
            {
                lexer.backToken(tok);
                getRequireItem();
                continue;
            }
            if (tok.isSeparator(TkSpEnum::OpenBrace) == true)
            {
                while (true)
                {
                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                        return;
                    lexer.backToken(tok);
                    getRequireItem();
                }
            }
            throw ErrorWhat::fmt("缺少依赖名！\n%s\n", tok.toString().c_str());
        }
    }
    // 语法 id="string";
    void Parser::getRequireItem()
    {
        // 跳过空白字符
        lexer.SkipWhiteSpaces();

        auto startpos = lexer.getPos(); // 起始位置
        std::string szFile, szName;

        auto tok = lexer.getNext();
        if (tok.isIdentity() == false)
            throw ErrorWhat::fmt("缺少依赖名！\n%s\n", tok.toString().c_str());
        szName = tok.txt;

        tok = lexer.getNext();
        if (tok.isOperator(TkOpEnum::Assign) == false)
            throw ErrorWhat::fmt("缺少符号“ = ”！\n%s\n", tok.toString().c_str());

        tok = lexer.getNext();
        if (tok.isString() == false)
            throw ErrorWhat::fmt("缺少文件路径！\n%s\n", tok.toString().c_str());
        szFile = tok.txt;
        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            throw ErrorWhat::fmt("缺少符号“ ; ”！\n%s\n", tok.toString().c_str());

        // 生成声明
        DeclFile *decl = nullptr;
        auto node = genDecl(decl, pool.refString(szName), pool.refString(szFile));
        unit.declist.push_back(node);
        decl->startpos = startpos;
        decl->endpos = lexer.getPos();
        FileSymbol *sym;
        // 插入符号
        auto symref = genSymbol(sym, *decl);
        auto res = unit.symbols.insert(&decl->name.get(), symref);
        if (res.first == false)
        {
            std::string src = lexer.getSub(decl->startpos.pos, decl->endpos.pos);
            Print("当前定义：\n%s\n", src.c_str());
            throw ErrorWhat::fmt("符号名称冲突！\n");
        }
    }
}