#ifndef GEAROENIX_GLES2_BUFFER_MESH_HPP
#define GEAROENIX_GLES2_BUFFER_MESH_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef USE_OPENGL_ES2
#include "../../core/cr-end-caller.hpp"
#include "../../render/buffer/rnd-buf-mesh.hpp"
#include "../gles2.hpp"
namespace gearoenix {
namespace gles2 {
    class Engine;
    namespace buffer {
        class Mesh : public render::buffer::Mesh {
        public:
        private:
            GLuint vbo, ibo;
            GLsizei ic;

        public:
            Mesh(unsigned int vertex_elements_count, system::File* f, Engine* e, core::EndCaller<core::EndCallerIgnore> c);
            ~Mesh();
            void bind();
            void draw();
        };
    } // namespace buffer
} // namespace gles2
} // namespace gearoenix
#endif
#endif // GEAROENIX_GLES2_BUFFER_MESH_HPP
