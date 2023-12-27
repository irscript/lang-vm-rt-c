#include "IRNode.hpp"

namespace air
{
    void IRBlock::visit(IIRVisit &vist){vist.visit(*this);}
    void IRUnary::visit(IIRVisit &vist){vist.visit(*this);}
    void IRBinary::visit(IIRVisit &vist){vist.visit(*this);}
}