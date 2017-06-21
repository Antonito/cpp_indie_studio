#include "packet_stdafx.hpp"

GameClientToGSPacketUDP::GameClientToGSPacketUDP() : pck()
{
}

GameClientToGSPacketUDPRaw::GameClientToGSPacketUDPRaw()
    : pos(), dir(), speed(0), id(0), playerCount(0)
{
}

GameClientToGSPacketUDP::GameClientToGSPacketUDP(
    GameClientToGSPacketUDP const &other)
    : pck(other.pck)
{
}

GameClientToGSPacketUDP &GameClientToGSPacketUDP::
    operator=(GameClientToGSPacketUDP const &other)
{
  if (&other != this)
    {
      pck = other.pck;
    }
  return (*this);
}

GameClientToGSPacketUDPRaw::GameClientToGSPacketUDPRaw(
    GameClientToGSPacketUDPRaw const &other)
    : pos(other.pos), dir(other.dir), speed(other.speed), id(other.id),
      playerCount(other.playerCount)
{
}

GameClientToGSPacketUDPRaw &GameClientToGSPacketUDPRaw::
    operator=(GameClientToGSPacketUDPRaw const &other)
{
  if (this != &other)
    {
      pos = other.pos;
      dir = other.dir;
      speed = other.speed;
      id = other.id;
      playerCount = other.playerCount;
    }
  return (*this);
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
  for (std::uint32_t &pos : data->pos)
    {
      pos = htonl(static_cast<std::uint32_t>(pos));
    }
  for (std::uint32_t &dir : data->dir)
    {
      dir = htonl(static_cast<std::uint32_t>(dir));
    }
  data->speed = htonl(static_cast<std::uint32_t>(data->speed));
  data->id = htons(data->id);
  data->playerCount = htons(data->playerCount);
  return (serial);
}

void GameClientToGSPacketUDP::deserialize(std::size_t, std::uint8_t *data)
{
  std::memcpy(&pck, data, sizeof(pck));

  for (std::uint32_t &pos : pck.pos)
    {
      pos = ntohl(static_cast<std::uint32_t>(pos));
    }
  for (std::uint32_t &dir : pck.dir)
    {
      dir = ntohl(static_cast<std::uint32_t>(dir));
    }
  pck.speed = ntohl(static_cast<std::uint32_t>(pck.speed));
  pck.id = ntohs(pck.id);
  pck.playerCount = ntohs(pck.playerCount);
}

std::vector<float> GameClientToGSPacketUDP::getDirection() const
{
  std::vector<float> quat;

  quat.push_back(static_cast<float>(static_cast<std::int32_t>(pck.dir[0])) /
                 1000.0f);
  quat.push_back(static_cast<float>(static_cast<std::int32_t>(pck.dir[1])) /
                 1000.0f);
  quat.push_back(static_cast<float>(static_cast<std::int32_t>(pck.dir[2])) /
                 1000.0f);
  quat.push_back(static_cast<float>(static_cast<std::int32_t>(pck.dir[3])) /
                 1000.0f);

  return quat;
}

std::vector<float> GameClientToGSPacketUDP::getPosition() const
{
  std::vector<float> vec;

  vec.push_back(static_cast<float>(static_cast<std::int32_t>(pck.pos[0])) /
                1000.0f);
  vec.push_back(static_cast<float>(static_cast<std::int32_t>(pck.pos[1])) /
                1000.0f);
  vec.push_back(static_cast<float>(static_cast<std::int32_t>(pck.pos[2])) /
                1000.0f);

  return vec;
}

void GameClientToGSPacketUDP::setDirection(std::vector<float> const &quat)
{
  pck.dir[0] = static_cast<std::uint32_t>(quat[0] * 1000.0f);
  pck.dir[1] = static_cast<std::uint32_t>(quat[1] * 1000.0f);
  pck.dir[2] = static_cast<std::uint32_t>(quat[2] * 1000.0f);
  pck.dir[3] = static_cast<std::uint32_t>(quat[3] * 1000.0f);
}

void GameClientToGSPacketUDP::setPosition(std::vector<float> const &vec)
{
  pck.pos[0] = static_cast<std::uint32_t>(vec[0] * 1000.0f);
  pck.pos[1] = static_cast<std::uint32_t>(vec[1] * 1000.0f);
  pck.pos[2] = static_cast<std::uint32_t>(vec[2] * 1000.0f);
}

void GameClientToGSPacketUDP::reinit()
{
  pck = GameClientToGSPacketUDPRaw();
}
