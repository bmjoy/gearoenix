#ifndef GEAROENIX_SYSTEM_STREAM_LOCAL_HPP
#define GEAROENIX_SYSTEM_STREAM_LOCAL_HPP

#include "sys-stm-stream.hpp"
#include <fstream>

namespace gearoenix::system::stream {
class Local final : public Stream {
private:
    std::fstream file;
    explicit Local(std::fstream file) noexcept;

public:
    explicit Local(const std::string& name, bool writable = false) noexcept;
    ~Local() noexcept final;
    [[nodiscard]] static Local* open(const std::string& name, bool writable = false) noexcept;
    [[nodiscard]] core::Count read(void* data, core::Count length) noexcept final;
    [[nodiscard]] core::Count write(const void* data, core::Count length) noexcept final;
    void seek(core::Count offset) noexcept final;
    [[nodiscard]] core::Count tell() noexcept final;
    [[nodiscard]] core::Count size() noexcept final;
    static bool exist(const std::string& name) noexcept;
};
}
#endif
