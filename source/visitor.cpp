#include "yasf/object.hpp"

namespace yasf
{

auto ObjectVisitor::traverse(Object& obj) -> void
{
    if (m_traversal_mode == TraversalMode::CHILDREN) {
        obj.traverse(*this);
    } else if (m_traversal_mode == TraversalMode::PARENTS) {
        obj.ascend(*this);
    }
}

}  // namespace yasf
