#include "rnd-rfl-type.hpp"
#include "../../system/sys-log.hpp"

namespace gearoenix::render::reflection {
std::ostream& operator<<(std::ostream& os, const Type t) noexcept
{
    if (2 < static_cast<int>(t))
        GXUNEXPECTED
    os << "gearoenix::render::reflection { ";
    switch (t) {
    case Type::Baked:
        os << "Baked";
        break;
    case Type::Runtime:
        os << "Runtime";
        break;
    }
    os << " }";
    return os;
}
}