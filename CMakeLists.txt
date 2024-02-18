cmake_minimum_required(VERSION 3.27)

project(
    seed
    VERSION 0.1.0
    DESCRIPTION "A short description"
    LANGUAGES CXX
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)

# Declare library
add_library(passionfruit_seed)
add_library(passionfruit::seed ALIAS passionfruit_seed)

# Add sources
target_sources(passionfruit_seed PRIVATE
    src/seed.cpp
    src/window/window.cpp
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(
    passionfruit_seed ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

# Import export.hpp
target_include_directories(
    passionfruit_seed SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)

# Include and link dependencies
target_link_libraries(passionfruit_seed
    PUBLIC
        adizzle::adizzle
        nonstd::expected-lite
        SDL2::SDL2
)

# Add compile options
add_dev_compile_opts(passionfruit_seed)

# Generate header for export
include(GenerateExportHeader)
generate_export_header(
    passionfruit_seed
    BASE_NAME seed
    EXPORT_FILE_NAME include/seed/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# Set properties
set_target_properties(
    passionfruit_seed PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME seed
    OUTPUT_NAME seed
)

# Install rules
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# Enable testing
if(BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
endif()