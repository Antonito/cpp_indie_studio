#ifndef GAME_CLIENT_SERVER_HPP_
#define GAME_CLIENT_SERVER_HPP_

#include <thread>
#include "IServer.hpp"
#include "TCPSocket.hpp"

class GameClientServer : public network::IServer
{
public:
  explicit GameClientServer(std::uint16_t const port);

  virtual ~GameClientServer();

  virtual bool run();
  virtual void stop();
  virtual bool addClient();
  virtual bool removeClient(network::IClient &);

private:
  constexpr static std::uint32_t maxGameClients = 64;
  void                           _loop();
  std::int32_t checkActivity(fd_set &readfds, fd_set &writefds,
                             fd_set &exceptfds);

  network::TCPSocket m_sock;
  std::thread        m_thread;
};

#endif // !GAME_CLIENT_SERVER_HPP_
