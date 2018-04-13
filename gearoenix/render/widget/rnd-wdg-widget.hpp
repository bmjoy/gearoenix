#ifndef GEAROEMIX_RENDER_WIDGET_WIDGET_HPP
#define GEAROEMIX_RENDER_WIDGET_WIDGET_HPP
#include "../model/rnd-mdl-dynamic.hpp"
namespace gearoenix {
namespace render {
    namespace widget {
        class Widget : public model::Dynamic {
            friend class physics::Kernel;

        public:
            enum Type : core::Id {
                BUTTON = 1,
                EDIT = 2,
                TEXT = 3,
            };

            typedef enum : core::Id {
                NORMAL,
                PRESSED,
            } StateType;

            // This is something internal, it's gonna be used between ui-scene & widget
            typedef enum : core::Id {
                PRESS,
                RELEASE,
                MOVE_OUT,
            } EventType;

        private:
            //std::mutex event_locker;

        protected:
            StateType state_type = StateType::NORMAL;
            Widget(core::Id my_id, system::stream::Stream* f, Engine* e, core::sync::EndCaller<core::sync::EndCallerIgnore> c);
            // at the end it must send event
            virtual void press_effect();
            virtual void release_effect();
            virtual void cancel_effect();

        public:
            static Widget* read(core::Id my_id, system::stream::Stream* f, Engine* e, core::sync::EndCaller<core::sync::EndCallerIgnore> c);
            virtual ~Widget();
            void state_change(EventType e);
        };
    }
}
}
#endif
