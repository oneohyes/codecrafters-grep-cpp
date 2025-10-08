cmake_minimum_required(VERSION 3.14)  # Required for FetchContent

project(grep-starter-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)  # Enable the C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add utils library
add_subdirectory(src/utils)

# Main executable
file(GLOB SOURCE_FILES 
    src/*.cpp 
    src/*.hpp
)

if(SOURCE_FILES)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} PRIVATE utils)
endif()

# Tests
option(BUILD_TESTS "Build tests" ON)

enable_testing()

if(BUILD_TESTS)
    # Add tests for utils
    add_subdirectory(test/utils)

    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS utils_tests
    )
endif()