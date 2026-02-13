cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CHIP8_EMULATOR
    VERSION 0.1.0
    DESCRIPTION "CHIP8 interpreter"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    CHIP8_EMULATOR_lib OBJECT
    source/lib.cpp
    source/application.cpp
    source/chip8.cpp
    source/chip8_impl.cpp
)

target_include_directories(
    CHIP8_EMULATOR_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(CHIP8_EMULATOR_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(CHIP8_EMULATOR_exe source/main.cpp)
add_executable(CHIP8_EMULATOR::exe ALIAS CHIP8_EMULATOR_exe)

set_property(TARGET CHIP8_EMULATOR_exe PROPERTY OUTPUT_NAME CHIP8_EMULATOR)

target_compile_features(CHIP8_EMULATOR_exe PRIVATE cxx_std_20)

find_package(SDL2 REQUIRED)

target_link_libraries(CHIP8_EMULATOR_exe PRIVATE CHIP8_EMULATOR_lib ${SDL2_LIBRARIES})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CHIP8_EMULATOR_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CHIP8_EMULATOR"
  )
endif()

include(cmake/dev-mode.cmake)
