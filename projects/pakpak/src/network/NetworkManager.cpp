#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkManager::NetworkManager()
      : m_auth(nullptr), m_connected(false), m_connectManagerAddr(),
        m_connectManagerPort(), m_gameServerToken("")
  {
    nope::log::Log(Debug) << "Creating NetworkManager";
    // Load configuration
    m_connectManagerAddr = Config::getInstance().getConnectManagerIp();
    m_connectManagerPort = Config::getInstance().getConnectManagerPort();
    nope::log::Log(Debug) << "NetworkManager started";
    nope::log::Log(Info) << "Serveur address: " << m_connectManagerAddr
                         << " : " << m_connectManagerPort;
  }

  NetworkManager::~NetworkManager()
  {
    nope::log::Log(Debug) << "Destroying NetworkManager";
  }

  void NetworkManager::authenticate()
  {
    nope::log::Log(Info) << "Starting connection to server.";
    deauthenticate();
    m_auth = std::make_unique<NetworkAuth>(m_connectManagerAddr,
                                           m_connectManagerPort);
  }

  void NetworkManager::deauthenticate()
  {
    nope::log::Log(Debug) << "De-authenticating client";
    if (m_auth)
      {
	m_auth.reset(nullptr);
      }
  }

  std::vector<GameServer> NetworkManager::getServerList()
  {
    nope::log::Log(Debug) << "Getting Game Server List";
    assert(m_auth != nullptr);
    return (m_auth->getServerList());
  }

  std::string const &NetworkManager::getToken(GameServer const &srv)
  {
    nope::log::Log(Debug) << "Getting Game Server Token";
    assert(m_auth != nullptr);
    return (m_auth->getToken(srv));
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
    if (m_auth)
      {
	m_auth.reset(nullptr);
      }
  }

  void NetworkManager::connect(GameServer const &srv, std::stirng const &token)
  {
    // TODO: Connect to a gameServer
  }

  bool NetworkManager::isConnected() const
  {
    return (m_connected);
  }
}
