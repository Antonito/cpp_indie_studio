#ifndef GAMECLIENT_GS_PACKET_UDP_HPP_
#define GAMECLIENT_GS_PACKET_UDP_HPP_

#include <cstdint>
#include <cstddef>
#include <array>
#include "ISerializable.hpp"
#include "PacketHeader.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// All the possible packets
enum class GameClientToGSEventUDP : std::uint16_t
{
  SIMPLE_EVENT = 0,
};

struct GameClientToGSPacketUDPRaw
{
  GameClientToGSPacketUDPRaw();
  GameClientToGSPacketUDPRaw(GameClientToGSPacketUDPRaw const &);

  GameClientToGSPacketUDPRaw &operator=(GameClientToGSPacketUDPRaw const &);

  std::array<std::uint32_t, 3> pos;
  std::array<std::uint32_t, 4> dir;
  std::uint32_t speed;
  std::uint16_t id;
  std::uint16_t playerCount;
};

struct GameClientToGSPacketUDP : public ISerializable
{
  GameClientToGSPacketUDP();
  GameClientToGSPacketUDP(GameClientToGSPacketUDP const &);
  GameClientToGSPacketUDP &  operator=(GameClientToGSPacketUDP const &);
  GameClientToGSPacketUDPRaw pck;

  virtual std::unique_ptr<std::uint8_t[]>
      serialize(std::size_t &sizeToFill) const;

  virtual void deserialize(std::size_t size, std::uint8_t *data);
  std::vector<float> getDirection() const;
  std::vector<float> getPosition() const;
  void setDirection(std::vector<float> const &quat);
  void setPosition(std::vector<float> const &vec);
  void reinit();
};

namespace packetSize
{
  constexpr std::size_t GameClientToGSPacketUDPSize =
      sizeof(PacketHeader) + sizeof(GameClientToGSPacketUDP);
}

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAMECLIENT_GS_PACKET_UDP_HPP_
