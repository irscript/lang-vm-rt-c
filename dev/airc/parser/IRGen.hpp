#ifndef __IRGEN_INC__
#define __IRGEN_INC__

#include "airc/base/astNode.hpp"
#include "utils/pch.hpp"
namespace air
{
    // IR生成
    struct IRGen : public IAstVisitor
    {

        // 访问声明
        virtual std::any visit(DeclFile &dec, std::any opt) override;
        virtual std::any visit(DeclVar &dec, std::any opt) override;
        virtual std::any visit(DeclFunc &dec, std::any opt) override;
        virtual std::any visit(DeclEnum &dec, std::any opt) override;
        virtual std::any visit(DeclStruct &dec, std::any opt) override;
        virtual std::any visit(DeclInterface &dec, std::any opt) override;
        virtual std::any visit(DeclEntrust &dec, std::any opt) override;
        virtual std::any visit(DeclClass &dec, std::any opt) override;
        // 访问语句
        virtual std::any visit(StmBlock &stm, std::any opt) override;
        virtual std::any visit(StmIf &stm, std::any opt) override;
        virtual std::any visit(StmElsif &stm, std::any opt) override;
        virtual std::any visit(StmElse &stm, std::any opt) override;
        virtual std::any visit(StmSwitch &stm, std::any opt) override;
        virtual std::any visit(StmCase &stm, std::any opt) override;
        virtual std::any visit(StmDefault &stm, std::any opt) override;
        virtual std::any visit(StmFor &stm, std::any opt) override;
        virtual std::any visit(StmDoWhile &stm, std::any opt) override;
        virtual std::any visit(StmWhile &stm, std::any opt) override;
        virtual std::any visit(StmTry &stm, std::any opt) override;
        virtual std::any visit(StmCatch &stm, std::any opt) override;
        virtual std::any visit(StmFinally &stm, std::any opt) override;
        virtual std::any visit(StmThrow &stm, std::any opt) override;
        virtual std::any visit(StmLabel &stm, std::any opt) override;
        virtual std::any visit(StmGoto &stm, std::any opt) override;
        virtual std::any visit(StmBreak &stm, std::any opt) override;
        virtual std::any visit(StmContinue &stm, std::any opt) override;
        virtual std::any visit(StmReturn &stm, std::any opt) override;
        virtual std::any visit(StmVar &stm, std::any opt) override;
        virtual std::any visit(StmExp &stm, std::any opt) override;

        // 访问表达式
        virtual std::any visit(ExpAnnFile &exp, std::any opt) override;
        virtual std::any visit(ExpAnnFunc &exp, std::any opt) override;
        virtual std::any visit(ExpAnnLine &exp, std::any opt) override;
        virtual std::any visit(ExpBool &exp, std::any opt) override;
        virtual std::any visit(ExpNull &exp, std::any opt) override;
        virtual std::any visit(ExpSInt &exp, std::any opt) override;
        virtual std::any visit(ExpUInt &exp, std::any opt) override;
        virtual std::any visit(ExpFlt32 &exp, std::any opt) override;
        virtual std::any visit(ExpFlt64 &exp, std::any opt) override;
        virtual std::any visit(ExpChar &exp, std::any opt) override;
        virtual std::any visit(ExpString &exp, std::any opt) override;
        virtual std::any visit(ExpThis &exp, std::any opt) override;
        virtual std::any visit(ExpSuper &exp, std::any opt) override;
        virtual std::any visit(ExpID &exp, std::any opt) override;
        virtual std::any visit(ExpFuncCall &exp, std::any opt) override;
        virtual std::any visit(ExpMemberCall &exp, std::any opt) override;
        virtual std::any visit(ExpUnary &exp, std::any opt) override;
        virtual std::any visit(ExpBinary &exp, std::any opt) override;
        virtual std::any visit(ExpTernary &exp, std::any opt) override;
        virtual std::any visit(ExpParen &exp, std::any opt) override;
        virtual std::any visit(ExpNew &exp, std::any opt) override;
        virtual std::any visit(ExpCast &exp, std::any opt) override;
        virtual std::any visit(ExpArrayIndex &exp, std::any opt) override;
        virtual std::any visit(ExpRange &exp, std::any opt) override;
        virtual std::any visit(ExpInRange &exp, std::any opt) override;
        virtual std::any visit(ExpBlock &exp, std::any opt) override;
    };
}

#endif // __IRGEN_INC__