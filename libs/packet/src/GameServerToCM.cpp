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
  data->eventType = static_cast<GameServerToCMEvent>(
      htons(static_cast<std::uint16_t>(data->eventType)));

  if (pck.eventType == GameServerToCMEvent::LICENCE_EVENT)
    {
      data->eventData.licence.port = htons(data->eventData.licence.port);
      data->eventData.licence.maxClients =
          htons(data->eventData.licence.maxClients);
      data->eventData.licence.curClients =
          htons(data->eventData.licence.curClients);
    }
  else if (pck.eventType == GameServerToCMEvent::NB_CLIENTS)
    {
      data->eventData.nbClients = htons(data->eventData.nbClients);
    }
  else if (pck.eventType == GameServerToCMEvent::TOKEN)
    {
      data->eventData.token.port = htons(pck.eventData.token.port);
      data->eventData.token.treated = htons(pck.eventData.token.treated);
      data->eventData.token.curClients = htons(pck.eventData.token.curClients);
    }

  return (serial);
}

void GameServerToCMPacket::deserialize(std::size_t, std::uint8_t *data)
{
  std::memcpy(&pck, data, sizeof(pck));

  pck.eventType = static_cast<GameServerToCMEvent>(
      ntohs(static_cast<std::uint16_t>(pck.eventType)));
  if (pck.eventType == GameServerToCMEvent::STRINGIFIED_EVENT)
    {
      ; // TODO : Do nothing
    }
  else if (pck.eventType == GameServerToCMEvent::LICENCE_EVENT)
    {
      pck.eventData.licence.port = ntohs(pck.eventData.licence.port);
      pck.eventData.licence.maxClients =
          ntohs(pck.eventData.licence.maxClients);
      pck.eventData.licence.curClients =
          ntohs(pck.eventData.licence.curClients);
    }
  else if (pck.eventType == GameServerToCMEvent::NB_CLIENTS)
    {
      pck.eventData.nbClients = ntohs(pck.eventData.nbClients);
    }
  else if (pck.eventType == GameServerToCMEvent::REQUEST_TOKEN)
    {
      // Do nothing
    }
  else if (pck.eventType == GameServerToCMEvent::TOKEN)
    {
      pck.eventData.token.port = ntohs(pck.eventData.token.port);
      pck.eventData.token.treated = ntohs(pck.eventData.token.treated);
      pck.eventData.token.curClients = ntohs(pck.eventData.token.curClients);
    }
  else
    {
      throw std::runtime_error("Invalid packet received");
    }
}
