#ifndef __ASTNODEANN_INC__
#define __ASTNODEANN_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstAnn : public IAstNode
    {
        IAstAnn(TkAnnotate kind) : kind(kind) {}
        inline TkAnnotate getKind() const { return kind; }
        virtual std::any visit(IAstVisitor &visitor, std::any opt) override;

    private:
        TkAnnotate kind;
    };

    //@buildin
    struct AnnBuildin : public IAstAnn
    {
        AnnBuildin() : IAstAnn(TkAnnotate::Buildin) {}
    };
    
    //@async
    struct AnnAsync : public IAstAnn
    {
        AnnAsync() : IAstAnn(TkAnnotate::Async) {}
    };
    //@volatile
    struct AnnVolatile : public IAstAnn
    {
        AnnVolatile() : IAstAnn(TkAnnotate::Volatile) {}
    };

    //@static
    struct AnnStatic : public IAstAnn
    {
        AnnStatic() : IAstAnn(TkAnnotate::Static) {}
    };
    //@final
    struct AnnFinal : public IAstAnn
    {
        AnnFinal() : IAstAnn(TkAnnotate::Final) {}
    };

    //@inline
    struct AnnInline : public IAstAnn
    {
        AnnInline() : IAstAnn(TkAnnotate::Inline) {}
    };
    //@virtual
    struct AnnVirtual : public IAstAnn
    {
        AnnVirtual() : IAstAnn(TkAnnotate::Virtual) {}
    };
    //@override
    struct AnnOverride : public IAstAnn
    {
        AnnOverride() : IAstAnn(TkAnnotate::Override) {}
    };
    //@operator op
    struct AnnOperator : public IAstAnn
    {
        AnnOperator(TkOpEnum op) : IAstAnn(TkAnnotate::Operator), op(op) {}

        TkOpEnum op;
    };

}
#endif // __ASTNODEANN_INC__