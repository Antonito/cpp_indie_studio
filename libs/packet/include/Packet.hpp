#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <memory>
#include <type_traits>
#include <cstring>
#include "IPacket.hpp"
#include "ISerializable.hpp"

template <typename T>
class Packet : public IPacket
{
  // Small check
  static_assert(std::is_base_of<ISerializable, T>(),
                "Type is not an ISerializable");

public:
  Packet() : m_size(0), m_data(), m_header()
  {
  }

  Packet(Packet const &other)
      : m_size(other.m_size), m_data(new std::uint8_t[m_size]),
        m_header(other.m_header)
  {
    std::memcpy(m_data.get(), other.m_data.get(), m_size);
  }

  Packet(Packet &&other)
      : m_size(other.m_size), m_data(std::move(other.m_data)),
        m_header(other.m_header)
  {
    other.m_size = 0;
  }

  explicit Packet(T const &obj) : m_size(0), m_data(), m_header()
  {
    this->fillData(obj);
  }

  virtual ~Packet()
  {
  }

  Packet &operator=(Packet const &other)
  {
    if (this == &other)
      return (*this);
    m_size = other.m_size;
    m_data = std::make_unique<std::uint8_t[]>(m_size);
    std::memcpy(m_data.get(), other.m_data.get(), m_size);
    return (*this);
  }

  Packet &operator=(Packet &&other)
  {
    if (this == &other)
      return (*this);
    m_size = other.m_size;
    m_data = std::move(m_data);
    other.m_size = 0;
    return (*this);
  }

  Packet &operator=(T const &obj)
  {
    this->fillData(obj);
    return (*this);
  }

  void fillPacket(T const &obj)
  {
    m_size = sizeof(m_header);
    m_data = obj.serialize(m_size);

    PacketHeader *header = reinterpret_cast<PacketHeader *>(m_data.get());

    header->magic.__data._magic = 0x1D;
    header->magic.__data.vers = 0; // TODO: Change version here
    header->magic.magic =
        static_cast<std::uint16_t>(htons(header->magic.magic));

    header->size =
        static_cast<std::uint16_t>(htons(m_size - sizeof(m_header)));

    // TODO: calculate checksum
    header->checkSum = 0;
    header->checkSum = static_cast<std::uint16_t>(htons(header->checkSum));
  }

  void getPacket(T &obj)
  {
    // Fill header
    PacketHeader *header = reinterpret_cast<PacketHeader *>(m_data.get());

    m_header.magic.magic = ntohs(header->magic.magic);
    m_header.size = ntohs(header->size);
    m_header.checkSum = ntohs(header->checkSum);
    obj.deserialize(m_size - sizeof(m_header),
                    m_data.get() + sizeof(m_header));
    // TODO : Check checksum
  }

  Packet &operator<<(T const &obj)
  {
    this->fillPacket(obj);
    return (*this);
  }

  Packet &operator>>(T &obj)
  {
    this->getPacket(obj);
    return (*this);
  }

  virtual std::size_t getSize() const
  {
    return (m_size);
  }

  virtual std::uint8_t *getData() const
  {
    return (m_data.get());
  }

  virtual void setData(std::size_t size, std::unique_ptr<std::uint8_t[]> data)
  {
    m_size = size;
    m_data = std::move(data);
  }

private:
  std::size_t                     m_size;
  std::unique_ptr<std::uint8_t[]> m_data;
  PacketHeader                    m_header;
};

#endif // !PACKET_HPP_
