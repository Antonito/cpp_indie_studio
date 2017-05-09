#ifndef IPACKET_HPP_
#define IPACKET_HPP_

#include <cstdint>
#include <memory>

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class IPacket
{
public:
  virtual ~IPacket()
  {
  }
  virtual std::size_t   getSize() const = 0;
  virtual std::uint8_t *getData() const = 0;
  virtual void setData(std::size_t                     size,
                       std::unique_ptr<std::uint8_t[]> data) = 0;
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !IPACKET_HPP_
