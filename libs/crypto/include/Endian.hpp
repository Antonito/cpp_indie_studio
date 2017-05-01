#ifndef ENDIAN_HPP_
#define ENDIAN_HPP_

#include <cstdint>

namespace crypto
{
  // Simple endianness check
  class Endian
  {
  private:
    static constexpr std::uint32_t magicNumber = {0xAABBCCDD};

  public:
    Endian() = delete;
    static bool isLittle()
    {
      return (*reinterpret_cast<std::uint8_t const *>(&magicNumber) == 0xDD);
    }
    static bool isMiddle()
    {
      return (*reinterpret_cast<std::uint8_t const *>(&magicNumber) == 0xBB);
    }
    static bool isBig()
    {
      return (*reinterpret_cast<std::uint8_t const *>(&magicNumber) == 0xAA);
    }
  };
}

#endif // !ENDIAN_HPP_
