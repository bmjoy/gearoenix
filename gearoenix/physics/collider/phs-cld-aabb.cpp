#include "phs-cld-aabb.hpp"

gearoenix::physics::collider::Aabb::Aabb(math::Vec3 u, math::Vec3 l) noexcept
    : Collider(Type::Aabb)
{
    box = math::Aabb3(u, l);
}