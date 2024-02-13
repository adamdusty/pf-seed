#include "seed/window.hpp"

using nonstd::expected;

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

} // namespace passionfruit::seed