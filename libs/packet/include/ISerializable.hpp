#ifndef ISERIALIZABLE_HPP_
#define ISERIALIZABLE_HPP_

#include <cstdint>
#include <memory>

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class ISerializable
{
public:
  virtual ~ISerializable()
  {
  }

  virtual std::unique_ptr<std::uint8_t[]>
      serialize(std::size_t &sizeToFill) const = 0;

  virtual void deserialize(std::size_t size, std::uint8_t *data) = 0;
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ISERIALIZABLE_HPP_
