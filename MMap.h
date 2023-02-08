#pragma once

#include <sys/mman.h>

#include <span>
#include <stdexcept>

namespace simplyfile
{

template<typename T>
struct MMap {
    MMap(int fd, std::size_t count, int prot = PROT_READ, int flags = MAP_PRIVATE, std::size_t offset = 0)
    {
        auto p = mmap(nullptr, count * sizeof(T), prot, flags, fd, offset);
        if (not p) {
            throw std::runtime_error("cannot do mmap");
        }
        _data = {reinterpret_cast<T*>(p), count};
    }
    MMap() = default;

    MMap(MMap const&) = delete;
    MMap& operator=(MMap const&) = delete;

    MMap(MMap&& other) { *this = std::move(other); };
    MMap& operator=(MMap&& rhs) {
        std::swap(_data, rhs._data);
        return *this;
    }

    ~MMap() {
        if (_data.empty()) {
            return;
        }
        munmap(const_cast<void*>(reinterpret_cast<void const*>(_data.data())), _data.size_bytes());
    }

    std::span<T> data() {
        return _data;
    }

private:
    std::span<T> _data;
};

}