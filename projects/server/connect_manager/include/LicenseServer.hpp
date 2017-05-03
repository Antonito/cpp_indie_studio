#ifndef LICENSE_SERVER_HPP_
#define LICENSE_SERVER_HPP_

#include "IServer.hpp"
#include "TCPSocket.hpp"

class LicenseServer : public network::IServer
{
public:
  explicit LicenseServer(std::uint16_t const port);
  virtual ~LicenseServer();

  virtual bool run();
  virtual void stop();
  virtual bool addClient();
  virtual bool removeClient(network::IClient &);

private:
  void               _loop();
  bool               loadLicenses();
  network::TCPSocket m_license;
  // network::TCPSocket m_gameServer;

  class License
  {
  public:
    explicit License(std::string const &nb);

  private:
  };

  class GameServer
  {
  public:
  private:
  };

  std::vector<std::string> m_licenseList; // TODO: Licenses ?
  std::vector<GameServer>  m_gameServerList;
  std::thread              m_thread;
};

#endif // !LICENSE_SERVER_HPP_
