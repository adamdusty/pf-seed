#include <chrono>
#include <seed/seed.hpp>
#include <snitch/snitch.hpp>
#include <thread>

using namespace passionfruit::seed;

TEST_CASE("Test case", "[greeting]") {
    auto wco = window_create_options{
        .title    = "Test window",
        .width    = 640,
        .height   = 480,
        .flags    = window_flags::hidden,
        .position = {window_position::centered, window_position::centered}
    };

    auto window_create_result = window::create(wco);
    REQUIRE(window_create_result);

    auto window = std::move(*window_create_result);
    CHECK(window);
}