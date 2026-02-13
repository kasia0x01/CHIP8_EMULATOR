# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(CHIP8_EMULATORTests LANGUAGES CXX)

# ---- Tests ----

add_executable(CHIP8_EMULATOR_test source/CHIP8_EMULATOR_test.cpp)
target_link_libraries(CHIP8_EMULATOR_test PRIVATE CHIP8_EMULATOR_lib)
target_compile_features(CHIP8_EMULATOR_test PRIVATE cxx_std_20)

add_test(NAME CHIP8_EMULATOR_test COMMAND CHIP8_EMULATOR_test)

# ---- End-of-file commands ----

add_folders(Test)
