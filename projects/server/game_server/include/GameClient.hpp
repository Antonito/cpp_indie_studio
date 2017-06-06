#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include <vector>
#include "IClient.hpp"
#include "Packet.hpp"
#include "GameClientGSPacket.hpp"
#include "Token.hpp"

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
    AUTHENTICATING,
    AUTHENTICATED
  };

  GameClient(sock_t const fd, std::vector<Token> &m_tokenList,
             std::size_t const ndx);
  virtual ~GameClient();

  GameClient(GameClient const &);
  GameClient &operator=(GameClient const &);

  virtual bool                  disconnect();
  virtual IClient::ClientAction write(IPacket const &);
  virtual IClient::ClientAction read(IPacket &);
  virtual bool                  hasTimedOut() const;

  network::IClient::ClientAction treatIncomingData();
  network::IClient::ClientAction treatOutgoingData();

  sock_t getSocket() const;
  bool   canWrite() const;
  void   toggleWrite();

  std::int32_t getId() const;

  bool operator==(GameClient const &other) const;

private:
  network::TCPSocket           m_sock;
  bool                         m_canWrite;
  State                        m_state;
  Packet<GameClientToGSPacket> m_packet;
  std::vector<Token> &         m_tokenList;
  std::int32_t                 m_id;
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAMECLIENT_HPP_
