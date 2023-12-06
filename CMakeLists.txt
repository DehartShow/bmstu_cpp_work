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
set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME} string_test.cpp bmstu_string/main.h
        dummy_vector/dummy_vector.h
        dummy_vector/array_bundle.h
        dummy_vector_test.cpp

)
target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
