#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <string>

#include "seed/export.hpp"
#include "seed/window/window_flags.hpp"

namespace passionfruit::seed {

struct window_position {
    static constexpr auto centered = SDL_WINDOWPOS_CENTERED;
    int x;
    int y;
};

struct SEED_EXPORT window_create_options {
    std::string title;
    std::int32_t width;
    std::int32_t height;
    window_flags flags;
    window_position position;
};
} // namespace passionfruit::seed