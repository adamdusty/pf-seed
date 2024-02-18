include(FetchContent)

if(NOT TARGET adizzle::adizzle)

FetchContent_Declare(
    adizzle
    GIT_REPOSITORY https://github.com/adamdusty/adizzle.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
    SYSTEM
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(adizzle)

endif()

if(NOT TARGET nonstd::expected-lite)
FetchContent_Declare(
    expected-lite
    GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
    GIT_TAG        3634b0a6d8dffcffad4d1355253d79290c0c754c # master 2024/01/01
    GIT_SHALLOW    TRUE
    SYSTEM            # Don't include in warnings
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(expected-lite)
endif()

if(NOT TARGET SDL2::SDL2)
set(SDL_SHARED TRUE CACHE BOOL "Build a SDL shared library (if available)")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        7de4f16710ba9a83a6f3d5d932a11623df6676df # release-2.30.x XINPUT_CAPABILITIES fix
    SYSTEM            # Don't include in warnings
)
set(MESSAGE_QUIET ON)
FetchContent_MakeAvailable(SDL2)
unset(MESSAGE_QUIET)
endif()
