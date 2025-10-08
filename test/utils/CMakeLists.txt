# Utils test executable
file(GLOB_RECURSE TEST_SOURCES
    "*.cpp"
)

find_package(GTest CONFIG REQUIRED)

# Create test executable
add_executable(utils_tests
    ${TEST_SOURCES}
)

set_target_properties(utils_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)

# Link against the utils library and GTest
target_link_libraries(utils_tests PRIVATE
    utils
    GTest::gtest
    GTest::gtest_main
)

# Include directories
target_include_directories(utils_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(utils_tests)

# Enable C++23 for tests
target_compile_features(utils_tests PRIVATE cxx_std_23)

# Enable warnings for tests
if(MSVC)
    target_compile_options(utils_tests PRIVATE /W4 /WX)
else()
    target_compile_options(utils_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()