#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    // 解析块表达式
    // 语法：{exp,exp}
    // 语法2：{exp:exp,exp:exp}
    AstExpRef Parser::getExpBlock(TokPos &startpos)
    {
        ExpBlock *blk = nullptr;
        auto result = genExp(blk);
        bool haveId = false; // 存在ID

        auto tok = lexer.getNext();
        // 结束 }
        if (tok.isSeparator(TkSpEnum::CloseBrace) == false)
        {
            lexer.backToken(tok);
            auto exp = getExp();

            tok = lexer.getNext();
            // exp:exp
            if (tok.isSeparator(TkSpEnum::CBSemiColon) == true)
            {
                tok.pos.pos++;
                lexer.backToken(tok);
            }
            else if (tok.isSeparator(TkSpEnum::Colon) == true)
            {
                blk->ids.push_back(exp);
                blk->val.push_back(getExp());

                while (true)
                {
                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::CBSemiColon) == true)
                    {
                        tok.pos.pos++;
                        lexer.backToken(tok);
                        break;
                    }
                    if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                        break;
                    if (tok.isSeparator(TkSpEnum::Comma) == false)
                        syntaxError(tok, "缺少符号“ } ”！");

                    // exp:exp
                    blk->ids.push_back(getExp());

                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::Colon) == false)
                        syntaxError(tok, "缺少符号“ : ”！");

                    blk->val.push_back(getExp());
                }
            }
            else // exp,exp
            {
                lexer.backToken(tok);
                blk->val.push_back(exp);
                while (true)
                {
                    tok = lexer.getNext();
                    if (tok.isSeparator(TkSpEnum::CBSemiColon) == true)
                    {
                        tok.pos.pos++;
                        lexer.backToken(tok);
                        break;
                    }
                    if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                        break;
                    if (tok.isSeparator(TkSpEnum::Comma) == false)
                        syntaxError(tok, "缺少符号“ } ”！");
                    blk->val.push_back(getExp());
                }
            }
        }

        blk->startpos = startpos;
        blk->endpos = lexer.getPos();
        return result;
    }
    // 解析范围表达式
    AstExpRef Parser::getExpRang()
    {
        bool lf = false, rf = false;
        // 开始符
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::OpenBracket) == true)
            lf = true;
        else if (tok.isSeparator(TkSpEnum::OpenBracket) == true)
            lf = false;
        else
            syntaxError(tok, "缺少符号“ [ ”或“ ( ”！");
        auto startpos = tok.pos;
        // 左范围
        AstExpRef lexp = getExpBin(0);

        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::Comma) == false)
            syntaxError(tok, "缺少符号“ , ”！");
        // 右范围
        AstExpRef rexp = getExpBin(0);
        // 结束符
        tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::CloseBracket) == true)
            rf = true;
        else if (tok.isSeparator(TkSpEnum::CloseBracket) == true)
            rf = false;
        else
            syntaxError(tok, "缺少符号“ ] ”或“ ) ”！");

        ExpRange *exp = nullptr;
        auto result = genExp(exp, lexp, rexp, lf, rf);
        exp->startpos = startpos;
        exp->endpos = tok.pos;
        return result;
    }
    // 解析基础表达式
    AstExpRef Parser::getExpBase()
    {
        auto tok = lexer.getNext();
        auto startpos = tok.pos;

        // 注解关键字
        if (tok.isAnnotate() == true)
        {
            switch (tok.code.ann)
            {
            case TkAnnotate::File:
            {
                ExpAnnFile *exp;
                auto result = genExp(exp);
                exp->startpos = startpos;
                exp->endpos = lexer.getPos();
                return result;
            }
            break;
            case TkAnnotate::Func:
            {
                ExpAnnFunc *exp;
                auto result = genExp(exp);
                exp->startpos = startpos;
                exp->endpos = lexer.getPos();
                return result;
            }
            break;
            case TkAnnotate::Line:
            {
                ExpAnnLine *exp;
                auto result = genExp(exp);
                exp->startpos = startpos;
                exp->endpos = lexer.getPos();
                exp->line = tok.pos.line;
                return result;
            }
            break;
            default:
                syntaxError(tok, "缺少表达式！");
                break;
            }
        }

        // 标识符
        // 可能是普通成员、数组成员、函数调用
        if (tok.isIdentity() == true)
        {
            auto tok2 = lexer.getNext();
            // 函数调用
            if (tok2.isSeparator(TkSpEnum::OpenParen) == true)
            {
                ExpFuncCall *fun = nullptr;
                auto result = genExp(fun, pool.refString(tok.txt));
                getExpFunc(*fun);
                fun->startpos = startpos;
                return result;
            }
            // 数组访问
            if (tok2.isSeparator(TkSpEnum::OpenBracket) == true)
            {
                ExpArrayIndex *array = nullptr;
                auto result = genExp(array, pool.refString(tok.txt));
                getExpArray(*array);
                array->startpos = startpos;
                return result;
            }
            // 成员变量
            lexer.backToken(tok2);
            ExpID *id = nullptr;
            auto result = genExp(id, pool.refString(tok.txt));
            id->startpos = startpos;
            id->endpos = lexer.getPos();
            return result;
        }
        // this 表达式
        if (tok.isKeyword(TkKeyWord::This) == true)
        {
            ExpThis *exp = nullptr;
            auto result = genExp(exp);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // super 表达式
        if (tok.isKeyword(TkKeyWord::Super) == true)
        {
            ExpSuper *exp = nullptr;
            auto result = genExp(exp);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // false 表达式
        if (tok.isKeyword(TkKeyWord::False) == true)
        {
            ExpBool *exp = nullptr;
            auto result = genExp(exp, false);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // true 表达式
        if (tok.isKeyword(TkKeyWord::True) == true)
        {
            ExpBool *exp = nullptr;
            auto result = genExp(exp, true);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // null 表达式
        if (tok.isKeyword(TkKeyWord::Null) == true)
        {
            ExpNull *exp = nullptr;
            auto result = genExp(exp);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        //(exp)括号表达式
        if (tok.isSeparator(TkSpEnum::OpenParen) == true)
        {
            auto res = getExp();
            ExpParen *exp = nullptr;
            auto result = genExp(exp, res);
            exp->startpos = startpos;
            tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::CloseParen) == false)
                syntaxError(tok, "缺少符号“ ) ”");
            exp->endpos = lexer.getPos();
            return result;
        }
        // 字符常量
        if (tok.kind == TkKind::CharLiteral)
        {
            ExpChar *exp = nullptr;
            auto result = genExp(exp, tok.val.i32);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // 有符号常量
        if (tok.kind == TkKind::SIntLiteral)
        {
            ExpSInt *exp = nullptr;
            auto result = genExp(exp, tok.val.i64);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        } // 无符号常量
        if (tok.kind == TkKind::UIntLiteral)
        {
            ExpUInt *exp = nullptr;
            auto result = genExp(exp, tok.val.i64);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        } // 32位浮点常量
        if (tok.kind == TkKind::Flt32Literal)
        {
            ExpFlt32 *exp = nullptr;
            auto result = genExp(exp, tok.val.f32);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        } // 64位浮点常量
        if (tok.kind == TkKind::Flt64Literal)
        {
            ExpFlt64 *exp = nullptr;
            auto result = genExp(exp, tok.val.f64);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // 字符串常量
        if (tok.kind == TkKind::StringLiteral)
        {
            ExpString *exp = nullptr;
            auto result = genExp(exp, tok.txt);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }
        // 字符串常量
        if (tok.kind == TkKind::StringLiteral2)
        {
            ExpString *exp = nullptr;
            auto result = genExp(exp, tok.txt);
            exp->startpos = startpos;
            exp->endpos = lexer.getPos();
            return result;
        }

        syntaxError(tok, "缺少表达式！");
        return AstExpRef();
    }
    // 数组
    // 语法：id[exp][exp][...]
    void Parser::getExpArray(ExpArrayIndex &exp)
    {
        while (true)
        {
            auto index = getExp();
            exp.indexs.push_back(index);
            auto tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::CloseBracket) == false)
                syntaxError(tok, "缺少符号“ ] ”!");
            tok = lexer.getNext();
            if (tok.isSeparator(TkSpEnum::OpenBracket) == false)
            {
                lexer.backToken(tok);
                break;
            }
        }
        exp.endpos = lexer.getPos();
    }
    // 解析函数调用
    // 语法：id(exp,exp,...)
    void Parser::getExpFunc(ExpFuncCall &exp)
    {
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::CloseParen) == false)
        {
            lexer.backToken(tok);
            while (true)
            {
                auto arg = getExp();
                exp.args.push_back(arg);
                tok = lexer.getNext();
                if (tok.isSeparator(TkSpEnum::Comma) == true)
                    continue;
                else if (tok.isSeparator(TkSpEnum::CloseParen) == true)
                    break;
                syntaxError(tok, "缺少符号“ ) ”!");
            }
        }
        exp.endpos = lexer.getPos();
    }
    // 解析一元表达式
    AstExpRef Parser::getExpUna()
    {
        auto tok = lexer.getNext();
        // 前置一元操作符
        if (tok.kind == TkKind::Operator)
        {
            // 普通一元操作符
            if (tok.code.op == TkOpEnum::Plus ||       // +
                tok.code.op == TkOpEnum::Plus2 ||      // ++
                tok.code.op == TkOpEnum::Minus ||      // -
                tok.code.op == TkOpEnum::Minus2 ||     // --
                tok.code.op == TkOpEnum::LogicalNot || // !
                tok.code.op == TkOpEnum::BitNot        // ~
            )
            {
                auto exp = getExpUna();
                ExpUnary *unary = nullptr;
                auto result = genExp(unary, exp, tok.code.op, true);
                unary->startpos = tok.pos;
                unary->endpos = lexer.getPos();
                return result;
            }
            // 特殊
            if (
                tok.code.op == TkOpEnum::BitAnd || // & 取址
                tok.code.op == TkOpEnum::Multiply  // * 取值
            )
            {
            }
        }
        lexer.backToken(tok);
        // 获取基础表达式
        auto exp = getExpBase();
        // 后置一元操作
        auto tok2 = lexer.getNext();
        if (tok2.isOperator(TkOpEnum::Plus2) == true ||
            tok2.isOperator(TkOpEnum::Minus2) == true)
        {
            ExpUnary *unary = nullptr;
            auto result = genExp(unary, exp, tok2.code.op, false);
            unary->startpos = exp->startpos;
            unary->endpos = lexer.getPos();
            return result;
        }
        // 成员调用
        if (tok2.isOperator(TkOpEnum::Dot) == true)
        {
            switch (exp->getKind())
            {
            case ExpKind::Identity:
            case ExpKind::FunCall:
            case ExpKind::Array:
            case ExpKind::This:
            case ExpKind::Super:
            {
                ExpMemberCall *mcall = nullptr;
                auto result = genExp(mcall);
                mcall->items.push_back(exp);
                mcall->startpos = exp->startpos;
                while (true)
                {
                    tok2 = lexer.getNext();
                    if (tok2.isOperator(TkOpEnum::Dot) == false)
                    {
                        lexer.backToken(tok2);
                        break;
                    }
                    auto sub = getExpBase();
                    switch (sub->getKind())
                    {
                    case ExpKind::Identity:
                    case ExpKind::FunCall:
                    case ExpKind::Array:
                    {
                        mcall->items.push_back(sub);
                        continue;
                    }
                    break;

                    default:
                        syntaxError(tok2, "非法成员调用！");
                        break;
                    }
                }
            }
            break;

            default:
                syntaxError(tok2, "非法成员调用！");
                break;
            }
        }
        // 范围表达式
        if (tok2.isKeyword(TkKeyWord::In) == true)
        {
            auto tok = lexer.getNext();
            bool neg = false;
            if (tok.isOperator(TkOpEnum::LogicalNot) == false)
                lexer.backToken(tok);
            else
                neg = true;
            auto range = getExpRang();
            ExpInRange *inexp = nullptr;
            auto result = genExp(inexp, neg, exp, range);
            inexp->startpos = exp->startpos;
            inexp->endpos = lexer.getPos();
            return result;
        }
        // 就是基本表达式
        lexer.backToken(tok2);
        return exp;
    }
    // 解析二元表达式
    AstExpRef Parser::getExpBin(int32_t priority)
    {
        // 1.先解析一个一元表达式
        auto left = getExpUna();
        // 获取操作符
        auto tok = lexer.getNext();
        if (tok.isOperator() == false)
        {
            lexer.backToken(tok);
            return left;
        }
        int32_t cur_pri = tok.getBinopPriority(); // 当前优先级
        // 不是二元操作符
        if (cur_pri == -1)
        {
            // 三元表达式
            if (tok.isOperator(TkOpEnum::Ques) == true)
                return getExpTer(left);
            // 非二元表达式
            lexer.backToken(tok);
            return left;
        }
        auto cur_op = tok.code.op; // 当前操作符

        while (cur_pri > priority)
        {
            auto right = getExpBin(cur_pri);
            ExpBinary *bin = nullptr;
            auto exp = genExp(bin, left, right, cur_op);
            exp->startpos = left->startpos;
            exp->endpos = left->endpos;

            left = exp;

            tok = lexer.getNext();
            if (tok.isOperator() == false)
            {
                lexer.backToken(tok);
                break;
            }
            cur_op = tok.code.op;             // 当前操作符
            cur_pri = tok.getBinopPriority(); // 当前优先级
            // 不是二元操作符
            if (cur_pri == -1)
            {
                lexer.backToken(tok);
                break;
            }
        }

        return left;
    }
    // 解析三元表达式
    AstExpRef Parser::getExpTer(AstExpRef &cond)
    {
        ExpTernary *ter = nullptr;
        auto result = genExp(ter, cond);
        ter->startpos = cond->startpos;
        ter->result = getExp();
        auto tok = lexer.getNext();
        if (tok.isSeparator(TkSpEnum::Colon) == false)
            syntaxError(tok, "缺少符号“ : ”");
        ter->result2 = getExp();
        ter->endpos = lexer.getPos();
        return result;
    }
}