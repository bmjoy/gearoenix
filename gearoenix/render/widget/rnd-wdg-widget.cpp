#include "rnd-wdg-widget.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "rnd-wdg-text.hpp"

gearoenix::render::widget::Widget::Widget(
    const core::Id my_id,
    const Type t,
    system::stream::Stream* const s,
    engine::Engine* const e,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept
    : model::Model(my_id, model::Type::Widget, s, e, c)
    , widget_type(t)
{
}

gearoenix::render::widget::Widget::Widget(
    const core::Id my_id,
    const Type t,
    engine::Engine* const e,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept
    : model::Model(my_id, model::Type::Widget, e, c)
    , widget_type(t)
{
}

gearoenix::render::widget::Widget::~Widget() noexcept = default;

std::shared_ptr<gearoenix::render::widget::Widget> gearoenix::render::widget::Widget::read_gx3d(
    const core::Id my_id,
    system::stream::Stream* const f,
    engine::Engine* const e,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept
{
    const auto t = f->read<Type>();
    switch (t) {
    case Type::Text:
        return std::shared_ptr<Widget>(new Text(my_id, f, e, c));
    default:
        GXLOGF("Unexpected widget type (" << static_cast<core::TypeId>(t) << ")  in: " << my_id)
    }
}

bool gearoenix::render::widget::Widget::get_dynamicity() const noexcept
{
    return true;
}

void gearoenix::render::widget::Widget::selected(const math::Vec3<double>&) noexcept
{
}

void gearoenix::render::widget::Widget::selected_on(const math::Vec3<double>&, const std::vector<model::Model*>&) noexcept
{
}

void gearoenix::render::widget::Widget::select_cancelled() noexcept
{
}

void gearoenix::render::widget::Widget::select_released() noexcept
{
}

void gearoenix::render::widget::Widget::dragged(const math::Vec3<double>&) noexcept
{
}

void gearoenix::render::widget::Widget::dragged_on(const math::Vec3<double>&, const std::vector<model::Model*>&) noexcept
{
}
