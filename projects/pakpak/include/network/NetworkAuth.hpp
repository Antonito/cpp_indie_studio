#ifndef NETWORK_AUTH_HPP_
#define NETWORK_AUTH_HPP_

#include <string>
#include <cstdint>
#include <vector>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "NetworkGameServer.hpp"
#include "Packet.hpp"
#include "GameClientCMPacket.hpp"

namespace core
{
  class NetworkAuth : public network::IClient
  {
  public:
    explicit NetworkAuth(std::string const &ip, std::uint16_t const port);
    virtual bool                           disconnect();
    virtual network::IClient::ClientAction write(IPacket const &pck);
    virtual network::IClient::ClientAction read(IPacket &pck);
    virtual bool hasTimedOut() const;
    virtual ~NetworkAuth();

    NetworkAuth(NetworkAuth const &) = delete;
    NetworkAuth &operator=(NetworkAuth const &) = delete;

    bool isAuthenticated() const;

    std::vector<GameServer> getServerList();
    std::string const &     getToken(GameServer const &);

  private:
    std::string const & m_ip;
    std::uint16_t const m_port;
    bool                m_auth;
    network::TCPSocket  m_sock;
    std::string         m_token;
  };
}

#endif // !NETWORK_AUTH_HPP_
