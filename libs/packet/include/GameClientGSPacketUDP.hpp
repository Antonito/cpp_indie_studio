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

  GameClientToGSEventUDP eventType;
  union
  {
    int i; // TODO: rm
  } eventData;
};

struct GameClientToGSPacketUDP : public ISerializable
{
  GameClientToGSPacketUDP();
  GameClientToGSPacketUDP(GameClientToGSPacketUDP const &);
  GameClientToGSPacketUDPRaw pck;

  virtual std::unique_ptr<std::uint8_t[]>
      serialize(std::size_t &sizeToFill) const;

  virtual void deserialize(std::size_t size, std::uint8_t *data);
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
