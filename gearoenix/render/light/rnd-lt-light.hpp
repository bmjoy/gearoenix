#ifndef GEAROEMIX_RENDER_LIGHT_LIGHT_HPP
#define GEAROEMIX_RENDER_LIGHT_LIGHT_HPP
#include "../../core/asset/cr-asset.hpp"
#include "../../math/math-vector.hpp"
#include <memory>
namespace gearoenix {
namespace system {
    namespace stream {
        class Stream;
    }
}
namespace render {
	namespace engine {
		class Engine;
	}
    namespace light {
        class Light : public core::asset::Asset {
        protected:
            Light(
				const core::Id my_id,
				const std::shared_ptr<system::stream::Stream> &f,
				const std::shared_ptr<engine::Engine> &e);

        public:
            virtual ~Light();
            static Light* read(
				const core::Id my_id,
				const std::shared_ptr<system::stream::Stream> &f,
				const std::shared_ptr<engine::Engine> &e);
            const math::Vec3& get_color() const;
        };
    }
}
}
#endif
