#ifndef GEAROENIX_RENDER_TEXTURE_SAMPLE_HPP
#define GEAROENIX_RENDER_TEXTURE_SAMPLE_HPP
#include "rnd-txt-filter.hpp"
#include "rnd-txt-wrap.hpp"

namespace gearoenix::system::stream {
class Stream;
}

namespace gearoenix::render::texture {
struct SampleInfo {
    Filter min_filter = Filter::LinearMipmapLinear;
    Filter mag_filter = Filter::Linear;
    Wrap wrap_s = Wrap::Repeat;
    Wrap wrap_t = Wrap::Repeat;
    Wrap wrap_r = Wrap::Repeat;

    void write(system::stream::Stream* s) const noexcept;
    void read(system::stream::Stream* s) noexcept;
    [[nodiscard]] bool needs_mipmap() const noexcept;
};
}
#endif
