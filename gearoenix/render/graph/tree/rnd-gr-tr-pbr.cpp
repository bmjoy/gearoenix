#include "rnd-gr-tr-pbr.hpp"
#include "../../../core/asset/cr-asset-manager.hpp"
#include "../../../system/sys-app.hpp"
#include "../../engine/rnd-eng-engine.hpp"
#include "../../light/rnd-lt-directional.hpp"
#include "../../scene/rnd-scn-manager.hpp"
#include "../../scene/rnd-scn-scene.hpp"
#include "../node/rnd-gr-nd-forward-pbr-directional-shadow.hpp"

gearoenix::render::graph::tree::Pbr::Pbr(const std::shared_ptr<engine::Engine>& e, const core::sync::EndCaller<core::sync::EndCallerIgnore>& call)
	: Tree(e)
	, in_weak_hardware(engine::Type::OPENGL_ES2 == e->get_engine_type_id())
{
	fwddirshd = std::shared_ptr<node::ForwardPbrDirectionalShadow>(new node::ForwardPbrDirectionalShadow(e, call));
}

gearoenix::render::graph::tree::Pbr::~Pbr()
{
}

void gearoenix::render::graph::tree::Pbr::update()
{
	fwddirshd->update();
}

void gearoenix::render::graph::tree::Pbr::record(const unsigned int kernel_index)
{
	const std::shared_ptr<system::Application> &sysapp = e->get_system_application();
	const std::shared_ptr<core::asset::Manager> &astmgr = sysapp->get_asset_manager();
	const std::shared_ptr<scene::Manager> &scnmgr = astmgr->get_scene_manager();
	const std::map<core::Id, std::weak_ptr<scene::Scene>> &scenes = scnmgr->get_scenes();
	unsigned int scene_number = 0;
	for (const std::pair<core::Id, std::weak_ptr<scene::Scene>> &id_scene : scenes) {
		if (const std::shared_ptr<scene::Scene> scn = id_scene.second.lock()) {
			const std::map<core::Id, std::shared_ptr<camera::Camera>> &cameras = scn->get_cameras();
			const std::map<core::Id, std::shared_ptr<light::Light>> &lights = scn->get_lights();
			const std::map<core::Id, std::shared_ptr<model::Model>> &models = scn->get_models();
			for (const std::pair<core::Id, std::shared_ptr<camera::Camera>> &id_camera : cameras) {
				for (const std::pair<core::Id, std::shared_ptr<light::Light>> &id_light : lights) {
					const std::shared_ptr<light::Directional> dirlt = std::dynamic_pointer_cast<light::Directional>(id_light.second);
					if (dirlt != nullptr) {
						for (const std::pair<core::Id, std::shared_ptr<model::Model>> &id_model : models) {
							fwddirshd->record(scn, id_camera.second, dirlt, id_model.second, kernel_index);
						}
						continue; /// This is for future
					}
					// const std::shared_ptr<light::Point> pntlt = std::dynamic_pointer_cast<light::Point>(id_light.second);
					/// like ...
				}
			}
			++scene_number;
		}
	}	
}

void gearoenix::render::graph::tree::Pbr::submit()
{
}
