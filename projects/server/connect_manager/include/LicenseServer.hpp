#ifndef LICENSE_SERVER_HPP_
#define LICENSE_SERVER_HPP_

#include <memory>
#include "IServer.hpp"
#include "TCPSocket.hpp"
#include "GameServer.hpp"
#include "Queue.hpp"

class LicenseServer : public network::IServer
{
public:
  explicit LicenseServer(std::uint16_t const port,
                         std::uint16_t const gameServerPort);
  virtual ~LicenseServer();

  virtual bool run();
  virtual void stop();
  virtual bool addClient();
  virtual bool removeClient(network::IClient &);

  void waitSignal();

  std::vector<std::unique_ptr<GameServer>> const &getGameServers() const;

  std::vector<std::string> const &getGameServerList() const;
  std::mutex &                    getGameServerListMut();

  void updateGameServerList();

private:
  void         _loop();
  bool         loadLicenses();
  std::int32_t checkActivity(fd_set &readfds, fd_set &writefds,
                             fd_set &   exceptfds,
                             bool const monitorLicenseServer);

  constexpr static std::uint32_t maxGameServer = 64;

  network::TCPSocket m_license;
  network::TCPSocket m_gameServer;

  class License
  {
  public:
    explicit License(std::string const &nb);

  private:
  };

  std::vector<std::string> m_licenseList; // TODO: Licenses ?
  std::vector<std::unique_ptr<GameServer>>
                           m_gameServerList; // TODO: Use Memory lib
  std::thread              m_thread;
  std::condition_variable  m_cond;
  std::mutex               m_mut;
  std::vector<std::string> m_list;
  std::mutex               m_gameServerListMut;
};

#endif // !LICENSE_SERVER_HPP_
