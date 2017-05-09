#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <vector>
#include <string>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "Packet.hpp"
#include "GameServerCMPacket.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

class GameServer : public network::IClient
{
public:
  enum State
  {
    CONNECTED,
    SETTING,
    AUTHENTICATED
  };

  explicit GameServer(sock_t socket, sockaddr_in_t const &in,
                      std::vector<std::string> const &licences);

  GameServer(GameServer &&);

  sock_t getSocket() const;
  bool   canWrite() const;

  void toggleWrite();

  virtual bool                           disconnect();
  virtual network::IClient::ClientAction write(IPacket const &packet);
  virtual network::IClient::ClientAction read(IPacket &packet);
  virtual bool hasTimedOut() const;

  network::IClient::ClientAction treatIncomingData();
  network::IClient::ClientAction treatOutcomingData();

  bool operator==(GameServer const &other) const;

private:
  network::TCPSocket              m_sock;
  sockaddr_in_t                   m_in;
  std::vector<std::string> const &m_licences;
  bool                            m_write;
  State                           m_state;
  Packet<GameServerToCMPacket>    m_packet;
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAMESERVER_HPP_
