#include "astNodeExp.hpp"

namespace air
{
    std::any ExpAnnFile::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpAnnFunc::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpAnnLine::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }

    std::any ExpBool::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpNull::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpSInt::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpUInt::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpFlt32::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpFlt64::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpChar::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpString::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpThis::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpSuper::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpID::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpFuncCall::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpMemberCall::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpUnary::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpBinary::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpTernary::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpParen::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpNew::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpCast::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpArrayIndex::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpRange::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpInRange::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any ExpBlock::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
}