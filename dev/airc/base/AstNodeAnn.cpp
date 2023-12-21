#include "AstNodeAnn.hpp"

namespace air
{
    std::any IAstAnn::visit(IAstVisitor &visitor, std::any opt)
    {
        return {};
    }
}