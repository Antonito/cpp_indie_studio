#include "packet_stdafx.hpp"

constexpr std::size_t GameServerToCMPacketSimple::buffSize;

std::unique_ptr<std::uint8_t[]>
    GameServerToCMPacket::serialize(std::size_t &sizeToFill) const
{
  std::size_t cursor = sizeToFill;
  sizeToFill += sizeof(PacketHeader) + sizeof(GameServerToCMPacket);

  std::unique_ptr<std::uint8_t[]> serial = std::make_unique<std::uint8_t[]>(sizeToFill]);
  std::uint32_t toSend;

  // Convert to Big Endian
  magic = htons(magic);

  toSend = htonl(static_cast<uint32_t>(m_file.length()));
  std::memcpy(&serial[cursor], &toSend, sizeof(uint32_t));
  cursor += sizeof(uint32_t);

  std::memcpy(&serial[cursor], m_file.c_str(), m_file.length());
  cursor += m_file.length();

  toSend = htonl(static_cast<uint32_t>(m_info));
  std::memcpy(&serial[cursor], &toSend, sizeof(uint32_t));
  return (serial);
}

void deserialize(std::size_t size, std::uint8_t *data)
{
}
