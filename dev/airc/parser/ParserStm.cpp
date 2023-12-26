#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    AstStmRef Parser::getStmBlock(AstStmRef result)
    {
        StmBlock *blk = (StmBlock *)result.get();
        if (result.get() == nullptr)
            result = genStm(blk);

        Token tok;
        // 注解
        std::vector<AstAnnRef> anns;
        while (true)
        {
            tok = lexer.getNext();
            // } 结束
            if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                break;
            // 无意义的分号
            if (tok.isSeparator(TkSpEnum::SemiColon) == true)
                continue;
            // 普通块语句
            if (tok.isSeparator(TkSpEnum::OpenBrace) == true)
            {
                StmBlock *stm = nullptr;
                auto result = genStm(stm, BlockKind::Normal);
                stm->startpos = tok.pos;
                blk->stms.push_back(getStmBlock(result));
                continue;
            }
            anns.clear();
            // 注解
            while (tok.isAnnotate() == true)
            {
                anns.push_back(getAnn(tok));
                tok = lexer.getNext();
            }
            // 关键字
            if (tok.isKeyword() == true)
            {
                switch (tok.code.key)
                {
                case TkKeyWord::If:
                    blk->stms.push_back(getStmIf(tok.pos, anns));
                    continue;
                case TkKeyWord::Elsif:
                    blk->stms.push_back(getStmElsif(tok.pos, anns));
                    continue;
                case TkKeyWord::Else:
                    blk->stms.push_back(getStmElse(tok.pos, anns));
                    continue;

                case TkKeyWord::Switch:
                    blk->stms.push_back(getStmIf(tok.pos, anns));
                    continue;
                    /*  case TkKeyWord::Case:
                          blk->stms.push_back(getStmIf(tok.pos, anns));
                          continue;
                      case TkKeyWord::Default:
                          blk->stms.push_back(getStmIf(tok.pos, anns));
                          continue;*/

                case TkKeyWord::For:
                    blk->stms.push_back(getStmFor(tok.pos, anns));
                    continue;
                case TkKeyWord::While:
                    blk->stms.push_back(getStmWhile(tok.pos, anns));
                    continue;
                case TkKeyWord::Do:
                    blk->stms.push_back(getStmDoWhile(tok.pos, anns));
                    continue;

                case TkKeyWord::Try:
                    blk->stms.push_back(getStmTry(tok.pos, anns));
                    continue;
                /*case TkKeyWord::Catch:
                    blk->stms.push_back(getStmCatch(tok.pos, anns));
                    continue;
                case TkKeyWord::Finally:
                    blk->stms.push_back(getStmFinally(tok.pos, anns));
                    continue;*/
                case TkKeyWord::Throw:
                    blk->stms.push_back(getStmThrow(tok.pos, anns));
                    continue;

                case TkKeyWord::Goto:
                    blk->stms.push_back(getStmGoto(tok.pos, anns));
                    continue;
                case TkKeyWord::Break:
                    blk->stms.push_back(getStmBreak(tok.pos, anns));
                    continue;
                case TkKeyWord::Continue:
                    blk->stms.push_back(getStmContinue(tok.pos, anns));
                    continue;
                case TkKeyWord::Return:
                    blk->stms.push_back(getStmReturn(tok.pos, anns));
                    continue;
                }
            }
            // 标签定义？
            if (tok.isIdentity() == true)
            {
                auto tok2 = lexer.getNext();
                if (tok2.isSeparator(TkSpEnum::Colon) == true)
                {
                    StmLabel *label = nullptr;
                    auto result = genStm(label, pool.refString(tok.txt));
                    label->startpos = tok.pos;
                    label->endpos = tok2.pos;
                    blk->stms.push_back(result);
                    continue;
                }
                lexer.backToken(tok2);
            }
            // 表达式语句 ？ 变量定义语句 ？
            lexer.backToken(tok);
            blk->stms.push_back(getStmVar(anns));
        }
        blk->endpos = lexer.getPos();
        return result;
    }
    AstStmRef Parser::getStmVar(const std::vector<AstAnnRef> &anns)
    {
        auto tok = lexer.getNext();

        // 必须是变量定义
        if (tok.isKeyword(TkKeyWord::Const) == true || tok.isTypeKeyword() == true)
            goto _VarStm_;
        // 假定是表达式语句
        if (tok.isIdentity() == true)
        {
            lexer.backToken(tok);
            auto exp = getExp();
            switch (exp->getKind())
            {

            case ExpKind::MemberCall:
            {
                ExpMemberCall &mcall = *(ExpMemberCall *)exp.get();

                // 确保内部只有ID
                bool fexp = false;
                for (auto item : mcall.items)
                {
                    if (item->getKind() != ExpKind::Identity)
                    {
                        fexp = true;
                        break;
                    }
                }
                // 确定是表达式语句
                if (fexp == true)
                    goto _ExpStm;
                // 否则就需要进行下一步判断
            }
            case ExpKind::Identity:
            {
                auto tok2 = lexer.getNext();
                // 可能是变量定义
                if (tok.isSeparator(TkSpEnum::Comma) == false &&
                    tok.isSeparator(TkSpEnum::Comma) == false)
                    goto _VarStm_;
                else
                    goto _ExpStm; // 确定是表达式语句
            }
            break;
            // 必须是逗号表达式
            default:
                goto _ExpStm;
            }
        }
        // 就是表达式
    _ExpStm:
    {
        lexer.backToken(tok);
        StmExp *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = lexer.getPos();
        stm->anns = anns;

        stm->exp.push_back(getExp());
        while (true)
        {
            tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::SemiColon))
                break;
            if (tok.isSeparator(TkSpEnum::Comma))
            {
                stm->exp.push_back(getExp());
                continue;
            }
            syntaxError(tok, "缺少符号“ ; ”！");
        }

        stm->endpos = lexer.getPos();
        return result;
    }

    // 取保是变量定义语句
    _VarStm_:
        lexer.backToken(tok);
        StmVar *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = lexer.getPos();
        stm->anns = anns;
        // 解析类型
        AstType type;
        getType(type);
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
        stm->vardef = getDeclVar(ScopeEnum::Public, startpos, type, name, array);
        stm->endpos = lexer.getPos();
        return result;
    }

    // 语法：goto label;
    AstStmRef Parser::getStmGoto(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        auto tok = lexer.getNext();
        if (tok.isIdentity() == false)
            syntaxError(tok, "缺少标签名！");
        auto tok2 = lexer.getNext();
        if (tok2.isSeparator(TkSpEnum::Colon) == false)
            syntaxError(tok2, "缺少符号“ : ”！");
        StmGoto *stm = nullptr;
        auto result = genStm(stm, pool.refString(tok.txt));
        stm->startpos = startpos;
        stm->anns = anns;
        stm->endpos = lexer.getPos();
        return result;
    } // 语法：break;
    AstStmRef Parser::getStmBreak(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");
        StmBreak *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法：continue;
    AstStmRef Parser::getStmContinue(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");
        StmContinue *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法：return [exp];
    AstStmRef Parser::getStmReturn(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmReturn *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
        {
            lexer.backToken(tok);
            stm->exp = getExp();
            tok = lexer.getNext();
        }
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： if exp {}
    AstStmRef Parser::getStmIf(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmIf *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        stm->cond = getExp();

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    } // 语法： elsif exp {}
    AstStmRef Parser::getStmElsif(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmElsif *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        stm->cond = getExp();

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    } // 语法： else {}
    AstStmRef Parser::getStmElse(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmElse *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： switch exp {}
    AstStmRef Parser::getStmSwitch(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmSwitch *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        stm->cond = getExp();

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        while (true)
        {
            tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                break;
            if (tok.isKeyword(TkKeyWord::Case) == true)
                stm->cases.push_back(getStmCase(tok.pos, {}));
            else if (tok.isKeyword(TkKeyWord::Default) == true)
            {
                stm->defaults = getStmDefault(tok.pos, {});
                tok = lexer.getNext();
                if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                    break;
            }
            syntaxError(tok, "缺少符号“ } ”！");
        }
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： case exp {}
    AstStmRef Parser::getStmCase(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmCase *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        stm->cond = getExp();

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： default {}
    AstStmRef Parser::getStmDefault(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmDefault *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： for (exp;exp;exp) {}
    AstStmRef Parser::getStmFor(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmFor *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenParen) == false)
            syntaxError(tok, "缺少符号“ ( ”！");

        stm->init = getStmVar({}); // 初始语句
        stm->cond = getStmVar({}); // 条件语句

        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::CloseParen) == false)
        {
            lexer.backToken(tok);
            StmExp *stmexp = nullptr;
            stm->finish = genStm(stmexp);
            stmexp->startpos = lexer.getPos();
            stmexp->anns = anns;

            stmexp->exp.push_back(getExp());
            while (true)
            {
                tok = lexer.getNext();
                if (tok.isSeparator(TkSpEnum::CloseParen))
                    break;
                if (tok.isSeparator(TkSpEnum::Comma))
                {
                    stmexp->exp.push_back(getExp());
                    continue;
                }
                syntaxError(tok, "缺少符号“ ) ”！");
            }
            stmexp->endpos = lexer.getPos();
        }

        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： do{}while exp;
    AstStmRef Parser::getStmDoWhile(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmDoWhile *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");

        getStmBlock(result);

        tok = lexer.getNext();
        if (tok.isKeyword(TkKeyWord::While) == false)
            syntaxError(tok, "缺少符号“ while ”！");

        stm->cond = getExp();

        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");

        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： while exp {}
    AstStmRef Parser::getStmWhile(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmWhile *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        stm->cond = getExp();

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： try{}
    AstStmRef Parser::getStmTry(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmTry *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        while (true)
        {
            tok = lexer.getNext();
            if (tok.isKeyword(TkKeyWord::Catch) == true)
            {
                stm->catchs.push_back(getStmCatch(tok.pos, {}));
                continue;
            }
            else if (tok.isKeyword(TkKeyWord::Finally) == true)
                stm->finallys = getStmFinally(tok.pos, {});
            else
                lexer.backToken(tok);

            break;
        }
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： catch( type var) {}
    AstStmRef Parser::getStmCatch(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmCatch *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenParen) == false)
            syntaxError(tok, "缺少符号“ ( ”！");

        getType(stm->type);

        tok = lexer.getNext();
        if (tok.isIdentity() == false)
            syntaxError(tok, "缺少名称！");

        stm->name = pool.refString(tok.txt);

        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::CloseParen) == false)
            syntaxError(tok, "缺少符号“ ) ”！");

        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： finally {}
    AstStmRef Parser::getStmFinally(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmFinally *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;

        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBrace) == false)
            syntaxError(tok, "缺少符号“ { ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }
    // 语法： trow exp ;
    AstStmRef Parser::getStmThrow(TokPos &startpos, const std::vector<AstAnnRef> &anns)
    {
        StmThrow *stm = nullptr;
        auto result = genStm(stm);
        stm->startpos = startpos;
        stm->anns = anns;
        stm->exp = getExp();
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::SemiColon) == false)
            syntaxError(tok, "缺少符号“ ; ”！");
        getStmBlock(result);
        stm->endpos = lexer.getPos();
        return result;
    }

}