#ifndef NETWORK_MANAGER_HPP_
#define NETWORK_MANAGER_HPP_

#include <string>
#include <cstdint>
#include <memory>
#include "NetworkAuth.hpp"
#include "Config.hpp"

namespace core
{
  class NetworkManager
  {
  public:
    NetworkManager();
    ~NetworkManager();

    NetworkManager(NetworkManager const &) = delete;
    NetworkManager &operator=(NetworkManager const &) = delete;

    // Authenticate on a connectManager
    void                    authenticate();
    void                    deauthenticate();
    bool                    isAuthenticated() const;
    std::vector<GameServer> getServerList();

    // Disconnect from any connectManager / gameServer
    void disconnect();

    // Connect to a gameServer
    void connect();
    bool isConnected() const;

  private:
    std::unique_ptr<NetworkAuth> m_auth;
    bool                         m_connected;
    std::string                  m_connectManagerAddr;
    std::uint16_t                m_connectManagerPort;
    std::string                  m_gameServerToken;
  };
}

#endif // !NETWORK_MANAGER_HPP_
