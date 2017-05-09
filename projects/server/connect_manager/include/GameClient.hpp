#ifndef GAME_CLIENT_HPP_
#define GAME_CLIENT_HPP_

#include <array>
#include <cstdint>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "IPacket.hpp"

class GameClient : public network::IClient
{
public:
  explicit GameClient(sock_t const fd);
  virtual ~GameClient();

  virtual bool                           disconnect();
  virtual network::IClient::ClientAction write(IPacket const &packet);
  virtual network::IClient::ClientAction read(IPacket &packet);
  virtual bool hasTimedOut() const;

  std::int32_t getSocket() const;
  bool         canWrite() const;
  void         toggleWrite();

private:
  network::TCPSocket m_sock;
  bool               m_write;

  // Explicit padding
  std::array<std::uint8_t, 7> __padding;
};

#endif // !GAME_CLIENT_HPP_
