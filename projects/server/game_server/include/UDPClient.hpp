#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include <cstring>
#include <cstdint>
#include <chrono>
#include "GenNetwork.hpp"
#include "IClient.hpp"
#include "UDPSocket.hpp"
#include "GameClientGSPacket.hpp"

class UDPClient : public network::IClient
{
public:
  explicit UDPClient(sockaddr_in_t const &addr, network::UDPSocket &sock);
  virtual ~UDPClient();

  UDPClient(UDPClient const &);
  UDPClient &operator=(UDPClient const &);

  bool operator==(sockaddr_in_t const &addr) const;
  bool operator==(UDPClient const &cli) const;

  // Client
  virtual bool                           disconnect();
  virtual network::IClient::ClientAction write(IPacket const &);
  virtual network::IClient::ClientAction read(IPacket &);
  virtual bool                           hasTimedOut() const;

  void operator<<(Packet<GameClientToGSPacketUDP> &pck);

  GameClientToGSPacketUDP const &getData() const;

  void updateAction();

private:
  sockaddr_in_t                         m_addr;
  network::UDPSocket &                  m_sock;
  GameClientToGSPacketUDP               m_data;
  std::chrono::system_clock::time_point m_lastAction;
};

#endif // !UDP_CLIENT_HPP_
