#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <cstdint>
#include "TCPSocket.hpp"
#include "IServer.hpp"

class GameServer : public network::IServer
{
public:
  explicit GameServer(std::string const & connectManagerIp,
                      std::uint16_t const cmPort, std::uint16_t const gsPort,
                      std::int32_t const maxClients);
  virtual ~GameServer();

  virtual bool run();
  virtual void stop();
  virtual bool addClient();
  virtual bool removeClient(network::IClient &);

private:
  std::uint16_t      m_connectManagerPort;
  std::uint16_t      m_gameServerPort;
  std::int32_t const m_maxClients;

  network::TCPSocket m_connectManagerSock;
};

#endif // !GAMESERVER_HPP_
