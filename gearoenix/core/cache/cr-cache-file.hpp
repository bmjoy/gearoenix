#ifndef GEAROENIX_CORE_CACHE_FILE_HPP
#define GEAROENIX_CORE_CACHE_FILE_HPP
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-log.hpp"
#include "../cr-build-configuration.hpp"
#include "cr-cache-cacher.hpp"
namespace gearoenix {
namespace core {
    namespace cache {
        template <class T>
        class File {
        private:
            Cacher<T> cacher;
            std::map<Id, Offset> offsets;
            const std::shared_ptr<system::stream::Stream> file;

        public:
            File(const std::shared_ptr<system::stream::Stream>& file)
                : file(file)
            {
                const Count c = file->read<Count>();
                for (Count i = 0; i < c; ++i) {
                    offsets[file->read<Id>()] = file->read<Offset>();
                }
            }

            template <class CT>
            std::shared_ptr<CT> get(const Id id, std::function<std::shared_ptr<CT>()> new_fun)
            {
                std::function<std::shared_ptr<CT>()> fn_new = [new_fun, this, id] {
#ifdef GX_DEBUG_MODE
                    auto search = offsets.find(id);
                    if (search == offsets.end()) {
                        GXLOGF("object with id: " << id << ", not found in table of offsets.");
                    }
                    file->seek(static_cast<unsigned int>(search->second));
#else
                    file->seek(offsets[id]);
#endif
                    return new_fun();
                };
                return cacher.get(id, fn_new);
            }

            template <class CT>
            std::shared_ptr<CT> get(const Id id) const
            {
                return cacher.get(id);
            }
        };
    } // namespace cache
} // namespace core
} // namespace gearoenix
#endif // GEAROENIX_CORE_CACHE_FILE_HPP
