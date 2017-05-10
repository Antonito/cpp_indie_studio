#include "GameClient.hpp"

GameClient::GameClient(sock_t const fd)
    : m_sock(fd), m_write(false), m_state(State::CONNECTED)
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
  uint8_t const *                data = pck.getData();

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
  std::size_t const buffSize = packetSize::GameClientToCMPacketSize;

  // Allocate buffer
  std::unique_ptr<uint8_t[]> buff = std::make_unique<uint8_t[]>(buffSize);
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
	  pck.setData(static_cast<size_t>(buffLen), std::move(buff));
	}
    }
  return (ret);
}

bool GameClient::hasTimedOut() const
{
  // TODO
  return (false);
}

bool GameClient::operator==(GameClient const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}

std::int32_t GameClient::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameClient::canWrite() const
{
  return (m_write);
}

void GameClient::toggleWrite()
{
  m_write = !m_write;
}

network::IClient::ClientAction GameClient::treatIncomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  GameClientToCMPacket rep;

  switch (m_state)
    {
    case State::CONNECTED:
      {
        ret = read(m_packet);
	nope::log::Log(Debug) << "Reading in state CONNECTED [GameClient]";
        if (ret == network::IClient::ClientAction::SUCCESS)
        {
          m_packet >> rep;
          if (rep.pck.eventData.intEvent.event == 0)
          {
            m_state = Sate::STATUS;
          }
          else
          {
            nope::log::Log(Debug) << "Error in state CONNECTED, invalid "
              "payload, shall disconnect "
              "[GameClient]";
            return (network::IClient::ClientAction::DISCONNECT);
          }
        }
      }
      break;
    case State::AUTHENTICATED:
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
  {
    toggleWrite();
  }
  return (ret);
}

network::IClient::ClientAction GameClient::treatOutcomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  switch (m_state)
  {
    case State::CONNECTED:
      break;
    case State::STATUS:
      //for server in servers: send server
      m_state = Sate::CONNECTED;
      nope::log::Log(Info) << "GameClient " << getSocket()
        << " ServerList sent."; // TODO: Put here or output ?
      break;
  }
  if (ret == network::IClient::ClientAction::SUCCESS)
  {
    toggleWrite();
  }
  return (ret);
}
