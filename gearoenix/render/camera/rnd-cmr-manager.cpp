#include "rnd-cmr-manager.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../engine/rnd-eng-engine.hpp"
#include "rnd-cmr-orthographic.hpp"
#include "rnd-cmr-perspective.hpp"

gearoenix::render::camera::Manager::Manager(std::unique_ptr<system::stream::Stream> s, engine::Engine* const e) noexcept
    : e(e)
    , cache(std::move(s))
{
}

std::shared_ptr<gearoenix::render::camera::Camera> gearoenix::render::camera::Manager::get_gx3d(const core::Id id, core::sync::EndCaller<Camera>& call) noexcept
{
    std::shared_ptr<Camera> data = cache.get<Camera>(
        id, [this, id, call]() noexcept -> std::shared_ptr<Camera> {
            system::stream::Stream* const file = cache.get_file();
            const auto t = file->read<core::TypeId>();
            switch (t) {
            case 1:
                return std::make_shared<Perspective>(id, file, e);
            case 2:
                return std::make_shared<Orthographic>(id, file, e);
            default:
                GXLOGF("Unexpected camera type " << t)
            }
        });
    call.set_data(data);
    return data;
}
