#ifndef NETWORK_CONNECT_HPP_
#define NETWORK_CONNECT_HPP_

#include <string>
#include <cstdint>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "GameClientGSPacket.hpp"

namespace core
{
  class NetworkConnect : public network::IClient
  {
  public:
    explicit NetworkConnect(std::string const &ip, std::uint16_t const port,
                            std::string const &token);
    virtual ~NetworkConnect();
    virtual bool                           disconnect();
    virtual network::IClient::ClientAction write(IPacket const &pck);
    virtual network::IClient::ClientAction read(IPacket &pck);
    virtual bool hasTimedOut() const;

    NetworkConnect(NetworkConnect const &) = delete;
    NetworkConnect &operator=(NetworkConnect const &) = delete;

    bool isConnected() const;

  private:
    std::string const & m_ip;
    std::uint16_t const m_port;
    bool                m_conn;
    network::TCPSocket  m_sock;
    std::string const & m_token;

    void authenticate();
    void checkFiles();
    void Tokenize(std::string const &str, std::vector<std::string> &tokens,
                  std::string const &delimiters = " ");
  };
}

#endif // !NETWORK_CONNECT_HPP_
