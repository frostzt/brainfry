cmake_minimum_required(VERSION 3.14)
project(perfkit VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# header lib so
add_library(perfkit INTERFACE)
target_include_directories(perfkit INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_features(perfkit INTERFACE cxx_std_17)

# install targets
install(TARGETS perfkit EXPORT perfkitTargets)
install(DIRECTORY include/perfkit DESTINATION include)
install(EXPORT perfkitTargets
  FILE perfkitConfig.cmake
  NAMESPACE perfkit::
  DESTINATION lib/cmake/perfkit
)

# tests
option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
enable_testing()
add_subdirectory(tests)
endif()
