find_package(SDL2 REQUIRED)

include(FetchContent)

if(NOT TARGET nonstd::expected-lite)
FetchContent_Declare(
    expected-lite
    GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    SYSTEM            # Don't include in warnings
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(expected-lite)
endif()