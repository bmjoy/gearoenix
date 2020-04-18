#include "rnd-txt-texture.hpp"
#include "../../system/stream/sys-stm-local.hpp"
#include "rnd-txt-image.hpp"

void gearoenix::render::texture::Texture::write_gx3d_image(
    system::stream::Stream* const s,
    const float* const data,
    const std::size_t img_width,
    const std::size_t img_height,
    const std::size_t components_count) noexcept
{
    const auto offset_of_size = s->tell();
    (void)s->write(static_cast<core::Count>(0));
    const auto offset_after_size = s->tell();
    render::texture::Image::encode_hdr(s, data, img_width, img_height, components_count);
    const auto curr_off = s->tell();
    s->seek(offset_of_size);
    (void)s->write(static_cast<core::Count>(curr_off - offset_after_size));
    s->seek(curr_off);
}

void gearoenix::render::texture::Texture::write_gx3d_image(
    system::stream::Stream* const s,
    const unsigned char* const data,
    const std::size_t img_width,
    const std::size_t img_height,
    const std::size_t components_count) noexcept
{
    const auto offset_of_size = s->tell();
    (void)s->write(static_cast<core::Count>(0));
    const auto offset_after_size = s->tell();
    render::texture::Image::encode_png(s, data, img_width, img_height, components_count);
    const auto curr_off = s->tell();
    s->seek(offset_of_size);
    (void)s->write(static_cast<core::Count>(curr_off - offset_after_size));
    s->seek(curr_off);
}

gearoenix::render::texture::Texture::Texture(
    const core::Id my_id,
    const Type texture_type,
    const TextureFormat texture_format,
    const SampleInfo& sample_info,
    engine::Engine* const e) noexcept
    : core::asset::Asset(my_id, core::asset::Type::Texture)
    , texture_type(texture_type)
    , texture_format(texture_format)
    , render_engine(e)
    , sample_info(sample_info)
{
}

gearoenix::render::texture::Texture::~Texture() noexcept = default;

void gearoenix::render::texture::Texture::write_gx3d(
    const std::string& file_address,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept
{
    std::shared_ptr<system::stream::Stream> l(new system::stream::Local(file_address, true));
    write_gx3d(l, c);
}

void gearoenix::render::texture::Texture::write_gx3d(
    const std::shared_ptr<system::stream::Stream>& s,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>&) noexcept
{
    (void)s->write(texture_type);
    (void)s->write(texture_format);
    sample_info.write(s.get());
}
