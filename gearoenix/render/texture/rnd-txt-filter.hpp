#ifndef GEAROENIX_RENDER_TEXTURE_FILTER_HPP
#define GEAROENIX_RENDER_TEXTURE_FILTER_HPP
#include "../../core/cr-types.hpp"
namespace gearoenix::render::texture {
class Filter {
public:
    typedef enum : core::TypeId {
        CUBIC = 1,
        LINEAR = 2,
        NEAREST = 3,
    } Id;
};
}
#endif
