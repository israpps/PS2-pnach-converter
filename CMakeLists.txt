# begin basic metadata
# minimum CMake version required for C++20 support, among other things
cmake_minimum_required(VERSION 3.15)

# detect if MyHovercraftIsFullOfEels is being used as a sub-project of another CMake project
if(NOT DEFINED PROJECT_NAME)
    set(WX_WIDGETS_TEST_SUBPROJECT OFF)
else()
    set(WX_WIDGETS_TEST_SUBPROJECT ON)
endif()

project(wx-widgets-test VERSION 0.4.1 LANGUAGES CXX)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# set some handy custom variables to detect Release-type builds from Debug-type ones
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(WX_WIDGETS_TEST_BUILD_DEBUG ON)
    set(WX_WIDGETS_TEST_BUILD_RELEASE OFF)
else()
    set(WX_WIDGETS_TEST_BUILD_DEBUG OFF)
    set(WX_WIDGETS_TEST_BUILD_RELEASE ON)
endif()

message(STATUS "[wx-widgets-test] Build Mode: ${CMAKE_BUILD_TYPE}")

# set the C++ standard to use to C++20 always
set(WX_WIDGETS_TEST_CXX_STANDARD "20")
message(STATUS "[wx-widgets-test] C++ Standard set to C++${WX_WIDGETS_TEST_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD ${WX_WIDGETS_TEST_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# end basic metadata

# This is a special target which only exists to capture compilation options
# used for wx-widgets-test and its tests. This is to avoid setting global compiler
# options which would be inherited by dependencies as well, which is bad
# because wx-widgets-test uses strict compiler warning options which not all other
# projects can build successfully with.
# Any target linked with this one will inherit the compiler options used for
# wx-widgets-test.
add_library(wx-widgets-test-compiler-options INTERFACE)

# used for enabling additional compiler options if supported
include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    message(STATUS "[wx-widgets-test] Checking if compiler supports warning flag '${flag}'")
    check_cxx_compiler_flag("${flag}" flag_supported)
    if(flag_supported)
        message(STATUS "[wx-widgets-test] Enabling warning flag '${flag}'")
        target_compile_options(wx-widgets-test-compiler-options INTERFACE "${flag}")
    endif()
    unset(flag_supported CACHE)
endfunction()

# enable a large amount of extra warnings, regardless of build mode
if (MSVC) # MSVC supports different warning options to GCC/Clang
    enable_cxx_compiler_flag_if_supported("/W3")  # set warning level 3
    # if tests are enabled, enable converting all warnings to errors too
    if (ENABLE_TESTS)
        # add_compile_options(/WX)
        enable_cxx_compiler_flag_if_supported("/WX")
    endif()
else() # GCC/Clang warning option
    # NOTE: GCC and Clang support most of the same options, but neither supports all
    # of the others'. By only enabling them if supported, we get graceful failure
    # when trying to enable unsupported flags
    # e.g. at the time of writing, GCC does not support -Wdocumentation
    #
    # enable all warnings about 'questionable constructs'
    enable_cxx_compiler_flag_if_supported("-Wall")
    # issue 'pedantic' warnings for strict ISO compliance
    enable_cxx_compiler_flag_if_supported("-pedantic")
    # enable 'extra' strict warnings
    enable_cxx_compiler_flag_if_supported("-Wextra")
    # enable sign conversion warnings
    enable_cxx_compiler_flag_if_supported("-Wsign-conversion")
    # enable warnings about mistakes in Doxygen documentation
    enable_cxx_compiler_flag_if_supported("-Wdocumentation")
    # if tests are enabled, enable converting all warnings to errors too
    if (ENABLE_TESTS)
        enable_cxx_compiler_flag_if_supported("-Werror")
        # exclude the following kinds of warnings from being converted into errors
        # unknown-pragma is useful to have as a warning but not as an error, if you have
        # pragmas which are for the consumption of one compiler only
        enable_cxx_compiler_flag_if_supported("-Wno-error=unknown-pragmas")
        # unused variable and function warnings are helpful but we don't need them as errors
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-function")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-variable")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-parameter")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-private-field")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-but-set-variable")
    endif()
endif()

# add custom dependencies directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# a better way to load dependencies
include(CPM)

# add wxWidgets as dependency
CPMFindPackage(
    NAME wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
    GIT_TAG v3.1.6
    EXCLUDE_FROM_ALL YES
)

add_executable(demo WIN32 main.cpp)
# target_link_libraries(demo PRIVATE wx-widgets-test-compiler-options)
target_link_libraries(demo PRIVATE wx::net wx::core wx::base)
