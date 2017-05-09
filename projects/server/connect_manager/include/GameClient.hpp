#ifndef GAME_CLIENT_HPP_
#define GAME_CLIENT_HPP_

#include <cstdint>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "IPacket.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

class GameClient : public network::IClient
{
public:
  enum State
  {
    CONNECTED = 0,
    AUTHENTICATED
  };
  explicit GameClient(sock_t const fd);
  virtual ~GameClient();

  virtual bool                           disconnect();
  virtual network::IClient::ClientAction write(IPacket const &packet);
  virtual network::IClient::ClientAction read(IPacket &packet);
  virtual bool hasTimedOut() const;

  std::int32_t getSocket() const;
  bool         canWrite() const;
  void         toggleWrite();

  network::IClient::ClientAction treatIncomingData();
  network::IClient::ClientAction treatOutcomingData();

  bool operator==(GameClient const &other) const;

private:
  network::TCPSocket m_sock;
  bool               m_write;
  State              m_state;
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAME_CLIENT_HPP_
