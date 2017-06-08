#ifndef GAME_CLIENT_HPP_
#define GAME_CLIENT_HPP_

#include <vector>
#include <cstdint>
#include <mutex>
#include "IClient.hpp"
#include "TCPSocket.hpp"
#include "Packet.hpp"
#include "GameClientCMPacket.hpp"
#include "GameServerInfo.hpp"
#include "Queue.hpp"
#include "ResultGetter.hpp"
#include "RequestToken.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

class GameClient : public network::IClient
{
public:
  enum class State : std::int32_t
  {
    CONNECTED = 0,
    REQU_LIST_SERV,
    REQU_TOKEN
  };

  explicit GameClient(
      sock_t const fd, std::vector<GameServerInfo> const &, std::mutex &,
      multithread::Queue<multithread::ResultGetter<TokenCom>> &token);
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
  network::TCPSocket                                       m_sock;
  bool                                                     m_write;
  State                                                    m_state;
  Packet<GameClientToCMPacket>                             m_packet;
  std::vector<GameServerInfo> const &                      m_gameServerList;
  std::mutex &                                             m_gameServerListMut;
  multithread::Queue<multithread::ResultGetter<TokenCom>> &m_token;

  // Request's data
  std::array<char, INET6_ADDRSTRLEN_INDIE> m_requIp;
  std::uint16_t m_requPort;

  network::IClient::ClientAction _listServers(GameClientToCMPacket &rep);
  network::IClient::ClientAction _requToken(GameClientToCMPacket &rep);
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAME_CLIENT_HPP_
