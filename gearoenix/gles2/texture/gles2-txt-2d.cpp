#include "gles2-txt-2d.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../render/texture/rnd-txt-png.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-log.hpp"
#include "../engine/gles2-eng-engine.hpp"
#include "../../core/cr-function-loader.hpp"
#include "gles2-txt-sample.hpp"

gearoenix::gles2::texture::Texture2D::Texture2D(
	const core::Id my_id,
	const std::shared_ptr<engine::Engine>& e,
	const void * data,
	const render::texture::TextureFormat::Id f,
	const render::texture::SampleInfo s,
	const unsigned int img_width,
	const unsigned int img_heigt,
	const core::sync::EndCaller<core::sync::EndCallerIgnore>& call)
    : render::texture::Texture2D(my_id, e)
{
#ifdef GX_DEBUG_GLES2
	if (render::texture::TextureFormat::RGBA_UINT8 != f)
	{
		GXLOGF("Only RGBA_UINT8 format is supported in gles2, in texture: " << my_id);
	}
#endif
	const SampleInfo sample_info = SampleInfo(s);
	e->get_function_loader()->load([this, data, f, s, img_width, img_heigt, sample_info, call]
	{
        glGenTextures(1, &texture_object);
        glBindTexture(GL_TEXTURE_2D, texture_object);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sample_info.min_filter);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sample_info.mag_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sample_info.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sample_info.wrap_t);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_heigt, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    });
}

gearoenix::gles2::texture::Texture2D::Texture2D(const core::Id my_id, const GLuint txtobj, const std::shared_ptr<engine::Engine>& e)
    : render::texture::Texture2D(my_id, e)
    , texture_object(txtobj)
{
}

gearoenix::gles2::texture::Texture2D::~Texture2D()
{
	GXUNIMPLEMENTED;
    if (texture_object == 0)
        return;
    const GLuint c_texture_object = texture_object;
//    render_engine->add_load_function([c_texture_object] {
//        glBindTexture(GL_TEXTURE_2D, 0);
//        glDeleteTextures(1, &c_texture_object);
//    });
    texture_object = 0;
}

void gearoenix::gles2::texture::Texture2D::bind(GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_object);
}

#endif
