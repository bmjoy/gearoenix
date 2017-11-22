#ifndef GEAROEMIX_RENDER_MATERIAL_DIRECTIONAL_D2_SPECULATED_BAKED_FULL_OPAQUE_HPP
#define GEAROEMIX_RENDER_MATERIAL_DIRECTIONAL_D2_SPECULATED_BAKED_FULL_OPAQUE_HPP
#include "../../math/math-matrix.hpp"
#include "../../math/math-vector.hpp"
#include "../shader/rnd-shd-resources.hpp"
#include "rnd-mat-material.hpp"
#include <memory>
namespace gearoenix {
namespace core {
    class EndCaller;
}
namespace render {
    namespace texture {
        class Texture2D;
        class Cube;
    }
    namespace material {
        class DirectionalD2SpeculatedBakedFullOpaque : public Material {
        public:
            const static core::Id SHADER_ID;
            class Resources : public shader::Resources {
            protected:
                texture::Cube* env;
                texture::Texture2D* txt;
                texture::Texture2D* shdtxt;

            public:
                Resources(Engine* e, pipeline::Pipeline* pip, buffer::Uniform* u);
                void set_texture(texture::Texture2D* t);
                void set_baked_env(texture::Cube* t);
                void set_shadow_texture(texture::Texture2D* t);
            };
            typedef struct {
                math::Mat4x4 vp;
                math::Mat4x4 m;
                math::Mat4x4 db;
                math::Vec3 sun;
                math::Vec3 sun_color;
                math::Vec3 spec_color;
                math::Vec3 spec_factors;
                math::Vec3 ambl_color;
                math::Vec3 eye;
                core::Real rfl_fac = 0.5f;
            } Uniform;

        private:
            Uniform u;
            std::shared_ptr<texture::Texture2D> txt;
            std::shared_ptr<texture::Cube> env;
            Resources* shdrsc;

        public:
            DirectionalD2SpeculatedBakedFullOpaque(system::File* f, Engine* e, std::shared_ptr<core::EndCaller> end);
            ~DirectionalD2SpeculatedBakedFullOpaque();
            unsigned int get_vertex_elements_count() const;
            core::Id get_shader_id() const;
            bool needs_mvp() const;
            bool needs_dbm() const;
            void update(const scene::Scene* s, const model::Model* m);
            void bind(texture::Texture2D* shadow_texture);
        };
    }
}
}
#endif