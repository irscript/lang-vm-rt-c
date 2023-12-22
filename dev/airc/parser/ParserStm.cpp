#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    AstStmRef Parser::getStmBlock()
    {
        StmBlock *blk = nullptr;
        auto result = genStm(blk);
        Token tok;
        while (true)
        {
            tok = lexer.getNext();
            // } 结束
            if (tok.isSeparator(TkSpEnum::CloseBrace) == true)
                break;
            // 无意义的分号
            if (tok.isSeparator(TkSpEnum::SemiColon) == true)
                continue;
            // 关键字
            if (tok.isKeyword() == true)
            {
                switch (tok.code.key)
                {
                case TkKeyWord::If:
                    getStmIf(tok.pos);
                    break;
                }
            }
            // 变量定义
        }
        return result;
    }
    AstStmRef Parser::getStmVar(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmExp(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmLable(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmGoto(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmBreak(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmContinue(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmReturn(TokPos &startpos)
    {
        return {};
    }

    AstStmRef Parser::getStmIf(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmElsif(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmElse(TokPos &startpos)
    {
        return {};
    }

    AstStmRef Parser::getStmSwitch(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmCase(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmDefault(TokPos &startpos)
    {
        return {};
    }

    AstStmRef Parser::getStmFor(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmDoWhile(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmWhile(TokPos &startpos)
    {
        return {};
    }

    AstStmRef Parser::getStmTry(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmCatch(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmFinally(TokPos &startpos)
    {
        return {};
    }
    AstStmRef Parser::getStmThrow(TokPos &startpos)
    {
        return {};
    }

}