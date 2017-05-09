#include "packet_stdafx.hpp"

constexpr std::size_t GameServerToCMPacketSimple::buffSize;

GameServerToCMPacket::GameServerToCMPacket() : pck(), __padding()
{
}

std::unique_ptr<std::uint8_t[]>
    GameServerToCMPacket::serialize(std::size_t &sizeToFill) const
{
  // Set up cursor
  std::size_t cursor = sizeToFill;
  sizeToFill += sizeof(GameServerToCMPacket);

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> serial =
      std::make_unique<std::uint8_t[]>(sizeToFill);

  // Fill buffer
  std::memcpy(&serial[cursor], &pck, sizeof(GameServerToCMPacketRaw));

  GameServerToCMPacketRaw *data =
      reinterpret_cast<GameServerToCMPacketRaw *>(&serial[cursor]);
  data->eventType = static_cast<GameServerToCMEvent>(htons(data->eventType));

  if (pck.eventType == LICENCE_EVENT)
    {
      data->eventData.licence.port = htons(data->eventData.licence.port);
    }
  else if (pck.eventType == NB_CLIENTS)
    {
      data->eventData.nbClients = htons(data->eventData.nbClients);
    }

  return (serial);
}

void GameServerToCMPacket::deserialize(std::size_t, std::uint8_t *data)
{
  std::memcpy(&pck, data, sizeof(pck));

  pck.eventType = static_cast<GameServerToCMEvent>(ntohs(pck.eventType));
  if (pck.eventType == STRINGIFIED_EVENT)
    {
      ; // TODO : Do nothing
    }
  else if (pck.eventType == LICENCE_EVENT)
    {
      pck.eventData.licence.port = ntohs(pck.eventData.licence.port);
    }
  else if (pck.eventType == NB_CLIENTS)
    {
      pck.eventData.nbClients = ntohs(pck.eventData.nbClients);
    }
  else
    {
      throw std::runtime_error("Invalid packet received");
    }
}
