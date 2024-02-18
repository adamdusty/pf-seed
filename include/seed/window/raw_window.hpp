#pragma once

#include <variant>

#include "seed/export.hpp"

namespace passionfruit::seed {

struct android_window {
    void* window;
};

struct html_canvas {
    char* selector;
};

struct metal_layer {
    void* layer;
};

struct wayland_surface {
    void* display;
    void* surface;
};

struct hwnd {
    void* hwnd;
    void* hinstance;
};

struct xcb_window {
    void* connection;
    void* window;
};

struct xlib_window {
    void* display;
    void* window;
};

using raw_window =
    std::variant<android_window, html_canvas, metal_layer, wayland_surface, hwnd, xcb_window, xlib_window>;

} // namespace passionfruit::seed