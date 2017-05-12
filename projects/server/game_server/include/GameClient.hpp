#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include "IClient.hpp"

class GameClient : public network::IClient
{
public:
  GameClient();
  virtual ~GameClient();

  GameClient(GameClient const &);
  GameClient &operator=(GameClient const &);

  virtual bool                  disconnect();
  virtual IClient::ClientAction write(IPacket const &);
  virtual IClient::ClientAction read(IPacket &);
  virtual bool                  hasTimedOut() const;

private:
};

#endif // !GAMECLIENT_HPP_
