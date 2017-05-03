#include "connect_manager_stdafx.hpp"

LicenseServer::LicenseServer(std::uint16_t const port)
    : m_license(port, "localhost", false, network::ASocket::BLOCKING),
      m_licenseList(), m_gameServerList(), m_thread()
{
}

LicenseServer::~LicenseServer()
{
}

bool LicenseServer::run()
{
  m_license.openConnection();
  m_thread = std::thread(&LicenseServer::_loop, this);
  return (true);
}

void LicenseServer::stop()
{
  if (m_thread.joinable())
    {
      m_thread.join();
    }
}

bool LicenseServer::addClient()
{
  return (true);
}

bool LicenseServer::removeClient(network::IClient &)
{
  return (true);
}

void LicenseServer::_loop()
{
  while (1)
    {
      std::int32_t   rc;
      fd_set         readfds, writefds, exceptfds;
      struct timeval tv;
      std::int32_t   maxFd;

      // Check file descriptors
      do
	{
	  FD_ZERO(&readfds);
	  FD_ZERO(&writefds);
	  FD_ZERO(&exceptfds);

	  tv.tv_sec = 2;
	  tv.tv_usec = 0;

	  maxFd = m_license.getSocket();
	  FD_SET(maxFd, &readfds);

	  // Loop over gameServers

	  rc = select(maxFd + 1, &readfds, &writefds, &exceptfds, &tv);
	}
      while (rc == -1 && errno == EINTR);

      if (rc == -1)
	{
	  // There was an error
	  break;
	}
      else if (!rc)
	{
	  // Time out !
	}
      else
	{
	  // Handle IO
	  if (FD_ISSET(m_license.getSocket(), &readfds))
	    {
	      std::array<char, 400> arr;
	      ssize_t readVal;

	      if (m_license.rec(arr.data(), 400, &readVal))
		{
		  arr[static_cast<std::size_t>(readVal)] = '\0';
		  std::cout << std::string(arr.data()) << std::endl;
		}
	    }

	  // Loop over gameServers and handle IO
	}
    }
}
