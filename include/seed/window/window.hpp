#pragma once

#include "seed/export.hpp"
#include "seed/window/raw_window.hpp"
#include "seed/window/window_create_options.hpp"
#include "seed/window/window_flags.hpp"
#include <SDL2/SDL.h>
#include <cstdint>
#include <nonstd/expected.hpp>
#include <string>
#include <utility>
#include <variant>

namespace passionfruit::seed {

class SEED_EXPORT window {
    SDL_Window* _handle;
    explicit constexpr window(SDL_Window* handle) : _handle(handle) {}

public:
    window() = delete;
    ~window();

    window(window&)         = delete;
    auto operator=(window&) = delete;

    window(window&& other) noexcept { _handle = std::exchange(other._handle, nullptr); }
    auto operator=(window&& other) noexcept -> window& {
        _handle = std::exchange(other._handle, nullptr);
        return *this;
    }

    explicit operator bool() { return _handle != nullptr; }
    static auto create(const window_create_options& options) -> nonstd::expected<window, std::string>;

    auto size() const -> std::pair<std::uint32_t, std::uint32_t>;
    auto size(std::uint32_t width, std::uint32_t height) -> void;

    auto platform_window() const -> nonstd::expected<raw_window, std::string>;
};

} // namespace passionfruit::seed