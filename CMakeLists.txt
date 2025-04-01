cmake_minimum_required(VERSION 3.10)
project(EmbeddedProjectQ2)

set(CMAKE_CXX_STANDARD 17)

# Inclure les headers
include_directories(SuperStar)
include_directories(/opt/homebrew/opt/googletest/include)
link_directories(/opt/homebrew/opt/googletest/lib)

# Tests à compiler
add_executable(AllTests
    Test/PIDTest.cpp
    Test/MotorsTest.cpp
    SuperStar/PID.cpp
    SuperStar/Motors.cpp
)

# Lier avec GoogleTest
target_link_libraries(AllTests gtest gtest_main)

