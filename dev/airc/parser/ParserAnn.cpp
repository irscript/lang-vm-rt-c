#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    AstAnnRef Parser::getAnn(Token &tok)
    {
        switch (tok.code.ann)
        {
        case TkAnnotate::Buildin:
        {
            AnnBuildin *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Async:
        {
            AnnAsync *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Volatile:
        {
            AnnVolatile *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Static:
        {
            AnnStatic *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Final:
        {
            AnnFinal *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Inline:
        {
            AnnInline *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Virtual:
        {
            AnnVirtual *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Override:
        {
            AnnOverride *ann;
            auto result = genAnn(ann);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;
        case TkAnnotate::Operator:
        {
            auto tok2 = lexer.getNext();
            if (tok2.isOperator() == false)
                syntaxError(tok2, "缺少操作符");

            AnnOperator *ann;
            auto result = genAnn(ann, tok2.code.op);
            ann->startpos = tok.pos;
            ann->endpos = lexer.getPos();
            return result;
        }
        break;

        default:
            syntaxError(tok, "未知注解！");
            break;
        }
        return AstAnnRef();
    }
}