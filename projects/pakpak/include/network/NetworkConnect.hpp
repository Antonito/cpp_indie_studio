#ifndef NETWORK_CONNECT_HPP_
#define NETWORK_CONNECT_HPP_

#include <string>
#include <cstdint>
#include <thread>
#include <memory>
#include <atomic>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "GameClientGSPacket.hpp"
#include "NetworkGame.hpp"

namespace core
{
  class NetworkConnect : public network::IClient
  {
  public:
    explicit NetworkConnect(std::string const &ip, std::uint16_t const port,
                            std::string const &           token,
                            std::unique_ptr<NetworkGame> &net);
    virtual ~NetworkConnect();
    virtual bool                           disconnect();
    virtual network::IClient::ClientAction write(IPacket const &pck);
    virtual network::IClient::ClientAction read(IPacket &pck);
    virtual bool hasTimedOut() const;

    NetworkConnect(NetworkConnect const &) = delete;
    NetworkConnect &operator=(NetworkConnect const &) = delete;

    bool isConnected() const;

    std::uint16_t getId() const;

  private:
    std::string const &           m_ip;
    std::uint16_t const           m_port;
    bool                          m_conn;
    network::TCPSocket            m_sock;
    std::string const &           m_token;
    std::unique_ptr<NetworkGame> &m_game;
    std::thread                   m_udp;
    std::uint16_t                 m_id;

    // Token exchange
    void authenticate();
    // Integrity check
    void checkFiles();
    // Start UDP thread
    void setup();
    void Tokenize(std::string const &str, std::vector<std::string> &tokens,
                  std::string const &delimiters = " ");
  };
}

#endif // !NETWORK_CONNECT_HPP_
