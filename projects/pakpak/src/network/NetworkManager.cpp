#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkManager::NetworkManager()
      : m_auth(false), m_connected(false), m_connectManagerAddr(),
        m_connectManagerPort(), m_connectManagerSocket(nullptr),
        m_gameServerToken("")
  {
    // TODO: Implement configuration
    // Load configuration here
    m_connectManagerAddr = Config::getInstance().getConnectManagerIp();
    m_connectManagerPort = Config::getInstance().getConnectManagerPort();
    nope::log::Log(Debug) << "NetworkManager started";
    nope::log::Log(Info) << "Serveur address: " << m_connectManagerAddr
                         << " : " << m_connectManagerPort;
  }

  NetworkManager::~NetworkManager()
  {
  }

  void NetworkManager::authenticate()
  {
    // TODO: Deconnect clients already connected
    if (m_auth)
      {
	nope::log::Log(Debug) << "Connection already exists, deleting it";
	m_auth.reset(nullptr);
      }

    m_auth = std::make_unique<NetworkAuth>(
        m_connectManagerPort, m_connectManagerAddr;
  }

  bool NetworkManager::isAuthenticated() const
  {
    if (!m_auth)
      {
	return (false);
      }
    return (m_auth->isAuthenticated());
  }

  void NetworkManager::disconnect()
  {
    // TODO
    if (m_auth)
      {
	m_auth->reset(nullptr);
      }
  }

  void NetworkManager::connect()
  {
    // TODO: Connect to a gameServer
  }

  bool NetworkManager::isConnected() const
  {
    return (m_connected);
  }
}
