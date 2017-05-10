#include "packet_stdafx.hpp"

GameClientToCMPacket::GameClientToCMPacket() : pck(), __padding()
{
}

std::unique_ptr<std::uint8_t[]>
    GameClientToCMPacket::serialize(std::size_t &sizeToFill) const
{
  // Set up cursor
  std::size_t cursor = sizeToFill;
  sizeToFill += sizeof(GameClientToCMPacket);

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> serial =
      std::make_unique<std::uint8_t[]>(sizeToFill);

  // Fill buffer
  std::memcpy(&serial[cursor], &pck, sizeof(GameClientToCMPacketRaw));

  GameClientToCMPacketRaw *data =
      reinterpret_cast<GameClientToCMPacketRaw *>(&serial[cursor]);
  data->eventType = static_cast<GameClientToCMEvent>(
      htons(static_cast<std::uint16_t>(data->eventType)));

  if (pck.eventType == GameClientToCMEvent::INT_EVENT)
    {
      data->eventData.intEvent.event = htons(data->eventData.intEvent.event);
    }
  else if (pck.eventType == GameClientToCMEvent::SERVER_STATUS_EVENT)
    {
      data->eventData.status.port = htons(data->eventData.status.port);
      data->eventData.status.currentClients =
          htons(data->eventData.status.currentClients);
      data->eventData.status.maxClients =
          htons(data->eventData.status.maxClients);
    }

  return (serial);
}

void GameClientToCMPacket::deserialize(std::size_t, std::uint8_t *data)
{
  std::memcpy(&pck, data, sizeof(pck));

  pck.eventType = static_cast<GameClientToCMEvent>(
      ntohs(static_cast<std::uint16_t>(pck.eventType)));
  if (pck.eventType == GameClientToCMEvent::INT_EVENT)
    {
      pck.eventData.intEvent.event = ntohs(pck.eventData.intEvent.event);
    }
  else if (pck.eventType == GameClientToCMEvent::SERVER_STATUS_EVENT)
    {
      pck.eventData.status.port = ntohs(pck.eventData.status.port);
      pck.eventData.status.currentClients =
          htons(pck.eventData.status.currentClients);
      pck.eventData.status.maxClients = htons(pck.eventData.status.maxClients);
    }
  else
    {
      throw std::runtime_error("Invalid packet received");
    }
}
