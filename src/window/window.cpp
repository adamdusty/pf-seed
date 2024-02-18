#include "seed/window.hpp"
#include <adizzle/assert.hpp>
#include <format>
#include <limits>

#include <SDL2/SDL_syswm.h>

using nonstd::expected;
using nonstd::make_unexpected;

namespace passionfruit::seed {

window::~window() {
    if(_handle != nullptr) {
        SDL_DestroyWindow(_handle);
    }
}

auto window::create(const window_create_options& opt) -> expected<window, std::string> {
    auto* win = SDL_CreateWindow(
        opt.title.c_str(),
        opt.position.x,
        opt.position.y,
        opt.width,
        opt.height,
        static_cast<SDL_WindowFlags>(opt.flags)
    );

    if(win == nullptr) {
        const auto* err = SDL_GetError();
        return nonstd::make_unexpected(err);
    }

    return window(win);
}

auto window::size() const -> std::pair<std::uint32_t, std::uint32_t> {
    int x{};
    int y{};

    SDL_GetWindowSize(_handle, &x, &y);

    return {x, y};
}

auto window::size(std::uint32_t width, std::uint32_t height) -> void {
    ADIZZLE_ASSERT(width < std::numeric_limits<int>::max(), "Width not convertable to int");
    ADIZZLE_ASSERT(height < std::numeric_limits<int>::max(), "Height not convertable to int");

    SDL_SetWindowSize(_handle, static_cast<int>(width), static_cast<int>(height));
}

auto window::platform_window() const -> expected<raw_window, std::string> {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);

    if(SDL_GetWindowWMInfo(_handle, &info) != SDL_TRUE) {
        return make_unexpected(std::format("Error getting SDL_WM info: {}", SDL_GetError()));
    }
    switch(info.subsystem) {
    case SDL_SYSWM_WINDOWS:
        return raw_window{hwnd{.hwnd = info.info.win.window, .hinstance = info.info.win.hinstance}}; // NOLINT
    case SDL_SYSWM_X11:
    case SDL_SYSWM_WAYLAND:
    case SDL_SYSWM_UNKNOWN:
    case SDL_SYSWM_DIRECTFB:
    case SDL_SYSWM_COCOA:
    case SDL_SYSWM_UIKIT:
    case SDL_SYSWM_MIR:
    case SDL_SYSWM_WINRT:
    case SDL_SYSWM_ANDROID:
    case SDL_SYSWM_VIVANTE:
    case SDL_SYSWM_OS2:
    case SDL_SYSWM_HAIKU:
    case SDL_SYSWM_KMSDRM:
    case SDL_SYSWM_RISCOS:
    default:
        return make_unexpected("Window system not implemented");
    }
}

} // namespace passionfruit::seed