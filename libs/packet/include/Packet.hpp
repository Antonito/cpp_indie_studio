#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <memory>
#include <type_traits>
#include <cstring>
#include "IPacket.hpp"
#include "ISerializable.hpp"
#include "GenNetwork.hpp"

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

    header->magic.__data._magic = PacketHeader::Magic;
    header->magic.__data.vers = PacketHeader::Version;
    header->magic.magic =
        static_cast<std::uint16_t>(htons(header->magic.magic));

    header->size =
        static_cast<std::uint16_t>(htons(m_size - sizeof(m_header)));

    header->checkSum = calculateChecksum(m_size - sizeof(m_header),
                                         m_data.get() + sizeof(m_header));
    header->checkSum = static_cast<std::uint16_t>(htons(header->checkSum));
  }

  void getPacket(T &obj)
  {
    // Fill header
    PacketHeader *header = reinterpret_cast<PacketHeader *>(m_data.get());

    m_header.magic.magic = ntohs(header->magic.magic);
    if (m_header.getMagic() != PacketHeader::Magic)
      {
	throw std::runtime_error("Magic number is invalid");
      }
    else if (m_header.getVersion() != PacketHeader::Version)
      {
	throw std::runtime_error("Invalid packet version");
      }
    m_header.size = ntohs(header->size);
    m_header.checkSum = ntohs(header->checkSum);
    obj.deserialize(m_size - sizeof(m_header),
                    m_data.get() + sizeof(m_header));
    std::uint16_t foundCheckSum = calculateChecksum(
        m_size - sizeof(m_header), m_data.get() + sizeof(m_header));
    if (m_header.checkSum != foundCheckSum)
      {
	throw std::runtime_error("Invalid packet : checksum is incorrect");
      }
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
  static std::uint16_t calculateChecksum(std::size_t const   size,
                                         std::uint8_t const *data)
  {
    std::size_t sum = 0;

    for (std::size_t i = 0; i < size; ++i)
      {
	sum += data[i];
      }
    return (sum & 0xFFFF);
  }

  std::size_t                     m_size;
  std::unique_ptr<std::uint8_t[]> m_data;
  PacketHeader                    m_header;
};

#endif // !PACKET_HPP_
