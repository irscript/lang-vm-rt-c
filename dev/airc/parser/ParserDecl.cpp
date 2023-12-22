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
    // 语法: [const] type ( '[,,]' | '[][]...' |  ('*')* )
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
            tok = lexer.getNext();
        }
        // 可能是 id.id
        else if (tok.isIdentity() == true)
        {
            while (true)
            {
                type.name.push_back(pool.refString(tok.txt));
                tok = lexer.getNext();
                if (tok.isOperator(TkOpEnum::Dot) == false)
                    break;
                tok = lexer.getNext();
                if (tok.isIdentity() == false)
                    syntaxError(tok, "缺少成员名称！");
            }
        }
        // 查看数组定义
        if (tok.isSeparator(TkSpEnum::OpenBracket) == true)
        {
            tok = lexer.getNext();
            // 块数组
            if (tok.isSeparator(TkSpEnum::Comma) == true)
            {
                uint32_t col = 2;
                while (true)
                {
                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::Comma) == true)
                    {
                        ++col;
                        continue;
                    }
                    if (tok.isSeparator(TkSpEnum::CloseBracket) == true)
                        break;
                    syntaxError(tok, "缺少符号“ ] ”！");
                }
                type.array = 1;
                type.block = 1;
                type.cols = col;

                tok = lexer.getNext(); // 为解析指针预读
            }
            // 动态数组
            else if (tok.isSeparator(TkSpEnum::CloseBracket) == true)
            {
                uint32_t col = 1;
                while (true)
                {
                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::OpenBracket) == true)
                    {
                        ++col;
                        tok = lexer.getNext();
                    }
                    else
                    {
                        // lexer.backToken(tok);//为解析指针预读
                        break;
                    }
                    if (tok.isSeparator(TkSpEnum::CloseBracket) == true)
                        continue;
                    syntaxError(tok, "缺少符号“ ] ”！");
                }
                type.array = 1;
                type.block = col == 1;
                type.cols = col;
            }
            else
                syntaxError(tok, "缺少符号“ ] ”！");
        }
        // 查看是否是指针
        if (tok.isOperator(TkOpEnum::Multiply) == true)
        {
            type.pointer = 1;
            uint32_t ptrs = 1;
            while (true)
            {
                tok = lexer.getNext();
                if (tok.isOperator(TkOpEnum::Multiply) == false)
                    break;
                ++ptrs;
            }
            type.ptrs = ptrs;
        }
        lexer.backToken(tok);
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
        lexer.backToken(tok);
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
        // 查看是否同行定义变量
        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::Comma) == true)
        {
            // 解析名称
            tok = lexer.getNext();
            if (tok.isIdentity() == false)
                syntaxError(tok, "缺少名称！");
            StringRef name = pool.refString(tok.txt);
            auto startpos = tok.pos;

            tok = lexer.getNext();
            bool array = false;
            // 静态数组?
            if (tok.isSeparator(TkSpEnum::OpenBracket) == true)
                array = true;
            else
                lexer.backToken(tok);
            var->nextvar = getDeclVar(scope, startpos, type, name, array);
        }
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");
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
        getDeclFunParam(*func);
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
    // 语法：'(' (type id ann, )* ')'
    void Parser::getDeclFunParam(DeclFunc &func)
    {
        Token tok;
        while (true)
        {
            tok = lexer.getNext();
            // ) 结束
            if (tok.isSeparator(TkSpEnum::CloseParen) == true)
                return;
            lexer.backToken(tok);
            auto startpos = lexer.getPos();
            // 解析类型
            AstType type;
            getType(type);
            // 解析名称
            tok = lexer.getNext();
            if (tok.isIdentity() == false)
                syntaxError(tok, "缺少参数名称！");
            StringRef name = pool.refString(tok.txt);
            DeclVar *var = nullptr;
            auto arg = genDecl(var, name);
            var->startpos = startpos;
            var->type = type;
            var->flag.arg = 1;

            tok = lexer.getNext();

            // 存在注解
            while (tok.isAnnotate() == true)
            {
                var->anns.push_back(getAnn(tok));
                tok = lexer.getNext();
            }
            // 记录结束位置
            var->endpos = lexer.getPos();
            func.args.push_back(arg);
            // 逗号 ，
            if (tok.isSeparator(TkSpEnum::Comma) == true)
                continue;
            // ) 结束
            if (tok.isSeparator(TkSpEnum::CloseParen) == true)
                return;
            syntaxError(tok, "缺少符号“ ) ”！");
        }
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