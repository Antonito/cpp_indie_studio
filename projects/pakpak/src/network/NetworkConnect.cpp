#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkConnect::NetworkConnect(std::string const & ip,
                                 std::uint16_t const port)
      : m_ip(ip), m_port(port), m_conn(false),
        m_sock(m_port, m_ip, true, network::ASocket::SocketType::BLOCKING)
  {
    nope::log::Log(Debug) << "Creating connection [NetworkConnect]";
    nope::log::Log(Info) << "Opening connection";
    if (!m_sock.openConnection())
      {
	nope::log::Log(Error) << "Cannot connect to " << ip << ":" << port;
	throw std::exception(); // TODO
      }
  }

  NetworkConnect::~NetworkConnect()
  {
    nope::log::Log(Debug) << "Destroying connection [NetworkConnect]";
  }

  bool NetworkConnect::disconnect()
  {
    // TODO
    return (false);
  }

  network::IClient::ClientAction NetworkConnect::write(IPacket const &pck)
  {
    network::IClient::ClientAction ret =
        network::IClient::ClientAction::SUCCESS;
    std::size_t const   sizeToWrite = pck.getSize();
    std::uint8_t const *data = pck.getData();

    if (m_sock.send(data, sizeToWrite) == false)
      {
	nope::log::Log(Debug) << "Failed to write data [NetworkConnect]";
	ret = network::IClient::ClientAction::FAILURE;
      }
    return (ret);
  }

  network::IClient::ClientAction NetworkConnect::read(IPacket &pck)
  {
    network::IClient::ClientAction ret =
        network::IClient::ClientAction::FAILURE;

    // Allocate buffer
    std::unique_ptr<std::uint8_t[]> buff =
        std::make_unique<std::uint8_t[]>(packetSize::GameClientToCMPacketSize);
    ssize_t buffLen = 0;
    ssize_t headerLen = 0;

    // Read header first
    if (m_sock.rec(buff.get(), sizeof(PacketHeader), &headerLen))
      {
	assert(headerLen >= 0);
	if (headerLen == 0)
	  {
	    nope::log::Log(Debug)
	        << "Read failed, shall disconnect [NetworkConnect]";
	    ret = network::IClient::ClientAction::DISCONNECT;
	  }
	else
	  {
	    nope::log::Log(Debug)
	        << "Received header, checking it [NetworkConnect]";
	    // Check header
	    PacketHeader *header =
	        reinterpret_cast<PacketHeader *>(buff.get());

	    header->magic.magic = ntohs(header->magic.magic);
	    std::uint8_t vers = header->getVersion();
	    std::uint8_t magic = header->getMagic();
	    header->magic.magic = htons(header->magic.magic);
	    if (vers == PacketHeader::Version && magic == PacketHeader::Magic)
	      {
		// Get size to read
		std::uint16_t sizeToRead = ntohs(header->size);

		nope::log::Log(Debug)
		    << "Should read " << sizeToRead << " [NetworkConnect]";
		// Read rest of the packet
		if (m_sock.rec(buff.get() + headerLen, sizeToRead, &buffLen))
		  {
		    assert(buffLen >= 0);
		    if (buffLen == 0)
		      {
			nope::log::Log(Debug) << "Read failed, shall "
			                         "disconnect [NetworkConnect]";
			ret = network::IClient::ClientAction::DISCONNECT;
		      }
		    else
		      {
			ret = network::IClient::ClientAction::SUCCESS;
			pck.setData(
			    static_cast<std::size_t>(buffLen + headerLen),
			    std::move(buff));
		      }
		  }
	      }
	  }
      }
    return (ret);
  }

  bool NetworkConnect::hasTimedOut() const
  {
    return (false);
  }

  bool NetworkConnect::isConnected() const
  {
    return (m_conn);
  }
}
