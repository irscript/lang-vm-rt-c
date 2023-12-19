#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    // 开始解析
    void Parser::start()
    {
        // 获取包名
        getPackage();
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
                throw ErrorWhat::fmt("缺少标识符！\n%s\n", tok.toString().c_str());
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
        unit.package = szPkg;
    }
    // 解析依赖
    // 语法1 require id="file.ext";
    // 语法2 require{ id="file.ext"; }
    void Parser::getRequire() {}
}