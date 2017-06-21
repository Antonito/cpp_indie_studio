#include "game_server_stdafx.hpp"

UDPClient::UDPClient(sockaddr_in_t const &addr, network::UDPSocket &sock,
                     std::uint16_t const id)
    : m_addr(addr), m_sock(sock), m_data(),
      m_lastAction(std::chrono::system_clock::now()), m_id(id)
{
  nope::log::Log(Debug) << "Creating client [UDPClient - "
                        << inet_ntoa(m_addr.sin_addr) << " - #" << m_id
                        << " ]";
}

UDPClient::~UDPClient()
{
}

UDPClient::UDPClient(UDPClient const &other)
    : m_addr(other.m_addr), m_sock(other.m_sock),
      m_lastAction(other.m_lastAction), m_id(other.m_id)
{
}

UDPClient &UDPClient::operator=(UDPClient const &other)
{
  if (this != &other)
    {
      m_addr = other.m_addr;
      m_id = other.m_id;
      m_lastAction = other.m_lastAction;
    }
  return (*this);
}

bool UDPClient::operator==(sockaddr_in_t const &addr) const
{
#if defined _WIN32
  if (addr.sin_addr.S_addr != m_addr.sin_addr.S_addr)
#else
  if (addr.sin_addr.s_addr != m_addr.sin_addr.s_addr)
#endif
    {
      return (false);
    }
  return (addr.sin_port == m_addr.sin_port);
}

bool UDPClient::operator==(UDPClient const &cli) const
{
  return (*this == cli.m_addr);
}

// Not implemented, won't be
bool UDPClient::disconnect()
{
  return (false);
}

network::IClient::ClientAction UDPClient::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_sock.send(data, sizeToWrite,
                  reinterpret_cast<sockaddr_t const *>(&m_addr),
                  sizeof(m_addr)) == false)
    {
      nope::log::Log(Warning)
          << "{ " << m_id << "} Failed to write data " << std::strerror(errno)
          << "[UDPClient - " << inet_ntoa(m_addr.sin_addr) << "]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

// Not implemented, won't be
network::IClient::ClientAction UDPClient::read(IPacket &)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  return (ret);
}

bool UDPClient::hasTimedOut() const
{
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  if (std::chrono::duration_cast<std::chrono::seconds>(now - m_lastAction)
          .count() >= 5)
    {
      nope::log::Log(Info) << "{ " << m_id
                           << "} Client time'd out. [UDPClient - "
                           << inet_ntoa(m_addr.sin_addr) << "]";
      return (true);
    }
  return (false);
}

void UDPClient::operator<<(Packet<GameClientToGSPacketUDP> &pck)
{
  pck >> m_data;
}

GameClientToGSPacketUDP const &UDPClient::getData() const
{
  return (m_data);
}

void UDPClient::updateAction()
{
  m_lastAction = std::chrono::system_clock::now();
}

std::uint16_t UDPClient::getId() const
{
  return (m_id);
}
