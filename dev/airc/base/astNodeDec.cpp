#include "astNodeDec.hpp"

namespace air
{
    std::any DeclFile::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclVar::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclFunc::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclEnum::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclStruct::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclInterface::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclEntrust::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }
    std::any DeclClass::visit(IAstVisitor &visitor, std::any opt) { return visitor.visit(*this, opt); }

}