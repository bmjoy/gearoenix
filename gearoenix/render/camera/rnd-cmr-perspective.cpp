#include "rnd-cmr-perspective.hpp"
#include "../../core/event/cr-ev-event.hpp"
#include "../../core/event/cr-ev-window-resize.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-log.hpp"
#include "../engine/rnd-eng-engine.hpp"
#include "rnd-cmr-transformation.hpp"
#include "rnd-cmr-uniform.hpp"
#include <cmath>

void gearoenix::render::camera::Perspective::update_fovy()
{
    fovy = static_cast<core::Real>(std::atan(static_cast<double>(tany))) * 2.0f;
    uniform->projection = math::Mat4x4::perspective(
        tanx * -uniform->near * 2.0f,
        tany * -uniform->near * 2.0f,
        -uniform->near,
        -uniform->far);
    uniform->uniform_projection = math::Mat4x4(
                                      0.5f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 0.5f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f, 0.0f,
                                      0.5f, 0.5f, 0.0f, 1.0f)
        * uniform->projection;
    lambda = static_cast<core::Real>(
                 std::sin(static_cast<double>(fovx) * 0.5) + std::sin(static_cast<double>(fovy) * 0.5))
        * 0.5f;
    transformation->update_view_projection();
}

gearoenix::render::camera::Perspective::Perspective(
    const core::Id my_id,
    const std::shared_ptr<system::stream::Stream>& f,
    const std::shared_ptr<engine::Engine>& e)
    : Camera(my_id, f, e)
{
    const auto rad = f->read<core::Real>();
    GXLOGD("Radiant is: " << rad << ", in perspective camera with id: " << my_id);
    set_field_of_view(rad);
}

gearoenix::render::camera::Perspective::Perspective(
    const core::Id my_id,
    const std::shared_ptr<engine::Engine>& e)
    : Camera(my_id, e)
{
    set_field_of_view(1.571f);
}

void gearoenix::render::camera::Perspective::set_aspect_ratio(const gearoenix::core::Real ratio)
{
    Camera::set_aspect_ratio(ratio);
    tany = tanx / ratio;
    update_fovy();
}

void gearoenix::render::camera::Perspective::set_field_of_view(const core::Real radian)
{
    fovx = radian;
    tanx = static_cast<core::Real>(std::tan(static_cast<double>(radian) * 0.5));
    tany = tanx / uniform->aspect_ratio;
    update_fovy();
}

gearoenix::math::Ray3 gearoenix::render::camera::Perspective::create_ray3(const core::Real x, const core::Real y) const
{
    math::Vec3 dir = (uniform->x * x) + (uniform->y * y) + (uniform->z * uniform->near);
    const math::Vec3 origin = dir + uniform->position;
    dir.normalize();
    return math::Ray3(origin, dir);
}

gearoenix::core::Real gearoenix::render::camera::Perspective::get_distance(const math::Vec3& model_location) const
{
    return (model_location - uniform->position).square_length();
}

std::vector<gearoenix::math::Vec3[4]> gearoenix::render::camera::Perspective::get_cascaded_shadow_frustum_partitions() const
{
	//e->get
	return std::vector<gearoenix::math::Vec3[4]>();
}
