#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    // 解析作用域描述
    ScopeEnum Parser::getScope()
    {
        auto tok = lexer.getNext();
        if (tok.isKeyword() == true)
        {
            switch (tok.code.key)
            {
            case TkKeyWord::Public:
                return ScopeEnum::Public;
            case TkKeyWord::Protected:
                return ScopeEnum::Protected;
            case TkKeyWord::Private:
                return ScopeEnum::Private;
            }
        }
        lexer.backToken(tok);
        return ScopeEnum::Public;
    }

    void Parser::getType(AstType &type)
    {
    }

    AstDeclRef Parser::getDecl()
    {
        auto scope = getScope(); // 获取作用域描述

        auto tok = lexer.getNext();
        auto startpos = tok.pos;
        if (tok.isKeyword() == true)
        {
            switch (tok.code.key)
            {
            case TkKeyWord::Enum:
            case TkKeyWord::Union:
            case TkKeyWord::Struct:
            case TkKeyWord::Entrust:
            case TkKeyWord::Interface:
            case TkKeyWord::Class:
                break;
            }
        }
        lexer.backToken(tok);
        // 解析类型
        AstType type;
        getType(type);
        // 解析名称
        tok = lexer.getNext();
        if (tok.isIdentity() == false)
            syntaxError(tok, "缺少名称！");
        StringRef name = pool.refString(tok.txt);
        // 判断函数？
        tok = lexer.getNext();
        // 函数
        if (tok.isSeparator(TkSpEnum::OpenParen) == true)
        {
        }
        return {};
    }
}