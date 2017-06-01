#include "Logger.hpp"
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

  if (pck.eventType == GameClientToCMEvent::REQUEST_EVENT)
    {
      data->eventData.intEvent.event = htons(data->eventData.intEvent.event);
    }
  else if (pck.eventType == GameClientToCMEvent::LIST_SERVERS_EVENT)
    {
      for (std::int32_t i = 0; i < data->eventData.serverList.nbServers; ++i)
	{
	  GameClientToCMPacketStatus *cur =
	      &data->eventData.serverList.servers[i];

	  cur->port = htons(cur->port);
	  cur->currentClients = htons(cur->currentClients);
	  cur->maxClients = htons(cur->maxClients);
	}
      data->eventData.serverList.nbServers = static_cast<std::int32_t>(htonl(
          static_cast<std::uint32_t>(data->eventData.serverList.nbServers)));
    }

  return (serial);
}

void GameClientToCMPacket::deserialize(std::size_t, std::uint8_t *data)
{
  std::memcpy(&pck, data, sizeof(pck));

  pck.eventType = static_cast<GameClientToCMEvent>(
      ntohs(static_cast<std::uint16_t>(pck.eventType)));
  if (pck.eventType == GameClientToCMEvent::REQUEST_EVENT)
    {
      pck.eventData.intEvent.event = ntohs(pck.eventData.intEvent.event);
    }
  else if (pck.eventType == GameClientToCMEvent::LIST_SERVERS_EVENT)
    {
      pck.eventData.serverList.nbServers = static_cast<std::int32_t>(ntohl(
          static_cast<std::uint32_t>(pck.eventData.serverList.nbServers)));

      for (std::int32_t i = 0; i < pck.eventData.serverList.nbServers; ++i)
	{
	  GameClientToCMPacketStatus *cur =
	      &pck.eventData.serverList.servers[i];

	  cur->port = ntohs(cur->port);
	  cur->currentClients = ntohs(cur->currentClients);
	  cur->maxClients = ntohs(cur->maxClients);
	}
    }
  else
    {
      nope::log::Log(Error)
          << "Received Event: " << static_cast<std::int32_t>(pck.eventType);
      throw std::runtime_error("Invalid packet received");
    }
}
