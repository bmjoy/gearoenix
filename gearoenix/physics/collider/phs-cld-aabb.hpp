#ifndef GEAROENIX_PHYSICS_COLLIDER_AABB_HPP
#define GEAROENIX_PHYSICS_COLLIDER_AABB_HPP
#include "phs-cld-collider.hpp"
namespace gearoenix::physics::collider {
class Aabb : public Collider {
public:
    Aabb(const math::Vec3 &u, const math::Vec3 &l) noexcept
            : Collider(Type::Aabb) {
        box = math::Aabb3(u, l);
    }
    ~Aabb() noexcept final = default;
};
}
#endif
