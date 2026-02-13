install(
    TARGETS CHIP8_EMULATOR_exe
    RUNTIME COMPONENT CHIP8_EMULATOR_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
