#include "game_server_stdafx.hpp"

GameClient::GameClient(sock_t const fd, std::vector<Token> &tokenList,
                       std::size_t const ndx)
    : m_sock(fd), m_canWrite(false), m_state(GameClient::State::CONNECTED),
      m_packet(), m_tokenList(tokenList), m_id(static_cast<std::int32_t>(ndx))
{
}

GameClient::~GameClient()
{
}

bool GameClient::disconnect()
{
  nope::log::Log(Debug) << "GameClient disconnected #" << getSocket();
  m_sock.closeConnection();
  return (true);
}

network::IClient::ClientAction GameClient::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_sock.send(data, sizeToWrite) == false)
    {
      nope::log::Log(Debug) << "Failed to write data [GameClient]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

network::IClient::ClientAction GameClient::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  std::size_t const buffSize = packetSize::GameClientToGSPacketSize;

  // Allocate buffer
  std::unique_ptr<uint8_t[]> buff = std::make_unique<std::uint8_t[]>(buffSize);
  ssize_t                    buffLen = 0;
  ssize_t                    headerLen = 0;

  // Read header first
  if (m_sock.rec(buff.get(), sizeof(PacketHeader), &headerLen))
    {
      assert(headerLen >= 0);
      if (headerLen == 0)
	{
	  nope::log::Log(Debug)
	      << "Read failed, shall disconnect [GameClient Header]";
	  ret = network::IClient::ClientAction::DISCONNECT;
	}
      else
	{
	  nope::log::Log(Debug) << "Received header, checking it [GameClient]";
	  // Check header
	  PacketHeader *header = reinterpret_cast<PacketHeader *>(buff.get());

	  header->magic.magic = ntohs(header->magic.magic);
	  std::uint8_t vers = header->getVersion();
	  std::uint8_t magic = header->getMagic();
	  header->magic.magic = htons(header->magic.magic);
	  if (vers == PacketHeader::Version && magic == PacketHeader::Magic)
	    {
	      // Get size to read
	      std::uint16_t sizeToRead = ntohs(header->size);

	      nope::log::Log(Debug)
	          << "Should read " << sizeToRead << "[GameClient]";
	      if (static_cast<std::size_t>(headerLen + sizeToRead) <=
	          packetSize::GameClientToGSPacketSize)
		{
		  // Read rest of the packet
		  if (m_sock.rec(buff.get() + headerLen, sizeToRead, &buffLen))
		    {
		      assert(buffLen >= 0);
		      if (buffLen == 0)
			{
			  nope::log::Log(Debug)
			      << "Read failed, shall disconnect [GameClient]";
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
	      else
		{
		  nope::log::Log(Debug)
		      << "Invalid packet received [GameClient]";
		  ret = network::IClient::ClientAction::DISCONNECT;
		}
	    }
	}
    }
  return (ret);
}

bool GameClient::hasTimedOut() const
{
  // TODO
  return (false);
}

sock_t GameClient::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameClient::canWrite() const
{
  return (m_canWrite);
}

void GameClient::toggleWrite()
{
  m_canWrite = !m_canWrite;
}

std::int32_t GameClient::getId() const
{
  return (m_id);
}

network::IClient::ClientAction GameClient::lobbyRead()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  // Check if alone -> stop game, and switch to playing game
  // TODO

  return (ret);
}

network::IClient::ClientAction GameClient::lobbyWrite()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  // TODO
  return (ret);
}

network::IClient::ClientAction GameClient::treatIncomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  GameClientToGSPacket           rep;

  switch (m_state)
    {
    // Authentication
    case State::CONNECTED:
      nope::log::Log(Debug) << "Reading in state CONNECTED [GameClient]";
      ret = read(m_packet);
      if (ret == network::IClient::ClientAction::SUCCESS)
	{
	  m_packet >> rep;

	  // The only event allowed here is TOKEN_EVENT
	  if (rep.pck.eventType == GameClientToGSEvent::TOKEN_EVENT)
	    {
	      std::string tokenStr =
	          std::string(rep.pck.eventData.token.data.data(), 40);
	      nope::log::Log(Debug) << "Received Token: " << tokenStr;
	      ret = network::IClient::ClientAction::FAILURE;
	      for (Token const &tok : m_tokenList)
		{
		  nope::log::Log(Debug) << "Is it ? -> " << tok.getToken();
		  if (tok == tokenStr)
		    {
		      nope::log::Log(Debug) << "Found token in token list";
		      if (tok.isValid())
			{
			  nope::log::Log(Debug) << "Token is valid";
			  m_state = State::AUTHENTICATING;
			  ret = network::IClient::ClientAction::SUCCESS;
			}
		      // Found it, now remove it from the list
		      m_tokenList.erase(std::remove(m_tokenList.begin(),
		                                    m_tokenList.end(), tok),
		                        m_tokenList.end());
		      break;
		    }
		}
	    }
	}
      break;
    case State::AUTHENTICATING:
      break;
    case State::AUTHENTICATED:
      nope::log::Log(Debug) << "Reading in state AUTHENTICATED [GameClient]";
      ret = read(m_packet);
      if (ret == network::IClient::ClientAction::SUCCESS)
	{
	  m_packet >> rep;
	  // The only event allowed is a VALIDATION event
	  if (rep.pck.eventType == GameClientToGSEvent::VALIDATION_EVENT)
	    {
	      nope::log::Log(Debug)
	          << "Got Validation: " << rep.pck.eventData.valid
	          << " [GameClient]";
	      if (rep.pck.eventData.valid == 1)
		{
		  nope::log::Log(Debug)
		      << "Switching to CHECKING_MAPS state [GameClient]";
		  m_state = State::CHECKING_MAPS;
		}
	    }
	}
      break;
    case State::CHECKING_MAPS:
      break;

    // Lobby
    case State::WAITING:
      ret = lobbyRead();
      break;

    // GameLogic
    case State::PLAYING:
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

network::IClient::ClientAction GameClient::treatOutgoingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  GameClientToGSPacket           rep;

  switch (m_state)
    {
    // Authentication
    case State::CONNECTED:
      break;
    case State::AUTHENTICATING:
      // Notify the client that it is authenticated
      rep.pck.eventType = GameClientToGSEvent::VALIDATION_EVENT;
      rep.pck.eventData.valid = 1;

      m_packet << rep;
      ret = write(m_packet);
      m_state = State::AUTHENTICATED;
      break;
    case State::AUTHENTICATED:
      break;
    case State::CHECKING_MAPS:
      if (checkMaps())
	{
	  ret = network::IClient::ClientAction::SUCCESS;
	  nope::log::Log(Debug) << "Switching to State::WAITING";
	  m_state = State::WAITING;
	}
      break;

    // Lobby
    case State::WAITING:
      ret = lobbyWrite();
      break;

    // Game logic
    case State::PLAYING:
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

bool GameClient::operator==(GameClient const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}

bool GameClient::checkMaps()
{
  GameClientToGSPacket           rep;
  network::IClient::ClientAction ret;
  std::string                    clientGlobalMD5;
  std::int32_t                   rc;

  // Multiplex I if read == true or O if read == false
  std::function<std::int32_t(bool read)> multiplex = [&](bool read) {
    std::int32_t _rc;

    do
      {
	sock_t const   fd = m_sock.getSocket();
	fd_set         readfds, writefds;
	struct timeval tv;

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	if (read)
	  {
	    FD_SET(fd, &readfds);
	  }
	else
	  {
	    FD_SET(fd, &writefds);
	  }
	_rc = select(fd + 1, &readfds, &writefds, nullptr, &tv);
      }
    while (_rc == -1 && errno == EINTR);
    return (_rc);
  };

  // Check global MD5
  nope::log::Log(Info) << "Checking integrity of client's maps";
  rep.pck.eventType = GameClientToGSEvent::MD5_REQUEST;
  std::memcpy(rep.pck.eventData.md5requ.file.data(), "~GENERAL~",
              sizeof("~GENERAL~"));
  static_assert(sizeof("~GENERAL~") < GameClientToGSPacketToken::tokenLength,
                "Filename is too large.");

  rc = multiplex(false);
  if (rc <= 0)
    {
      goto error_map;
    }

  m_packet << rep;
  ret = write(m_packet);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      goto error_map;
    }
  nope::log::Log(Debug) << "Sent Global MD5 request";

  rc = multiplex(true);
  if (rc <= 0)
    {
      goto error_map;
    }
  ret = read(m_packet);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      goto error_map;
    }
  nope::log::Log(Debug) << "Got response.";
  m_packet >> rep;
  if (rep.pck.eventType != GameClientToGSEvent::MD5_RESPONSE)
    {
      nope::log::Log(Error) << "Invalid reponse [GameClient]";
      goto error_map;
    }

  // Check Global MD5
  clientGlobalMD5 = std::string(rep.pck.eventData.md5resp.md5.data(), 32);
  nope::log::Log(Debug) << "Global MD5:          "
                        << Config::getInstance().getMapMD5();
  nope::log::Log(Debug) << "Received Global MD5: " << clientGlobalMD5;
  if (clientGlobalMD5 != Config::getInstance().getMapMD5())
    {
      nope::log::Log(Warning) << "Global MD5 differs";
      // If MD5 are different, check each maps
      std::vector<MapConfig> const &maps =
          Config::getInstance().getMapConfig();

      // Check MD5 for each map
      nope::log::Log(Debug) << "Looping over maps";
      for (MapConfig const &map : maps)
	{
	  nope::log::Log(Debug) << map.directory << ": " << map.md5Str;

	  rc = multiplex(false);
	  if (rc <= 0)
	    {
	      goto error_map;
	    }
	  rep.pck.eventType = GameClientToGSEvent::MD5_REQUEST;
	  rep.pck.eventData.md5requ.file.fill('\0');
	  std::memcpy(rep.pck.eventData.md5requ.file.data(),
	              map.directory.c_str(), map.directory.length());
	  m_packet << rep;
	  ret = write(m_packet);
	  if (ret != network::IClient::ClientAction::SUCCESS)
	    {
	      goto error_map;
	    }
	  nope::log::Log(Debug) << "Sent MD5 request";

	  rc = multiplex(true);
	  if (rc <= 0)
	    {
	      goto error_map;
	    }
	  ret = read(m_packet);
	  if (ret != network::IClient::ClientAction::SUCCESS)
	    {
	      goto error_map;
	    }
	  nope::log::Log(Debug) << "Received response";
	  m_packet >> rep;
	  if (rep.pck.eventType != GameClientToGSEvent::MD5_RESPONSE)
	    {
	      goto error_map;
	    }
	  std::string md5map(rep.pck.eventData.md5resp.md5.data());

	  // Check if map is OK
	  nope::log::Log(Debug) << "Received MD5: " << md5map;
	  if (md5map != map.md5Str)
	    {
	      nope::log::Log(Warning) << "Corrupted map: " << map.directory;
	      nope::log::Log(Debug) << "Checking files";

	      // Loop over all files
	      for (std::pair<std::string const, std::string> file : map.md5)
		{
		  nope::log::Log(Debug) << file.first << ": " << file.second;

		  std::string md5mapFile;
		  do
		    {
		      std::string curMap = map.directory + file.first;
		      rc = multiplex(false);
		      if (rc <= 0)
			{
			  goto error_map;
			}
		      rep.pck.eventType = GameClientToGSEvent::MD5_REQUEST;
		      rep.pck.eventData.md5requ.file.fill('\0');
		      std::memcpy(rep.pck.eventData.md5requ.file.data(),
		                  curMap.c_str(), curMap.length());
		      m_packet << rep;
		      ret = write(m_packet);
		      if (ret != network::IClient::ClientAction::SUCCESS)
			{
			  goto error_map;
			}
		      nope::log::Log(Debug) << "Sent MD5";

		      rc = multiplex(true);
		      if (rc <= 0)
			{
			  goto error_map;
			}
		      ret = read(m_packet);
		      if (ret != network::IClient::ClientAction::SUCCESS)
			{
			  goto error_map;
			}
		      nope::log::Log(Debug) << "Received response";
		      m_packet >> rep;
		      if (rep.pck.eventType !=
		          GameClientToGSEvent::MD5_RESPONSE)
			{
			  goto error_map;
			}
		      md5mapFile =
		          std::string(rep.pck.eventData.md5resp.md5.data());

		      nope::log::Log(Debug)
		          << "Checking received MD5: " << md5mapFile;
		      if (md5mapFile != file.second)
			{

			  // Send file
			  nope::log::Log(Warning)
			      << "Corrupted file: " << curMap;
			  rc = multiplex(false);
			  if (rc <= 0)
			    {
			      goto error_map;
			    }

			  // Open file, read it, send it
			  {
			    std::ifstream fileReader;
			    std::size_t   fileSize;

			    nope::log::Log(Debug) << "Opening file " << curMap;
			    fileReader.open(curMap.c_str(),
			                    std::ios::binary | std::ios::ate);
			    if (!fileReader.good() || !fileReader.is_open())
			      {
				nope::log::Log(Error)
				    << "Cannot open file " << curMap;
				throw IOError("Cannot open file " + curMap);
			      }
			    fileSize =
			        static_cast<std::size_t>(fileReader.tellg());
			    fileReader.seekg(0, std::ios::beg);
			    std::unique_ptr<char[]> fileBuff =
			        std::make_unique<char[]>(fileSize);
			    fileReader.read(
			        fileBuff.get(),
			        static_cast<std::streamsize>(fileSize));
			    fileReader.close();
			    nope::log::Log(Debug) << "Closing file " << curMap;

			    nope::log::Log(Debug) << "Building file packet";
			    rep.pck.eventType =
			        GameClientToGSEvent::FILE_EVENT;
			    rep.pck.eventData.file.len =
			        static_cast<std::uint32_t>(fileSize);
			    rep.pck.eventData.file.name.fill('\0');
			    std::memcpy(rep.pck.eventData.file.name.data(),
			                curMap.c_str(), curMap.length());
			    nope::log::Log(Debug) << "Sending packet";
			    m_packet << rep;
			    ret = write(m_packet);
			    if (ret != network::IClient::ClientAction::SUCCESS)
			      {
				goto error_map;
			      }

			    nope::log::Log(Debug) << "Sending file content ["
			                          << fileSize << " bytes]";
#if defined(_WIN32)
			    rc = static_cast<std::int32_t>(_write(
			        m_sock.getSocket(), fileBuff.get(), fileSize));
#else
			    rc = static_cast<std::int32_t>(::write(
			        m_sock.getSocket(), fileBuff.get(), fileSize));
#endif
			    if (rc <= 0)
			      {
				goto error_map;
			      }
			  }

			  rc = multiplex(true);
			  if (rc <= 0)
			    {
			      goto error_map;
			    }
			  ret = read(m_packet);
			  if (ret != network::IClient::ClientAction::SUCCESS)
			    {
			      goto error_map;
			    }
			  nope::log::Log(Debug) << "Received response";
			  m_packet >> rep;
			  if (rep.pck.eventType !=
			      GameClientToGSEvent::VALIDATION_EVENT)
			    {
			      nope::log::Log(Error)
			          << "Incorrect event type "
			          << static_cast<std::int32_t>(
			                 rep.pck.eventType);
			      goto error_map;
			    }
			  nope::log::Log(Debug) << "Correct event type";
			  if (rep.pck.eventData.valid != 1)
			    {
			      goto error_map;
			    }
			  nope::log::Log(Debug) << "Validated event";
			  // TODO: read OK
			}
		    }
		  while (md5mapFile != file.second);
		}
	    }
	}
    }

  // Send OK
  rc = multiplex(false);
  if (rc <= 0)
    {
      goto error_map;
    }

  nope::log::Log(Debug) << "Integrity OK, sending validation.";
  rep.pck.eventType = GameClientToGSEvent::VALIDATION_EVENT;
  rep.pck.eventData.valid = 1;
  m_packet << rep;
  ret = write(m_packet);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      goto error_map;
    }
  nope::log::Log(Info) << "Map integrity checked.";
  return (true);

error_map:
  nope::log::Log(Error) << "Cannot check integrity of client's maps";
  return (false);
}
