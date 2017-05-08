#ifndef IPACKET_HPP_
#define IPACKET_HPP_

#include <cstdint>
#include <memory>

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

#endif // !IPACKET_HPP_
