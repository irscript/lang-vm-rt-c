#include "astNodeStm.hpp"

namespace air
{
    std::any StmBlock::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmIf::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmElsif::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmElse::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmSwitch::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmCase::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmDefault::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmFor::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmDoWhile::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmWhile::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmTry::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmCatch::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmFinally::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmThrow::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmLable::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmGoto::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmBreak::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmContinue::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmReturn::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmVar::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any StmExp::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
}