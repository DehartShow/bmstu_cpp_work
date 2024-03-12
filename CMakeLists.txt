cmake_minimum_required(VERSION 3.14)
project(example)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 23)

enable_testing()
include(GoogleTest)
file(GLOB hw_dirs RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*_hw)
message("hw_dirs: ${hw_dirs}")
add_subdirectory(${hw_dirs})