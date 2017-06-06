#include "GameClientGSPacket.hpp"
#include "GameClient.hpp"

GameClient::GameClient(sock_t const fd)
    : m_sock(fd), m_canWrite(false), m_state(GameClient::State::CONNECTED)
{
}

GameClient::~GameClient()
{
}

bool GameClient::disconnect()
{
  nope::log::Log(Debug) << "GameClient disconnected #" << getSocket();
  m_sock.closeConnection();
  return (true);
}

network::IClient::ClientAction GameClient::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_sock.send(data, sizeToWrite) == false)
    {
      nope::log::Log(Debug) << "Failed to write data [GameClient]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

network::IClient::ClientAction GameClient::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  std::size_t const buffSize = packetSize::GameClientToGSPacketSize;

  // Allocate buffer
  std::unique_ptr<uint8_t[]> buff = std::make_unique<std::uint8_t[]>(buffSize);
  ssize_t                    buffLen = 0;

  if (m_sock.rec(buff.get(), buffSize, &buffLen))
    {
      assert(buffLen >= 0);
      if (buffLen == 0)
	{
	  nope::log::Log(Debug)
	      << "Read failed, shall disconnect [GameClient]";
	  ret = network::IClient::ClientAction::DISCONNECT;
	}
      else
	{
	  ret = network::IClient::ClientAction::SUCCESS;
	  pck.setData(static_cast<std::size_t>(buffLen), std::move(buff));
	}
    }
  return (ret);
}

bool GameClient::hasTimedOut() const
{
  // TODO
  return (false);
}

sock_t GameClient::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameClient::canWrite() const
{
  return (m_canWrite);
}

network::IClient::ClientAction GameClient::treatIncomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::AUTHENTICATED:
      break;
    }
  return (ret);
}

network::IClient::ClientAction GameClient::treatOutgoingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::AUTHENTICATED:
      break;
    }
  return (ret);
}

bool GameClient::operator==(GameClient const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}
