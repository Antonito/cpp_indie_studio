#ifndef GAMECLIENT_CM_PACKET_HPP_
#define GAMECLIENT_CM_PACKET_HPP_

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

enum class GameClientToCMEvent : std::uint16_t
{
  REQUEST_EVENT = 0,
  SERVER_STATUS_EVENT,
  LIST_SERVERS_EVENT
};

enum class GameClientToCMPacketSimpleEvent : std::uint16_t
{
  LIST_SERVERS = 0xAB,
  GET_TOKEN
};

struct GameClientToCMPacketSimple
{
  std::uint16_t event;
};

struct GameClientToCMPacketIP
{
  // constexpr static std::size_t buffSize = IP_SIZE;
  std::array<char, INET6_ADDRSTRLEN> data;
};

struct GameClientToCMPacketStatus
{
  GameClientToCMPacketIP ip;
  std::uint16_t          port;
  std::uint16_t          currentClients;
  std::uint16_t          maxClients;
};

struct GameClientToCMPacketServerList
{
  std::int32_t                nbServers;
  GameClientToCMPacketStatus *servers;
};

struct GameClientToCMPacketRaw
{
  GameClientToCMEvent eventType;
  union
  {
    GameClientToCMPacketSimple     intEvent;
    GameClientToCMPacketStatus     status;
    GameClientToCMPacketServerList serverList;
  } eventData;
};

struct GameClientToCMPacket : public ISerializable
{
  GameClientToCMPacket();
  GameClientToCMPacketRaw pck;

  virtual std::unique_ptr<std::uint8_t[]>
      serialize(std::size_t &sizeToFill) const;

  virtual void deserialize(std::size_t size, std::uint8_t *data);

private:
  std::array<std::uint8_t, 2> __padding;
};

namespace packetSize
{
  constexpr std::size_t GameClientToCMPacketSize =
      sizeof(PacketHeader) + sizeof(GameClientToCMPacket);
}

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAMECLIENT_CM_PACKET_HPP_
