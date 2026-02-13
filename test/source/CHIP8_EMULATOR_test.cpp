#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "CHIP8_EMULATOR" ? 0 : 1;
}
