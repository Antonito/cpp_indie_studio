#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include "IClient.hpp"
#include "TCPSocket.hpp"

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
    AUTHENTICATED
  };

  explicit GameServer(sock_t socket, sockaddr_in_t const &in);

  GameServer(GameServer &&);

  sock_t getSocket() const;
  bool   canWrite() const;

  void toggleWrite();

  virtual bool                           disconnect();
  virtual network::IClient::ClientAction write();
  virtual network::IClient::ClientAction read();
  virtual bool                           hasTimedOut() const;

  void treatIncomingData();
  void treatOutcomingData();

  bool operator==(GameServer const &other) const;

private:
  network::TCPSocket           m_sock;
  sockaddr_in_t                m_in;
  bool                         m_write;
  State                        m_state;
  Packet<GameServerToCMPacket> m_packet;
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAMESERVER_HPP_
