cmake_minimum_required(VERSION 3.15)
project(RobotArm)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)

option(CI_TEST_BUILD_TESTS "Build tests" ON)

# ==========================
# Testing
# ==========================

if (CI_TEST_BUILD_TESTS)

    #Download Catch2 unit-test framework from GitHub
    include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)

endif ()