#ifndef GAMESERVER_CM_PACKET_HPP_
#define GAMESERVER_CM_PACKET_HPP_

#include <cstdint>
#include <cstddef>
#include <array>
#include "ISerializable.hpp"
#include "PacketHeader.hpp"

enum class GameServerToCMEvent : std::uint16_t
{
  STRINGIFIED_EVENT = 0,
  LICENCE_EVENT,
  NB_CLIENTS,
  REQUEST_TOKEN,
  TOKEN
};

struct GameServerToCMPacketSimple
{
  constexpr static std::size_t buffSize = 256;
  std::array<char, buffSize> data;
};

struct GameServerToCMPacketLicence
{
  GameServerToCMPacketSimple licence;
  std::uint16_t              port;
};

struct GameServerToCMPacketToken
{
  std::uint16_t port;
  std::uint16_t treated;
  std::array<char, 40> tokenData;
};

struct GameServerToCMPacketRaw
{
  GameServerToCMEvent eventType;
  union
  {
    GameServerToCMPacketSimple  string;
    GameServerToCMPacketLicence licence;
    GameServerToCMPacketToken   token;
    uint16_t                    nbClients;
  } eventData;
};

struct GameServerToCMPacket : public ISerializable
{
  GameServerToCMPacket();
  GameServerToCMPacketRaw pck;

  virtual std::unique_ptr<std::uint8_t[]>
      serialize(std::size_t &sizeToFill) const;

  virtual void deserialize(std::size_t size, std::uint8_t *data);

private:
  std::array<std::uint8_t, 4> __padding;
};

namespace packetSize
{
  constexpr std::size_t GameServerToCMPacketSize =
      sizeof(PacketHeader) + sizeof(GameServerToCMPacket);
}

#endif // !GAMESERVER_CM_PACKET_HPP_
