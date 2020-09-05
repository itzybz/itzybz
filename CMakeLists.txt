cmake_minimum_required(VERSION 3.16)
project(itzybz VERSION 0.1.0 LANGUAGES C)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON CACHE BOOL "Prevents cmake -S. -B.")
set(CMAKE_DISABLE_SOURCE_CHANGES ON CACHE BOOL "Prevent writing files to CMAKE_SOURCE_DIR under configure")

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0075 NEW)

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_FIND_FRAMEWORK FIRST)

include(CMakeDependentOption)
include(GenerateExportHeader)
include(FetchContent)

# Enables debug output 
cmake_dependent_option(ITZY_DEBUG 
  "Build Itzy to debug" ON
  "CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME" ON)

# Enables building tests 
cmake_dependent_option(ITZY_BUILD_TESTS
  "Build Itzy's Tests" ON
  "CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME" ON)

# Enables linking ASAN for debugging
option(ITZY_ASAN OFF)

file(GLOB sources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.c)
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${sources})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INCLUDE_INSTALLDIR}>)
target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    $<$<BOOL:${ITZY_DEBUG}>:ITZY_DEBUG>)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)

# Add pedantic outputs 
target_compile_options(${PROJECT_NAME}
  PRIVATE
  $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
  $<$<C_COMPILER_ID:MSVC>:/WX /W4>)

# Enables ASAN
if(ITZY_ASAN)
  target_compile_options(${PROJECT_NAME}
    PUBLIC
    $<$<C_COMPILER_ID:MSVC>:/fsanitize=address>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>: -g -fsanitize=address -fno-omit-frame-pointer -O2 -g>)
  
  target_link_options(${PROJECT_NAME}
    PUBLIC
    $<$<C_COMPILER_ID:MSVC>:/fsanitize=address>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-g -fsanitize=address>)
endif()

if(ITZY_BUILD_TESTS)
  # Add the tests to be compiled
  add_subdirectory(tests)
endif()

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    $<$<NOT:$<PLATFORM_ID:Windows>>:m>)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_VISIBILITY_PRESET "hidden")
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})

install(TARGETS ${PROJECT_NAME} 
  EXPORT ${PROJECT_NAME}-targets
  INCLUDES DESTINATION "${CMAKE_INCLUDE_INSTALLDIR}")
install(EXPORT ${PROJECT_NAME}-targets 
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  NAMESPACE ${PROJECT_NAME})
install(DIRECTORY include/ "${PROJECT_BINARY_DIR}/include/"
  TYPE INCLUDE
  FILES_MATCHING PATTERN "*.h")
