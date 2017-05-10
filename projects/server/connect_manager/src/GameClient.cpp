#include "GameClient.hpp"

GameClient::GameClient(sock_t const                    fd,
                       std::vector<std::string> const &gameServerList,
                       std::mutex &                    gameServerListMut)
    : m_sock(fd), m_write(false), m_state(State::CONNECTED),
      m_gameServerList(gameServerList), m_gameServerListMut(gameServerListMut)
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
  std::size_t const buffSize = packetSize::GameClientToCMPacketSize;

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
  // TODO : implemented timeout
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
  GameClientToCMPacket           rep;

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
		m_state = State::STATUS;
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
    case State::STATUS:
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
  GameClientToCMPacket           rep;

  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::STATUS:
      {
	// TODO modify the packet to set real info insteab of bebete string
	m_gameServerListMut.lock();
	for (std::uint32_t i = 0; i < m_gameServerList.size(); i++)
	  {
	    rep.pck.eventType = GameClientToCMEvent::SERVER_STATUS_EVENT;
	    /*rep.pck.eventData.status.port = htons(rep.pck.eventData.port);
	      rep.pck.eventData.status.nbClients = htons(rep.pck.eventData.port);*/
	    rep.pck.eventData.status.port = 0;
	    rep.pck.eventData.status.nbClients = 0;
	    GameClientToCMPacketIP &simple = rep.pck.eventData.status.ip;
	    std::memcpy(simple.data.data(), m_gameServerList[i].c_str(),
	                m_gameServerList.size());
	    m_packet << rep;
	    ret = write(m_packet);
	  }
	m_gameServerListMut.unlock();
	m_state = State::CONNECTED;
	nope::log::Log(Info)
	    << "GameClient " << getSocket()
	    << " ServerList sent."; // TODO: Put here or output ?
      }
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}
