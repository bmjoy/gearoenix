#ifndef GEAROEMIX_RENDER_MODEL_MODEL_HPP
#define GEAROEMIX_RENDER_MODEL_MODEL_HPP
#include "../../core/asset/cr-asset.hpp"
#include "../../core/cr-build-configuration.hpp"
#include "../../core/cr-types.hpp"
#include "../../core/sync/cr-sync-end-caller.hpp"
#include "../../math/math-matrix.hpp"
#include "../../math/math-vector.hpp"
#include "rnd-mdl-uniform.hpp"
#include <map>
#include <memory>
namespace gearoenix {
namespace physics {
    namespace collider {
        class Collider;
    }
}
namespace render {
    namespace buffer {
        class Uniform;
    }
    namespace engine {
        class Engine;
    }
    namespace pipeline {
        class Resource;
    }
    namespace model {
		class Mesh;
        class Model : public core::asset::Asset {
        protected:
            const std::shared_ptr<engine::Engine> e;

			bool is_dynamic = true;
            bool has_shadow_caster = false;
            bool has_transparent = false;

            Uniform uniform;
			std::shared_ptr<buffer::Uniform> uniform_buffers[GX_FRAMES_COUNT];

            const std::shared_ptr<pipeline::Resource> pipeline_resource;

            std::map<core::Id, std::shared_ptr<Mesh>> meshes;
            std::map<core::Id, std::shared_ptr<Model>> children;
            std::shared_ptr<physics::collider::Collider> collider = nullptr;

        public:
			Model(
				const core::Id my_id,
				const std::shared_ptr<system::stream::Stream>& f,
				const std::shared_ptr<engine::Engine>& e,
				const core::sync::EndCaller<core::sync::EndCallerIgnore>& c,
				const bool is_dynamic = true);
			/// It will create an automatic Id for itself
			Model(
				const std::shared_ptr<engine::Engine>& e,
				const core::sync::EndCaller<core::sync::EndCallerIgnore>& c);
            virtual ~Model();
			void add_mesh(const std::shared_ptr<Mesh> &m);
			void add_child(const std::shared_ptr<Model> &c);

            const std::map<core::Id, std::shared_ptr<Model>>& get_children() const;
            const std::map<core::Id, std::shared_ptr<Mesh>>& get_meshes() const;
            const std::shared_ptr<physics::collider::Collider>& get_collider() const;
            
			const math::Mat4x4& get_model_matrix() const;
        };
    }
}
}
#endif
