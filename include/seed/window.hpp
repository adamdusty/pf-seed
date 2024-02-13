#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <nonstd/expected.hpp>
#include <seed/export.hpp>
#include <string>
#include <utility>
#include <variant>

namespace passionfruit::seed {

enum class SEED_EXPORT window_flags : std::uint32_t;

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
};

enum class SEED_EXPORT window_flags : std::uint32_t {
    fullscreen         = 0x00000001, /**< fullscreen window */
    opengl             = 0x00000002, /**< window usable with OpenGL context */
    shown              = 0x00000004, /**< window is visible */
    hidden             = 0x00000008, /**< window is not visible */
    borderless         = 0x00000010, /**< no window decoration */
    resizeable         = 0x00000020, /**< window can be resized */
    minimized          = 0x00000040, /**< window is minimized */
    maximized          = 0x00000080, /**< window is maximized */
    mouse_grabbed      = 0x00000100, /**< window has grabbed mouse input */
    input_focus        = 0x00000200, /**< window has input focus */
    mouse_focus        = 0x00000400, /**< window has mouse focus */
    fullscreen_desktop = (fullscreen | 0x00001000U),
    foreign            = 0x00000800, /**< window not created by SDL */
    allow_high_dpi     = 0x00002000, /**< window should be created in high-DPI mode if supported.
                                          On macOS NSHighResolutionCapable must be set true in the
                                          application's Info.plist for this to have any effect. */
    mouse_capture    = 0x00004000,   /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
    always_on_top    = 0x00008000,   /**< window should always be above others */
    skip_taskbar     = 0x00010000,   /**< window should not be added to the taskbar */
    utility          = 0x00020000,   /**< window should be treated as a utility window */
    tooltip          = 0x00040000,   /**< window should be treated as a tooltip */
    popup_menu       = 0x00080000,   /**< window should be treated as a popup menu */
    keyboard_grabbed = 0x00100000,   /**< window has grabbed keyboard input */
    vulkan           = 0x10000000,   /**< window usable for Vulkan surface */
    metal            = 0x20000000,   /**< window usable for Metal view */
};

constexpr auto operator&(window_flags lhs, window_flags rhs) -> window_flags {
    using T = std::underlying_type_t<window_flags>;
    return static_cast<window_flags>(static_cast<T>(lhs) & static_cast<T>(rhs));
}
constexpr auto operator|(window_flags lhs, window_flags rhs) -> window_flags {
    using T = std::underlying_type_t<window_flags>;
    return static_cast<window_flags>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

} // namespace passionfruit::seed