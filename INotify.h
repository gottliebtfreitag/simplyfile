// SPDX-FileCopyrightText: 2018 Lutz Freitag
// SPDX-License-Identifier: MIT
#include "FileDescriptor.h"

#include <map>
#include <optional>
#include <string>

#include <sys/inotify.h>

namespace simplyfile {

struct INotify : FileDescriptor {
    using FileDescriptor::FileDescriptor;
    INotify(int flags=0);

    INotify(INotify&&) noexcept = default;
    INotify& operator=(INotify&&) noexcept = default;

    // check inotify for mask meaning
    void watch(std::string const& _path, uint32_t mask);
    void unwatch(std::string const& _path);
    void unwatch_all();

    std::map<int, std::string> mIDs;

    struct Result {
        std::string path;
        std::string file;
    };

    [[nodiscard]] auto readEvent() -> std::optional<INotify::Result>;
};

}
