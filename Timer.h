// SPDX-FileCopyrightText: 2018 Lutz Freitag
// SPDX-License-Identifier: MIT
#pragma once

#include "FileDescriptor.h"

#include <chrono>
#include <sys/timerfd.h>

namespace simplyfile {

struct Timer : FileDescriptor {
    Timer(int flags=TFD_NONBLOCK);
    Timer(std::chrono::nanoseconds duration, bool oneShot=false, int flags=TFD_NONBLOCK);

    Timer(Timer&&) noexcept = default;
    Timer& operator=(Timer&&) noexcept = default;

    int getElapsed() const;
    void cancel();
    void reset(std::chrono::nanoseconds duration, bool oneShot=false);
};

}
