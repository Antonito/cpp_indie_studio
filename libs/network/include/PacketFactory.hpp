#ifndef PACKET_FACTORY_HPP_
#define PACKET_FACTORY_HPP_

#include <iostream>
#if defined(__linux__) || (__APPLE__)
#include <arpa/inet.h>
#endif
#include <functional>
#include <memory>
#include <cstring>
#include "PacketError.hpp"
#include "Packet.hpp"

namespace std
{
  template <>
  struct default_delete<arcade::NetworkPacket>
  {
    void operator()(arcade::NetworkPacket *ptr)
    {
      delete ptr->data;
      delete ptr;
    }
  };
}

namespace Network
{
  class PacketFactory
  {
  public:
    PacketFactory(){};
    ~PacketFactory(){};

    template <size_t gameEventLen, typename EntityDataType>
    std::unique_ptr<arcade::NetworkPacket> create(
        arcade::NetworkGames const game,
        std::function<void(NetworkPacketData<gameEventLen, EntityDataType> &)>
            callback) const
    {
      std::unique_ptr<arcade::NetworkPacket> pck =
          std::make_unique<arcade::NetworkPacket>();
      arcade::NetworkPacketHeader *head = &pck->header;
      uint16_t                     curChck = 0;

      // Fill header
      std::memset(pck.get(), 0, sizeof(arcade::NetworkPacket));
      head->magicNumber =
          htonl(arcade::NetworkPacketHeader::packetMagicNumber);
      head->game = static_cast<arcade::NetworkGames>(
          htons(static_cast<uint16_t>(game)));
      pck->len =
          htonl(sizeof(NetworkPacketData<gameEventLen, EntityDataType>));
      head->checksum = head->magicNumber + head->game + pck->len;
      curChck = head->checksum;

      // Fill datas && calc checksum
      NetworkPacketData<gameEventLen, EntityDataType> *data =
          new NetworkPacketData<gameEventLen, EntityDataType>;
      pck->data = reinterpret_cast<uint8_t *>(data);
      std::memset(data, 0,
                  sizeof(NetworkPacketData<gameEventLen, EntityDataType>));
      callback(*data);
      calcChecksum(ntohl(pck->len), pck->data, head->checksum);
      if (head->checksum == curChck)
	{
	  throw arcade::Network::PacketError("Checksum not computed");
	}
      head->checksum = htonl(head->checksum);
      return (pck);
    }

  private:
    void calcChecksum(uint32_t const len, uint8_t const *data,
                      uint32_t &checksum) const
    {
      // Basic checksum
      for (uint32_t i = 0; i < len; ++i)
	{
	  checksum += data[i];
	}
    }
  };
}

#endif // !PACKET_FACTORY_HPP_
