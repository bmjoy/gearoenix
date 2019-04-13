#include "../../core/asset/cr-asset-manager.hpp"
#include "../../core/cr-static.hpp"
#include "../../physics/collider/phs-collider.hpp"
#include "../../system/stream/sys-stm-asset.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-app.hpp"
#include "../camera/rnd-cmr-camera.hpp"
#include "../camera/rnd-cmr-orthographic.hpp"
#include "../engine/rnd-eng-engine.hpp"
#include "../material/rnd-mat-material.hpp"
#include "../mesh/rnd-msh-manager.hpp"
#include "../mesh/rnd-msh-mesh.hpp"
#include "../scene/rnd-scn-scene.hpp"
#include "../widget/rnd-wdg-widget.hpp"
#include "rnd-mdl-model.hpp"
#include <iostream>
#include "rnd-mdl-mesh.hpp"

gearoenix::render::model::Mesh::Mesh(const std::shared_ptr<system::stream::Stream>& f, const std::shared_ptr<engine::Engine>& e, const core::sync::EndCaller<core::sync::EndCallerIgnore>& c)
{
	core::sync::EndCaller<mesh::Mesh> call([c](std::shared_ptr<mesh::Mesh>) {});
	msh = e->get_system_application()->get_asset_manager()->get_mesh_manager()->get_gx3d(f->read<core::Id>(), call);
	mat = std::make_shared<material::Material>(f, e, core::sync::EndCaller<core::sync::EndCallerIgnore>([c] {}));
}

gearoenix::render::model::Mesh::~Mesh() {}

const std::shared_ptr<gearoenix::render::mesh::Mesh>& gearoenix::render::model::Mesh::get_mesh() const
{
	return msh;
}

const std::shared_ptr<gearoenix::render::material::Material>& gearoenix::render::model::Mesh::get_material() const
{
	return mat;
}

void gearoenix::render::model::Mesh::update_uniform()
{
	mat->update_uniform();
}
