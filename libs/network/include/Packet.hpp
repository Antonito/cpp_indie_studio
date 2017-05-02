#ifndef _PACKET_HPP_
#define _PACKET_HPP_

#include <functional>
#include "NetworkPacket.hpp"

#if defined(_WIN32)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

namespace network
{
  ///
  /// \struct NetworkGameEvent
  /// \brief Network Game Event
  ///
  template <std::size_t len>
  struct NetworkGameEvent
  {
    std::uint32_t buffLen = len;
    std::uint8_t  data[len];
  };

  ///
  /// \struct NetworkEntityEvent
  /// \brief Network Entity Event
  ///
  template <typename T>
  struct NetworkEntityEvent
  {
    T data;
  };

  ///
  /// \struct NetworkPlayerEvent
  /// \brief Network Player Event
  ///
  struct NetworkPlayerEvent
  {
    struct
    {
      ssize_t x;
      ssize_t y;
    } pos;
    std::uint8_t dir;
    std::size_t  life;
  };

  ///
  /// \struct NetworkPacketData
  /// \brief Network packet data
  ///
  template <std::size_t gameEventLen, typename EntityDataType>
  struct NetworkPacketData
  {
    NetworkPacketData() : action{}, game{} {};

    void handleAction(
        std::function<void(NetworkPlayerEvent const &)>             _play,
        std::function<void(NetworkGameEvent<gameEventLen> const &)> _game,
        std::function<void(NetworkEntityEvent<EntityDataType> const &)>
            _entity)
    {
      switch (action)
	{
	case PLAYER_EVENT:
	  _play(player);
	  break;
	case GAME_EVENT:
	  _game(game);
	  break;
	case ENTITY_EVENT:
	  _entity(entity);
	  break;
	default:
	  break;
	}
    }

    arcade::NetworkAction action;
    union
    {
      bool                               auth;
      NetworkPlayerEvent                 player;
      NetworkGameEvent<gameEventLen>     game;
      NetworkEntityEvent<EntityDataType> entity;
    };
  };
}

#endif // !_PACKET_HPP
