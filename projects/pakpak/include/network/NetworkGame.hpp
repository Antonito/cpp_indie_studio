#ifndef NETWORK_GAME_HPP_
#define NETWORK_GAME_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include "UDPSocket.hpp"
#include "GameClientGSPacketUDP.hpp"

namespace core
{
  class NetworkGame
  {
  public:
    NetworkGame();
    ~NetworkGame();

    NetworkGame(NetworkGame const &) = delete;
    NetworkGame &operator=(NetworkGame const &) = delete;

    void init(std::uint16_t const port, std::string const &addr);
    void run();

    void stop();

  private:
    std::shared_ptr<network::UDPSocket> m_sock;
    Packet<GameClientToGSPacketUDP>     m_pck;
    GameClientToGSPacketUDP             m_pckContent;
    std::atomic<bool>                   m_running;

    network::IClient::ClientAction writeUDP(IPacket const &      pck,
                                            sockaddr_in_t const *addr);
  };
}

#endif // !NETWORK_GAME_HPP_
