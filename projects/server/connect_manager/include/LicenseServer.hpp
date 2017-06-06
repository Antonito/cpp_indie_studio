#ifndef LICENSE_SERVER_HPP_
#define LICENSE_SERVER_HPP_

#include <memory>
#include "IServer.hpp"
#include "TCPSocket.hpp"
#include "GameServer.hpp"
#include "Queue.hpp"
#include "GameServerInfo.hpp"
#include "ResultGetter.hpp"
#include "RequestToken.hpp"

class LicenseServer : public network::IServer
{
public:
  explicit LicenseServer(
      std::uint16_t const port, std::uint16_t const gameServerPort,
      std::string const &                                      publicIP,
      multithread::Queue<multithread::ResultGetter<TokenCom>> &token);
  virtual ~LicenseServer();

  virtual bool run();
  virtual void stop();
  virtual bool addClient();
  virtual bool removeClient(network::IClient &);

  void waitSignal();

  std::vector<std::unique_ptr<GameServer>> const &getGameServers() const;

  std::vector<GameServerInfo> const &getGameServerList() const;
  std::mutex &                       getGameServerListMut();

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
  std::thread                                              m_thread;
  std::condition_variable                                  m_cond;
  std::mutex                                               m_mut;
  std::vector<GameServerInfo>                              m_list;
  std::mutex                                               m_gameServerListMut;
  std::string const &                                      m_publicIp;
  multithread::Queue<multithread::ResultGetter<TokenCom>> &m_token;
};

#endif // !LICENSE_SERVER_HPP_
