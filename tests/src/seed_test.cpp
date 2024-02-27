#include <chrono>
#include <seed/seed.hpp>
#include <snitch/snitch.hpp>

using namespace passionfruit::seed;

TEST_CASE("Window create", "[window]") {
    auto wco = window_create_options{
        .title    = "Test window",
        .width    = 640,
        .height   = 480,
        .flags    = window_flags::hidden,
        .position = {window_position::centered, window_position::centered},
    };

    auto window_create_result = window::create(wco);
    REQUIRE(window_create_result);

    auto window = std::move(*window_create_result);
    CHECK(window);
}

TEST_CASE("Window size", "[window]") {
    auto wco = window_create_options{
        .title    = "Test window",
        .width    = 640,
        .height   = 480,
        .flags    = window_flags::hidden,
        .position = {window_position::centered, window_position::centered},
    };

    auto window_create_result = window::create(wco);
    REQUIRE(window_create_result);

    auto window = std::move(*window_create_result);
    REQUIRE(window);

    auto [w, h] = window.size();
    CHECK(w == 640);
    CHECK(h == 480);

    window.size(1920, 1080);
    auto [x, y] = window.size();
    CHECK(x == 1920);
    CHECK(y == 1080);
}