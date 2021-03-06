#include "gles2-pip-irradiance-convoluter-resource-set.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../gl/gl-loader.hpp"
#include "../../render/buffer/rnd-buf-uniform.hpp"
#include "../../render/camera/rnd-cmr-uniform.hpp"
#include "../../render/graph/node/rnd-gr-nd-irradiance-convoluter.hpp"
#include "../../render/mesh/rnd-msh-mesh.hpp"
#include "../buffer/gles2-buf-index.hpp"
#include "../buffer/gles2-buf-vertex.hpp"
#include "../shader/gles2-shd-irradiance-convoluter.hpp"
#include "../texture/gles2-txt-cube.hpp"
#include "gles2-pip-irradiance-convoluter.hpp"
#include "gles2-pip-resource-set.hpp"

gearoenix::gles2::pipeline::IrradianceConvoluterResourceSet::IrradianceConvoluterResourceSet(const std::shared_ptr<shader::IrradianceConvoluter>& shd, std::shared_ptr<IrradianceConvoluter const> pip) noexcept
    : render::pipeline::IrradianceConvoluterResourceSet(std::move(pip))
    , base(new gles2::pipeline::ResourceSet(shd))
{
}

gearoenix::gles2::pipeline::IrradianceConvoluterResourceSet::~IrradianceConvoluterResourceSet() noexcept = default;

void gearoenix::gles2::pipeline::IrradianceConvoluterResourceSet::bind_final(gl::uint& bound_shader_program) const noexcept
{
#ifdef GX_DEBUG_MODE
    gl::Loader::check_for_error();
#endif
    GX_GLES2_PIP_RES_START_DRAWING_MESH
    GX_GLES2_PIP_RES_START_SHADER(IrradianceConvoluter, shd)
    GX_GLES2_PIP_RES_SET_TXT_CUBE(environment, environment)
    GX_GLES2_PIP_RES_END_DRAWING_MESH
#ifdef GX_DEBUG_MODE
    gl::Loader::check_for_error();
#endif
}

#endif