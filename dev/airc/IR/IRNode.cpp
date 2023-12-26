#include "IRNode.hpp"

namespace air
{
    void IRBlock::visit(IIRVisit &vist){vist.vist(*this);}
    void IRUnary::visit(IIRVisit &vist){vist.vist(*this);}
    void IRBinary::visit(IIRVisit &vist){vist.vist(*this);}
}