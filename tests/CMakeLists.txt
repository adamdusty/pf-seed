cmake_minimum_required(VERSION 3.27)

project(
    seedTests
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(seed REQUIRED)
    enable_testing()
endif()

# Get the testing library
include(FetchContent)
FetchContent_Declare(
    snitch
    GIT_REPOSITORY https://github.com/snitch-org/snitch.git
    GIT_TAG        v1.2.4
    SYSTEM
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(snitch)

# Add test exe
add_executable(seed_tests)

# Add test sources
target_sources(seed_tests PRIVATE
    src/seed_test.cpp
)

# Link libs
target_link_libraries(seed_tests PRIVATE passionfruit::seed snitch::snitch)

# Add test
add_test(NAME seed_tests COMMAND seed_tests)

# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(seed_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:passionfruit::seed>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>;PATH=path_list_append:$<TARGET_FILE_DIR:SDL2::SDL2>"
    )
endif()
