cmake_minimum_required(VERSION 3.16)
project(tcpip_c LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall -Wextra -Werror -Wpedantic
    -O0 -g
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
  add_compile_definitions(DEBUG)
endif()

# -----------------------------
# Core Library
# -----------------------------
add_library(tcpip_core STATIC
  src/debug.c
  src/icmp.c
  src/ip.c
  src/netdev.c
)

target_include_directories(tcpip_core PUBLIC include)

# -----------------------------
# Main Executable
# -----------------------------
add_executable(tcpip src/main.c)
target_link_libraries(tcpip PRIVATE tcpip_core)

# -----------------------------
# Test Executable
# -----------------------------
# add_executable(tcpip_test
#   tests/netdev_test.c
# )
# target_include_directories(tcpip_test PRIVATE tests)
# target_link_libraries(tcpip_test PRIVATE tcpip_core)
