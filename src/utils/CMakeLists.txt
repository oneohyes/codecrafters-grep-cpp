# Utils library
file(GLOB_RECURSE UTILS_SOURCES
    "*.cpp"
    "*.hpp"
)

# Create a library for utils
add_library(utils STATIC ${UTILS_SOURCES})

target_include_directories(utils
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set C++ standard for the utils target
target_compile_features(utils PRIVATE cxx_std_23)

# Enable warnings
if(MSVC)
    target_compile_options(utils PRIVATE /W4 /WX)
else()
    target_compile_options(utils PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()