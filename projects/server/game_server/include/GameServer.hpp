#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <string>
#include <cstdint>
#include "TCPSocket.hpp"
#include "IServer.hpp"
#include "IClient.hpp"

class GameServer : public network::IServer, public network::IClient
{
public:
  explicit GameServer(std::string const & connectManagerIp,
                      std::uint16_t const cmPort, std::uint16_t const gsPort,
                      std::int32_t const maxClients);
  virtual ~GameServer();

  // IServer
  virtual bool run();
  virtual void stop();
  virtual bool addClient();
  virtual bool removeClient(network::IClient &);

  // IClient
  virtual bool                           disconnect();
  virtual network::IClient::ClientAction write(IPacket const &);
  virtual network::IClient::ClientAction read(IPacket &);
  virtual bool                           hasTimedOut() const;

private:
  bool authenticateToConnectManager();

  std::uint16_t      m_connectManagerPort;
  std::uint16_t      m_gameServerPort;
  std::int32_t const m_maxClients;
  std::string        m_licence;

  network::TCPSocket m_connectManagerSock;
  network::TCPSocket m_gameSock;
};

#endif // !GAMESERVER_HPP_
