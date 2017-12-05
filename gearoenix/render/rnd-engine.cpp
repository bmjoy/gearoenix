#include "rnd-engine.hpp"
#include "../core/asset/cr-asset-manager.hpp"
#include "../core/cr-end-caller.hpp"
#include "../core/cr-semaphore.hpp"
#include "../physics/phs-engine.hpp"
#include "../system/sys-app.hpp"
#include "../system/sys-log.hpp"
#include "pipeline/rnd-pip-manager.hpp"
#include "scene/rnd-scn-scene.hpp"
#include <functional>
#include <thread>

#ifdef THREAD_SUPPORTED
void gearoenix::render::Engine::scene_loader_function()
{
    while (scene_loader_continue) {
        scene_loader_signaler->lock();
        std::vector<std::function<void()>> temp_functions;
        scene_loader_mutex.lock();
        std::move(scene_loader_functions.begin(), scene_loader_functions.end(), std::back_inserter(temp_functions));
        scene_loader_functions.clear();
        scene_loader_mutex.unlock();
        for (std::function<void()>& f : temp_functions) {
            f();
        }
    }
}
#endif

gearoenix::render::Engine::Engine(system::Application* system_application)
    : sysapp(system_application)
{

    GXLOGI("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
#ifdef THREAD_SUPPORTED
    scene_loader_signaler = new core::Semaphore();
    scene_loader = std::thread(std::bind(&Engine::scene_loader_function, this));
#endif
    physics_engine = new physics::Engine(this);
    physics_engine->update();
}

gearoenix::render::Engine::~Engine()
{
    delete physics_engine;
#ifdef THREAD_SUPPORTED
    scene_loader_continue = false;
    scene_loader_signaler->release();
    scene_loader.join();
    delete scene_loader_signaler;
#endif
    delete pipmgr;
}

const gearoenix::system::Application* gearoenix::render::Engine::get_system_application() const
{
    return sysapp;
}

gearoenix::system::Application* gearoenix::render::Engine::get_system_application()
{
    return sysapp;
}

const gearoenix::render::pipeline::Manager* gearoenix::render::Engine::get_pipeline_manager() const
{
    return pipmgr;
}

gearoenix::render::pipeline::Manager* gearoenix::render::Engine::get_pipeline_manager()
{
    return pipmgr;
}

void gearoenix::render::Engine::add_load_function(std::function<void()> fun)
{
#ifdef THREAD_SUPPORTED
    std::lock_guard<std::mutex> lock(load_functions_mutex);
#endif
    load_functions.push_back(fun);
}

const std::shared_ptr<gearoenix::render::scene::Scene>& gearoenix::render::Engine::get_scene(unsigned int scene_index) const
{
#ifdef DEBUG_MODE
    if (scene_index > (unsigned int)loaded_scenes.size()) {
        UNEXPECTED;
    }
#endif
    return loaded_scenes[scene_index];
}

const std::vector<std::shared_ptr<gearoenix::render::scene::Scene>>& gearoenix::render::Engine::get_all_scenes() const
{
    return loaded_scenes;
}

void gearoenix::render::Engine::load_scene(core::Id scene_id, std::function<void(unsigned int)> on_load)
{
#ifdef THREAD_SUPPORTED
    scene_loader_mutex.lock();
    scene_loader_functions.push_back([this, scene_id, on_load] {
        loaded_scenes_mutex.lock();
#endif
        unsigned int result = (unsigned int)loaded_scenes.size();
        loaded_scenes.push_back(sysapp->get_asset_manager()->get_scene(scene_id, core::EndCaller::create([this, result, on_load] {
            loaded_scenes[result]->set_renderable(true);
            on_load(result);
        })));
#ifdef THREAD_SUPPORTED
        loaded_scenes_mutex.unlock();
    });
    scene_loader_mutex.unlock();
    scene_loader_signaler->release();
#endif
}
