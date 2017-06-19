#include "packet_stdafx.hpp"

GameClientToGSPacketUDP::GameClientToGSPacketUDP() : pck()
{
}

GameClientToGSPacketUDPRaw::GameClientToGSPacketUDPRaw()
    : eventType(GameClientToGSEventUDP::SIMPLE_EVENT), eventData{}
{
}

GameClientToGSPacketUDP::GameClientToGSPacketUDP(
    GameClientToGSPacketUDP const &other)
    : pck(other.pck)
{
}

GameClientToGSPacketUDPRaw::GameClientToGSPacketUDPRaw(
    GameClientToGSPacketUDPRaw const &other)
    : eventType(other.eventType), eventData(other.eventData)
{
}

std::unique_ptr<std::uint8_t[]>
    GameClientToGSPacketUDP::serialize(std::size_t &sizeToFill) const
{
  // Set up cursor
  std::size_t cursor = sizeToFill;
  sizeToFill += sizeof(GameClientToGSPacketUDP);

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> serial =
      std::make_unique<std::uint8_t[]>(sizeToFill);

  // Fill buffer
  std::memcpy(&serial[cursor], &pck, sizeof(GameClientToGSPacketUDPRaw));

  GameClientToGSPacketUDPRaw *data =
      reinterpret_cast<GameClientToGSPacketUDPRaw *>(&serial[cursor]);
  data->eventType = static_cast<GameClientToGSEventUDP>(
      htons(static_cast<std::uint16_t>(data->eventType)));
  return (serial);
}

void GameClientToGSPacketUDP::deserialize(std::size_t, std::uint8_t *data)
{
  std::memcpy(&pck, data, sizeof(pck));

  pck.eventType = static_cast<GameClientToGSEventUDP>(
      ntohs(static_cast<std::uint16_t>(pck.eventType)));
  if (pck.eventType == GameClientToGSEventUDP::SIMPLE_EVENT)
    {
    }
  else
    {
      throw std::runtime_error("Invalid packet received");
    }
}
