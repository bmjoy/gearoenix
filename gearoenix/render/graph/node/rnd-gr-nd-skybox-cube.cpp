#include "rnd-gr-nd-skybox-cube.hpp"
#include "../../../core/asset/cr-asset-manager.hpp"
#include "../../../core/sync/cr-sync-kernel-workers.hpp"
#include "../../../system/sys-app.hpp"
#include "../../buffer/rnd-buf-manager.hpp"
#include "../../buffer/rnd-buf-uniform.hpp"
#include "../../camera/rnd-cmr-camera.hpp"
#include "../../command/rnd-cmd-buffer.hpp"
#include "../../command/rnd-cmd-manager.hpp"
#include "../../engine/rnd-eng-engine.hpp"
#include "../../material/rnd-mat-material.hpp"
#include "../../mesh/rnd-msh-mesh.hpp"
#include "../../model/rnd-mdl-mesh.hpp"
#include "../../model/rnd-mdl-model.hpp"
#include "../../pipeline/rnd-pip-manager.hpp"
#include "../../pipeline/rnd-pip-pipeline.hpp"
#include "../../pipeline/rnd-pip-skybox-cube-resource-set.hpp"
#include "../../skybox/rnd-sky-cube.hpp"
#include "../../sync/rnd-sy-semaphore.hpp"
#include "../../texture/rnd-txt-manager.hpp"
#include "../../texture/rnd-txt-texture-cube.hpp"

gearoenix::render::graph::node::SkyboxCubeRenderData::SkyboxCubeRenderData(engine::Engine* e, pipeline::Pipeline* pip) noexcept
    : r(dynamic_cast<pipeline::SkyboxCubeResourceSet*>(pip->create_resource_set()))
    , u(e->get_buffer_manager()->create_uniform(sizeof(SkyboxCubeUniform)))
{
    r->set_node_uniform_buffer(u.get());
}

gearoenix::render::graph::node::SkyboxCubeRenderData::~SkyboxCubeRenderData() noexcept = default;

gearoenix::render::graph::node::SkyboxCubeKernel::SkyboxCubeKernel(engine::Engine* e, const unsigned int kernel_index) noexcept
    : secondary_cmd(e->get_command_manager()->create_secondary_command_buffer(kernel_index))
{
}

gearoenix::render::graph::node::SkyboxCubeKernel::~SkyboxCubeKernel() noexcept = default;

gearoenix::render::graph::node::SkyboxCubeFrame::SkyboxCubeFrame(gearoenix::render::engine::Engine* e) noexcept
    : kernels(e->get_kernels()->get_threads_count())
{
    for (std::size_t i = 0; i < kernels.size(); ++i) {
        kernels[i] = std::make_unique<SkyboxCubeKernel>(e, static_cast<unsigned int>(i));
    }
}

gearoenix::render::graph::node::SkyboxCubeFrame::~SkyboxCubeFrame() noexcept = default;

void gearoenix::render::graph::node::SkyboxCube::record_sky(
    const skybox::Cube* const sky,
    const SkyboxCubeUniform& u,
    SkyboxCubeKernel* const kernel) noexcept
{
    auto* const rd = kernel->render_data_pool.get_next([this] {
        return new SkyboxCubeRenderData(e, render_pipeline.get());
    });
    rd->u->set_data(u);
    auto* const prs = rd->r.get();
    prs->set_mesh(sky->get_msh().get());
    prs->set_material(sky->get_mat_cube().get());
    prs->set_camera(cam);
    kernel->secondary_cmd->bind(prs);
}

gearoenix::render::graph::node::SkyboxCube::SkyboxCube(
    engine::Engine* const e,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept
    : Node(
        Type::SkyboxCube,
        e,
        pipeline::Type::SkyboxCube,
        0,
        1,
        {},
        {
            "color",
        },
        call)
    , frames(e->get_frames_count())
{
    set_providers_count(input_textures.size());
    for (auto& f : frames) {
        f = std::make_unique<SkyboxCubeFrame>(e);
    }
}

gearoenix::render::graph::node::SkyboxCube::~SkyboxCube() noexcept = default;

void gearoenix::render::graph::node::SkyboxCube::update() noexcept
{
    Node::update();
    const unsigned int frame_number = e->get_frame_number();
    frame = frames[frame_number].get();
    auto& kernels = frame->kernels;
    for (auto& kernel : kernels) {
        kernel->render_data_pool.refresh();
        kernel->secondary_cmd->begin();
    }
    skies.clear();
}

void gearoenix::render::graph::node::SkyboxCube::set_camera(const camera::Camera* const c) noexcept
{
    cam = c;
    render_target = c->get_target();
}

void gearoenix::render::graph::node::SkyboxCube::add_sky(const skybox::Cube* const sky) noexcept
{
    skies.push_back(sky);
}

void gearoenix::render::graph::node::SkyboxCube::record_continuously(const unsigned int kernel_index) noexcept
{
    auto* const kernel = frame->kernels[kernel_index].get();
    for (const auto* const sky : skies) {
        const auto& cam_unf = cam->get_uniform();
        const SkyboxCubeUniform u {
            .mvp = cam_unf.view_projection * math::Mat4x4<float>::translator(cam_unf.position) * math::Mat4x4(std::abs(cam_unf.far) * 0.57735026f),
        };
        record_sky(sky, u, kernel);
    }
}

void gearoenix::render::graph::node::SkyboxCube::submit() noexcept
{
    const unsigned int frame_number = e->get_frame_number();
    command::Buffer* cmd = frames_primary_cmd[frame_number].get();
    cmd->bind(render_target);
    for (const auto& k : frame->kernels) {
        cmd->record(k->secondary_cmd.get());
    }
    Node::submit();
}
