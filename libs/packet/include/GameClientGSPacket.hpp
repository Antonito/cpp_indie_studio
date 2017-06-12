#ifndef GAMECLIENT_GS_PACKET_HPP_
#define GAMECLIENT_GS_PACKET_HPP_

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
enum class GameClientToGSEvent : std::uint16_t
{
  TOKEN_EVENT,
  VALIDATION_EVENT,
  MD5_REQUEST,
  MD5_RESPONSE
};

// Expected with MD5_RESPONSE packets
struct GameClientToGSPacketMD5Resp
{
  std::array<char, 32> md5;
};

// Expected with MD5_REQUEST packets
struct GameClientToGSPacketMD5Requ
{
  static constexpr std::size_t fileLength = 256;
  // TODO: Add -> file or map
  std::array<char, fileLength> file;
};

// Expected with GET_TOKEN_EVENT packets
struct GameClientToGSPacketToken
{
  static constexpr std::size_t tokenLength = 40; // 40 is SHA-1 length
  std::array<char, tokenLength> data;
};

struct GameClientToGSPacketRaw
{
  GameClientToGSEvent eventType;
  union
  {
    std::uint16_t               valid;
    GameClientToGSPacketToken   token;
    GameClientToGSPacketMD5Requ md5requ;
    GameClientToGSPacketMD5Resp md5resp;
  } eventData;
};

struct GameClientToGSPacket : public ISerializable
{
  GameClientToGSPacket();
  GameClientToGSPacketRaw pck;

  virtual std::unique_ptr<std::uint8_t[]>
      serialize(std::size_t &sizeToFill) const;

  virtual void deserialize(std::size_t size, std::uint8_t *data);
};

namespace packetSize
{
  constexpr std::size_t GameClientToGSPacketSize =
      sizeof(PacketHeader) + sizeof(GameClientToGSPacket);
}

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAMECLIENT_GS_PACKET_HPP_
