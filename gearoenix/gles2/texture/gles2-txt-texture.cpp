#include "gles2-txt-texture.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "gles2-txt-2d.hpp"
#include "gles2-txt-target.hpp"

void gearoenix::gles2::texture::Texture::bind(
    const render::texture::Texture* const t,
    const gl::enumerated texture_unit) noexcept
{
    switch (t->get_texture_type()) {
    case render::texture::Type::Target2D:
        Target::bind_texture(reinterpret_cast<const render::texture::Target*>(t), texture_unit);
        return;
    case render::texture::Type::Texture2D:
        reinterpret_cast<const texture::Texture2D*>(t)->bind(texture_unit);
        return;
    default:
        GXUNEXPECTED
    }
}

#endif
