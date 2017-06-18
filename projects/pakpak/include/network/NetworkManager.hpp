#ifndef NETWORK_MANAGER_HPP_
#define NETWORK_MANAGER_HPP_

#include <string>
#include <cstdint>
#include <memory>
#include "NetworkAuth.hpp"
#include "NetworkConnect.hpp"
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
    std::string const &getToken(GameServer const &srv);

    // Connect to a gameServer
    void connect(GameServer const &srv, std::string const &token);
    void disconnect();
    bool isConnected() const;

  private:
    std::unique_ptr<NetworkAuth>    m_auth;
    std::unique_ptr<NetworkConnect> m_conn;
    std::string                     m_connectManagerAddr;
    std::uint16_t                   m_connectManagerPort;
    std::string                     m_gameServerToken;
  };
}

#endif // !NETWORK_MANAGER_HPP_
