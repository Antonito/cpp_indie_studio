#ifndef NETWORK_AUTH_HPP_
#define NETWORK_AUTH_HPP_

#include <string>
#include <cstdint>

// TODO Antoine : implement in cpp file
// TODO: Inherit from IClient ?
namespace core
{
  class NetworkAuth
  {
  public:
    NetworkAuth(std::string const &ip, std::uint16_t const port)
        : m_ip(ip), m_port(port), m_auth(false),
          m_sock(port, ip, true, network::ASocket::SocketType::BLOCKING)
    {
      nope::log::Log(Debug) << "Creating connection [NetworkAuth]";
      nope::log::Log(Info) << "Opening connection";
      if (!m_connectManagerSocket->openConnection())
	{
	  nope::log::Log(Error) << "Cannot connect to " << ip << ":" << port;
	  throw std::exception(); // TODO
	}
    }

    ~NetworkAuth()
    {
      nope::log::Log(Debug) << "Destroying connection [NetworkAuth]";
    }

    NetworkAuth(NetworkAuth const &) = delete;
    NetworkAuth &operator=(NetworkAuth const &) = delete;

    bool isAuthenticated() const
    {
      return (m_auth);
    }

  private:
    std::string const & m_ip;
    std::uint16_t const m_port;
    bool                m_auth;
    network::TCPSocket  m_sock;
  };
};

#endif // !NETWORK_AUTH_HPP_
