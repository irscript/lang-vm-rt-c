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
    // 语法: [const] type ( '[,,]' | '[][]...' ) ( '&' | ('*')* )
    void Parser::getType(AstType &type)
    {
        auto tok = lexer.getNext();
        if (tok.isKeyword(TkKeyWord::Const) == true)
        {
            type.constv = 1;
            tok = lexer.getNext();
        }
        // 基本类型
        if (tok.isTypeKeyword() == true)
        {
            type.name.push_back(pool.refString(tok.txt));
        }
        // 可能是 id.id
        else if (tok.isIdentity() == true)
        {
            while (true)
            {
                type.name.push_back(pool.refString(tok.txt));
                tok = lexer.getNext();
                if (tok.isOperator(TkOpEnum::Dot) == false)
                {
                    lexer.backToken(tok);
                    break;
                }
                tok = lexer.getNext();
                if (tok.isIdentity() == false)
                    syntaxError(tok, "缺少成员名称！");
            }
        }
        // 查看数组定义
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
                return getDeclEnum(scope, startpos);
            case TkKeyWord::Union:
                return getDeclUnion(scope, startpos);
            case TkKeyWord::Struct:
                return getDeclStruct(scope, startpos);
            case TkKeyWord::Entrust:
                return getDeclEntrust(scope, startpos);
            case TkKeyWord::Interface:
                return getDeclInterface(scope, startpos);
            case TkKeyWord::Class:
                return getDeclClass(scope, startpos);
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
            return getDeclFunc(scope, startpos, type, name);
        // 静态数组?
        if (tok.isSeparator(TkSpEnum::OpenBracket) == true)
            return getDeclVar(scope, startpos, type, name, true);
        return getDeclVar(scope, startpos, type, name, false);
    }
    AstDeclRef Parser::getDeclVar(ScopeEnum scope, TokPos &startpos, AstType &type, StringRef &name, bool array)
    {
        DeclVar *var = nullptr;
        auto decl = genDecl(var, name);
        var->startpos = startpos;
        var->type = type;
        var->flag.scope = scope;

        // 解析静态数组维度
        while (array == true)
        {
            var->arrcols.push_back(getExp());
            auto tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::CloseBracket) == false)
                syntaxError(tok, "缺少符号“ ] ”！");
            tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::OpenBracket) == false)
            {
                lexer.backToken(tok);
                break;
            }
        }

        // 查看是否有初始值表达式
        auto tok = lexer.getNext();
        if (tok.isOperator(TkOpEnum::Assign) == true)
        {
            var->init = getExp();
        }
        else
            lexer.backToken(tok);
        var->endpos = lexer.getPos();
        return decl;
    }

    AstDeclRef Parser::getDeclFunc(ScopeEnum scope, TokPos &startpos, AstType &type, StringRef &name)
    {
        DeclFunc *func = nullptr;
        auto decl = genDecl(func, name);
        func->startpos = startpos;
        func->retType = type;
        func->flag.scope = scope;

        // 解析参数列表

        // 解析函数体
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == true)
        {
            func->body = getStmBlock();
        }
        else if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”");

        func->endpos = lexer.getPos();
        return decl;
    }

    AstDeclRef Parser::getDeclEnum(ScopeEnum scope, TokPos &startpos)
    {
        return {};
    }

    AstDeclRef Parser::getDeclStruct(ScopeEnum scope, TokPos &startpos)
    {
        return {};
    }

    AstDeclRef Parser::getDeclUnion(ScopeEnum scope, TokPos &startpos)
    {
        return {};
    }

    AstDeclRef Parser::getDeclEntrust(ScopeEnum scope, TokPos &startpos)
    {
        return {};
    }

    AstDeclRef Parser::getDeclInterface(ScopeEnum scope, TokPos &startpos)
    {
        return {};
    }

    AstDeclRef Parser::getDeclClass(ScopeEnum scope, TokPos &startpos)
    {
        return {};
    }
}