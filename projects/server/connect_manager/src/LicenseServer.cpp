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
  nope::log::Log(Debug) << "Running server";
  if (m_license.openConnection())
    {
      nope::log::Log(Debug) << "Connection opened";
      m_thread = std::thread([&]() { this->_loop(); });
    }
  else
    {
      nope::log::Log(Error) << "Cannot open connection";
    }
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
  bool monitorLicenseServer = true;

  loadLicenses();
  while (1)
    {
      std::int32_t   rc = -1;
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

	  maxFd = (monitorLicenseServer) ? m_license.getSocket() : 0;
	  assert(maxFd != -1);
	  if (monitorLicenseServer)
	    {
	      FD_SET(maxFd, &readfds);
	    }

	  if (!monitorLicenseServer && maxFd == 0)
	    {
	      break;
	    }
	  // Loop over gameServers
	  rc = select(maxFd + 1, &readfds, &writefds, &exceptfds, &tv);
	}
      while (rc == -1 && errno == EINTR);

      if (maxFd == 0)
	{
	  break;
	}

      if (rc < 0)
	{
	  // There was an error
	  break;
	}
      else if (!rc)
	{
	  // Time out !
	  ;
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
		  if (readVal == 0)
		    {
		      break;
		    }
		  arr[static_cast<std::size_t>(readVal)] = '\0';
		  std::cout << std::string(arr.data()) << std::endl;
		  loadLicenses();
		}
	      else
		{
		  // Nothing more to read, byebye
		  break;
		}
	    }

	  // Loop over gameServers and handle IO
	}
    }
  std::cout << "Loop finished" << std::endl;
}

bool LicenseServer::loadLicenses()
{
  std::ifstream licensesFile(".license_keys");

  if (licensesFile.is_open())
    {
      // Add each key the key list
      std::string license;
      while (std::getline(licensesFile, license))
	{
	  if (std::find(m_licenseList.begin(), m_licenseList.end(), license) ==
	      m_licenseList.end())
	    {
	      m_licenseList.push_back(license);
	      nope::log::Log(Info) << "Adding key: " << license;
	    }
	}
      licensesFile.close();
      return (true);
    }
  return (false);
}
