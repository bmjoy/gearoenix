#ifndef GEAROEMIX_RENDER_SCENE_SCENE_HPP
#define GEAROEMIX_RENDER_SCENE_SCENE_HPP
#include "../../core/asset/cr-asset.hpp"
#include "../../math/math-vector.hpp"
#include <map>
#include <memory>
#include <tuple>
#include <vector>

namespace gearoenix {
namespace audio {
    class Audio;
}
namespace core {
    class EndCaller;
}
namespace system {
    class File;
}
namespace render {
    class Engine;
    namespace camera {
        class Camera;
    }
    namespace light {
        class Light;
        class Sun;
    }
    namespace material {
        class Material;
    }
    namespace mesh {
        class Mesh;
    }
    namespace model {
        class Model;
    }
    namespace texture {
        class Texture2D;
    }
    namespace scene {
        class Scene : public core::asset::Asset {
        private:
            std::vector<std::shared_ptr<camera::Camera>> cameras;
            std::vector<std::shared_ptr<audio::Audio>> audios;
            std::vector<std::shared_ptr<light::Light>> lights;
            std::map<core::Id, std::shared_ptr<model::Model>> root_models;
            std::map<core::Id, std::weak_ptr<model::Model>> all_models;
            // shader_id -> model_id -> Mesh
            std::map<core::Id, std::map<core::Id, std::weak_ptr<mesh::Mesh>>> shadow_caster_models;
            // shader_id -> model_id -> (Material , Mesh)
            std::map<core::Id, std::map<core::Id, std::tuple<std::weak_ptr<material::Material>, std::weak_ptr<mesh::Mesh>>>> opaque_models;
            std::map<core::Id, std::map<core::Id, std::tuple<std::weak_ptr<material::Material>, std::weak_ptr<mesh::Mesh>>>> transparent_models;
            unsigned int curcam = 0;
            bool renderable = false;
            math::Vec3 ambient_light = math::Vec3(0.2f, 0.2f, 0.2f);
            //Engine* e;

            void add_model(core::Id id, std::weak_ptr<model::Model> m);

        protected:
            Scene(system::File* f, Engine* e, std::shared_ptr<core::EndCaller> c);

        public:
            void commit();
            void cast_shadow();
            void draw(texture::Texture2D* shadow_texture);
            ~Scene();
            static Scene* read(system::File* f, Engine* e, std::shared_ptr<core::EndCaller> c);
            const camera::Camera* get_current_camera() const;
            camera::Camera* get_current_camera();
            const math::Vec3& get_ambient_light() const;
            const light::Sun* get_sun() const;
            void set_renderable(bool);
        };
    }
}
}
#endif
