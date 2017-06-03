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

// All the possible packets
enum class GameClientToCMEvent : std::uint16_t
{
  REQUEST_EVENT = 0,
  LIST_SERVERS_EVENT,
  GET_TOKEN_EVENT
};

// The possible REQUEST_EVENT events
enum class GameClientToCMPacketSimpleEvent : std::uint16_t
{
  LIST_SERVERS = 0xAB,
  GET_TOKEN
};

// Expected with REQUEST_EVENT packets
struct GameClientToCMPacketSimple
{
  std::uint16_t event;
};

// Expected with GET_TOKEN_EVENT packets
struct GameClientToCMPacketToken
{
  static constexpr std::size_t tokenLength = 40; // 40 is SHA-1 length
  std::uint16_t                valid;
  std::array<char, tokenLength> data;
};

// Contains an IP address
struct GameClientToCMPacketIP
{
  std::array<char, INET6_ADDRSTRLEN> data;
};

// Expected with REQUEST_EVENT packets when event is GET_TOKEN
struct GameClientToCMPacketTokenRequ
{
  GameClientToCMPacketSimple ev;
  GameClientToCMPacketIP     ip;
  std::uint16_t              port;
};

// Description of a server
struct GameClientToCMPacketStatus
{
  GameClientToCMPacketIP ip;
  std::uint16_t          port;
  std::uint16_t          currentClients;
  std::uint16_t          maxClients;
};

// Expected with LIST_SERVERS_EVENT packets
struct GameClientToCMPacketServerList
{
  static constexpr std::int32_t maxServers =
      64; // The maximum number of server you can discover with one request
  std::int32_t nbServers;
  std::array<GameClientToCMPacketStatus,
             GameClientToCMPacketServerList::maxServers>
      servers;
};

struct GameClientToCMPacketRaw
{
  GameClientToCMEvent eventType;
  union
  {
    GameClientToCMPacketSimple     intEvent;
    GameClientToCMPacketServerList serverList;
    GameClientToCMPacketTokenRequ  tokenRequ;
    GameClientToCMPacketToken      token;
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
