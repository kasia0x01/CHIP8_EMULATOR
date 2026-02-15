#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <filesystem>

#include "chip8.h"

#include "chip8_impl.h"

std::map<char, int> CHIP8::keyLayout_ = {
    {'1', 0},  // 1
    {'2', 1},  // 2
    {'3', 2},  // 3
    {'4', 3},  // c
    {'q', 4},  // 4
    {'w', 5},  // 5
    {'e', 6},  // 6
    {'r', 7},  // d
    {'a', 8},  // 7
    {'s', 9},  // 8
    {'d', 10},  // 9
    {'f', 11},  // e
    {'z', 12},  // a
    {'x', 13},  // 0
    {'c', 14},  // b
    {'v', 15}  // f
};

CHIP8::CHIP8()
    : impl_(std::make_unique<CHIP8_impl>())
{
}

CHIP8::~CHIP8() = default;

void CHIP8::display() const
{
  impl_->display();
}

bool CHIP8::loadROM(const std::string& filePath)
{
  namespace fs = std::filesystem;

  std::error_code ec;

  if (!fs::exists(filePath, ec)) {
    if (ec) {
      std::cerr << "Error checking file: " << ec.message() << std::endl;
    } else {
      std::cerr << "Error: File not found: " << filePath << std::endl;
    }
    return false;
  }

  auto fileSize = fs::file_size(filePath, ec);
  if (ec) {
    std::cerr << "Error getting file size: " << ec.message() << std::endl;
    return false;
  }

  constexpr std::streamsize MAX_ROM_SIZE = CHIP8_defs::MEM_SIZE - CHIP8_defs::START_ADDRESS;
  if (fileSize > MAX_ROM_SIZE) {
    std::cerr << "Error: ROM too large (" << fileSize
              << " bytes, max " << MAX_ROM_SIZE << ")" << std::endl;
    return false;
  }

  if (fileSize == 0) {
    std::cerr << "Error: ROM file is empty" << std::endl;
    return false;
  }

  std::ifstream in;
  in.open(filePath, std::ios::in | std::ios::binary);

  if (!in.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return false;
  }

  in.read(reinterpret_cast<char*>(&impl_->mem_[CHIP8_defs::START_ADDRESS]),fileSize);
  in.close();

  return true;
}

void CHIP8::cycle()
{
  impl_->cycle();
}

bool CHIP8::displayUpdatePending() const
{
  return impl_->displayUpdatePending();
}

void CHIP8::clearDisplayUpdatePending()
{
  impl_->clearDisplayUpdatePending();
}

// Keypad                   Keyboard
//+-+-+-+-+                +-+-+-+-+
//|1|2|3|C|                |1|2|3|4|
//+-+-+-+-+                +-+-+-+-+
//|4|5|6|D|                |Q|W|E|R|
//+-+-+-+-+       =>       +-+-+-+-+
//|7|8|9|E|                |A|S|D|F|
//+-+-+-+-+                +-+-+-+-+
//|A|0|B|F|                |Z|X|C|V|
//+-+-+-+-+                +-+-+-+-+

void CHIP8::keyPressed(char c)
{
  std::cout << "Key pressed " << c << std::endl;

  int index = keyLayout_.at(c);
  impl_->keys_.at(index) = 1;
}

void CHIP8::keyReleased(char c)
{
  std::cout << "Key released " << c << std::endl;

  int index = keyLayout_.at(c);
  impl_->keys_.at(index) = 0;
}

size_t CHIP8::getHeight() const
{
  return CHIP8_defs::DISPLAY_HEIGHT;
}

size_t CHIP8::getWidth() const
{
  return CHIP8_defs::DISPLAY_WIDTH;
}

bool CHIP8::getPixelAt(size_t x, size_t y) const
{
  // std::cout << "x=" << x << " y=" << y << std::endl;

  size_t index = y * CHIP8_defs::DISPLAY_WIDTH + x;
  return (impl_->display_.at(index));
}
