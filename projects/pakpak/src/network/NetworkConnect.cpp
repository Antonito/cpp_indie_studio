#include "pakpak_stdafx.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

namespace core
{
  NetworkConnect::NetworkConnect(std::string const & ip,
                                 std::uint16_t const port,
                                 std::string const & token)
      : m_ip(ip), m_port(port), m_conn(false),
        m_sock(m_port, m_ip, true, network::ASocket::SocketType::BLOCKING),
        m_token(token)
  {
    nope::log::Log(Debug) << "Creating connection [NetworkConnect]";
    nope::log::Log(Info) << "Opening connection";
    if (!m_sock.openConnection())
      {
	nope::log::Log(Error) << "Cannot connect to " << ip << ":" << port;
	throw NetworkConnectionError("Cannot connect to " + ip + ":" +
	                             std::to_string(port));
      }
    authenticate();
    checkFiles();
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

  void NetworkConnect::authenticate()
  {
    network::IClient::ClientAction ret;
    GameClientToGSPacket           pckContent = {};
    Packet<GameClientToGSPacket>   pck = {};

    // Send token
    pckContent.pck.eventType = GameClientToGSEvent::TOKEN_EVENT;
    std::memcpy(pckContent.pck.eventData.token.data.data(), m_token.c_str(),
                40);
    pck << pckContent;
    ret = write(pck);
    if (ret != network::IClient::ClientAction::SUCCESS)
      {
	nope::log::Log(Error) << "Write failed ! [NetworkConnect]";
	return;
      }
    nope::log::Log(Debug) << "Packet sent [NetworkConnect]";

    // Reading response
    ret = read(pck);
    if (ret != network::IClient::ClientAction::SUCCESS)
      {
	nope::log::Log(Error) << "Read failed ! [NetworkConnect]";
	throw NetworkReadPacketError("Read failed ! [NetworkConnect]");
      }
    pck >> pckContent;
    if (pckContent.pck.eventType != GameClientToGSEvent::VALIDATION_EVENT)
      {
	nope::log::Log(Error) << "Invalid event type [NetworkConnect]";
	throw NetworkInvalidPacketError("Invalid event type [NetworkConnect]");
      }
    nope::log::Log(Debug) << "Read successful ! [NetworkConnect]";
    nope::log::Log(Debug) << "Validation: " << pckContent.pck.eventData.valid
                          << " [NetworkConnect]";
    nope::log::Log(Info)
        << "Client connected and authenticated to game server.";
  }

  void NetworkConnect::checkFiles()
  {
    network::IClient::ClientAction ret;
    GameClientToGSPacket           pckContent = {};
    Packet<GameClientToGSPacket>   pck = {};
    std::vector<MapConfig> const & mapConf =
        Config::getInstance().getMapConfig();

    // Check files
    pckContent.pck.eventType = GameClientToGSEvent::VALIDATION_EVENT;
    pckContent.pck.eventData.valid = 1;
    pck << pckContent;
    ret = write(pck);
    if (ret != network::IClient::ClientAction::SUCCESS)
      {
	nope::log::Log(Error) << "Write failed ! [NetworkConnect]";
	throw NetworkWritePacketError("Write failed ! [NetworkConnect]");
      }

    nope::log::Log(Info) << "Starting to check files";
    while (1)
      {
	if (read(pck) != network::IClient::ClientAction::SUCCESS)
	  {
	    nope::log::Log(Error) << "Cannot read";
	    throw NetworkReadPacketError("Cannot read");
	  }
	pck >> pckContent;

	if (pckContent.pck.eventType == GameClientToGSEvent::MD5_REQUEST)
	  {
	    nope::log::Log(Debug) << "Received MD5 Request";
	    std::string payload(pckContent.pck.eventData.md5requ.file.data());
	    std::string const gen = "~GENERAL~";

	    pckContent.pck.eventType = GameClientToGSEvent::MD5_RESPONSE;
	    if (payload.compare(0, gen.length(), gen) == 0)
	      {
		// Treat global MD5
		nope::log::Log(Debug) << "Treating Global MD5";
		std::memcpy(pckContent.pck.eventData.md5resp.md5.data(),
		            Config::getInstance().getMapMD5().c_str(), 32);
		pck << pckContent;
		if (write(pck) != network::IClient::ClientAction::SUCCESS)
		  {
		    nope::log::Log(Error) << "Cannot write";
		    throw NetworkWritePacketError("Cannot write");
		  }
	      }
	    else
	      {
		// Load file
		std::vector<std::string> filePath;
		std::string              md5Found;
		nope::log::Log(Debug) << "Requested MD5 of " << payload;

		// Split according to /
		Tokenize(payload, filePath, "/");

		if (filePath.size() < 2)
		  {
		    nope::log::Log(Error) << "Invalid map requested";
		    throw NetworkInvalidMapError("Invalid map requested");
		  }
		bool found = false;
		for (MapConfig const &m : mapConf)
		  {
		    if (filePath[1] == m.name)
		      {
			found = true;
			nope::log::Log(Debug) << "Found requested map";

			if (filePath.size() > 2)
			  {
			    std::map<std::string, std::string>::const_iterator
			        it = m.md5.find(filePath[2]);

			    // Check if key exist
			    if (it != m.md5.end())
			      {
				nope::log::Log(Debug) << "File is knowned.";
				md5Found = m.md5.at(filePath[2]);
			      }
			    else
			      {
				nope::log::Log(Debug) << "Uknown file !";
				md5Found = "";
			      }
			  }
			else
			  {
			    md5Found = m.md5Str;
			  }
		      }
		  }
		if (!found)
		  {
		    // TODO: Check if folder exists
		    nope::log::Log(Debug) << "Didn't find map";

		    // Create folder
		    std::string  folderPath = filePath[0] + "/" + filePath[1];
		    std::int32_t rc;
#if defined(_WIN32)
		    rc = CreateDirectory(folderPath.c_str(), nullptr);
		    if (!rc)
		      {
			rc = -1;
		      }
#else
		    rc = mkdir(folderPath.c_str(), 0777);
#endif
		    if (rc == -1)
		      {
			nope::log::Log(Warning)
			    << "Cannot create folder " << folderPath;
		      }
		    else
		      {
			nope::log::Log(Info)
			    << "Created folder " << folderPath;
		      }
		  }

		pckContent.pck.eventData.md5resp.md5.fill('\0');
		std::memcpy(pckContent.pck.eventData.md5resp.md5.data(),
		            md5Found.c_str(), 32);
		pck << pckContent;
		if (write(pck) != network::IClient::ClientAction::SUCCESS)
		  {
		    nope::log::Log(Error) << "Cannot write";
		    throw NetworkWritePacketError("Cannot write"); // TODO
		  }
		nope::log::Log(Debug) << "Sent MD5 response";
	      }
	  }
	else if (pckContent.pck.eventType ==
	         GameClientToGSEvent::VALIDATION_EVENT)
	  {
	    nope::log::Log(Debug) << "Received validation event";

	    if (pckContent.pck.eventData.valid == 1)
	      {
		nope::log::Log(Info) << "Files validated.";
		break;
	      }
	    nope::log::Log(Warning) << "Invalid validation event";
	  }
	else if (pckContent.pck.eventType == GameClientToGSEvent::FILE_EVENT)
	  {
	    nope::log::Log(Debug) << "Received file event";
	    std::uint32_t len = pckContent.pck.eventData.file.len;
	    std::string   filename(pckContent.pck.eventData.file.name.data());
	    nope::log::Log(Debug)
	        << "FileName: " << filename << " | Len: " << len;

	    // Read file
	    {
	      std::uint32_t           off = 0;
	      std::unique_ptr<char[]> buff = std::make_unique<char[]>(len);
	      do
		{
#if defined(_WIN32)
		  ssize_t rc =
		      _read(m_sock.getSocket(), buff.get() + off, len - off);
#else
		  ssize_t rc =
		      ::read(m_sock.getSocket(), buff.get() + off, len - off);
#endif

		  if (rc == -1 && rc != EINTR)
		    {
		      nope::log::Log(Error) << "Cannot read file";
		      throw NetworkReadPacketError("Cannot read file");
		    }
		  off += static_cast<std::uint32_t>(rc);
		}
	      while (off != len);
	      nope::log::Log(Debug) << "Received file.";
	      std::ofstream outputFile(filename,
	                               std::ios::binary | std::ios::out |
	                                   std::ios::trunc);
	      if (!outputFile.good() || !outputFile.is_open())
		{
		  nope::log::Log(Error) << "Cannot open file " << filename;
		  throw IOError("Cannot open file " + filename);
		}
	      nope::log::Log(Debug) << "Writing to file " << filename;
	      outputFile.write(buff.get(), len);
	      outputFile.close();
	      nope::log::Log(Debug) << "Closing file" << filename;
	    }

	    // Notify server it's OK
	    nope::log::Log(Debug) << "Notifying server.." << filename;
	    pckContent.pck.eventType = GameClientToGSEvent::VALIDATION_EVENT;
	    nope::log::Log(Debug)
	        << "Event Type: "
	        << static_cast<std::int32_t>(pckContent.pck.eventType);
	    pckContent.pck.eventData.valid = 1;
	    pck << pckContent;
	    if (write(pck) != network::IClient::ClientAction::SUCCESS)
	      {
		nope::log::Log(Error) << "Cannot write";
		throw NetworkWritePacketError("Cannot write");
	      }
	    nope::log::Log(Debug) << "Send response to server." << filename;
	    nope::log::Log(Info) << "Updating MD5 informations";
	    Config::getInstance().updateMD5();
	    nope::log::Log(Debug) << "MD5 informations updated.";
	  }
	else
	  {
	    nope::log::Log(Warning) << "Received invalid event";
	  }
      }
  }

  void NetworkConnect::Tokenize(std::string const &       str,
                                std::vector<std::string> &tokens,
                                std::string const &       delimiters)
  {

    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
      {
	tokens.push_back(str.substr(lastPos, pos - lastPos));
	lastPos = str.find_first_not_of(delimiters, pos);
	pos = str.find_first_of(delimiters, lastPos);
      }
  }
}

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif
