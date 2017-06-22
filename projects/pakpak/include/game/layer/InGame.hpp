#ifndef INGAME_HPP_
#define INGAME_HPP_

#include "pakpak_stdafx.hpp"

namespace game
{
  enum SPEED_UNITS
  {
    U0,
    U1,
    U2,
    U3,
    U4,
    U5,
    U6,
    U7,
    U8,
    U9
  };

  enum POSITIONS
  {
    ST,
    ND,
    RD,
    TH
  };

  static const std::vector<std::string> screens = {"player1/", "player2/",
                                                   "player3/", "player4/"};

  template <std::uint8_t PCOUNT>
  class InGame           final : public ALayer
  {
  public:
    explicit InGame() = delete;
    InGame(GameData &data, LocalPlayer &player, core::HUD *hud,
           std::vector<std::unique_ptr<LocalPlayer>> &players)
        : ALayer(data, player, hud, players), m_player(player), m_speed(),
          m_positionSuffix(), m_positionPrefix(), m_start(), m_startIdx(0),
          m_time(1000)
    {
    }
    virtual ~InGame()
    {
    }

    InGame(InGame const &) = delete;
    InGame(InGame &&) = delete;
    InGame &operator=(InGame const &) = delete;
    InGame &operator=(InGame &&) = delete;

    virtual void enable()
    {
      nope::log::Log(Debug) << "Enabling InGame";
      if (m_gui)
	{
	  switch (PCOUNT)
	    {
	    case (2):
	      m_gui->loadLayout("gui_ingame2.layout");
	      break;
	    case (3):
	      m_gui->loadLayout("gui_ingame3.layout");
	      break;
	    case (4):
	      m_gui->loadLayout("gui_ingame4.layout");
	      break;
	    default:
	      m_gui->loadLayout("gui_ingame.layout");
	    }

	  for (std::uint8_t playerIndex = 0;
	       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
	    {
	      m_speed[playerIndex][0] =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "unit");
	      m_speed[playerIndex][1] =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "decade");
	      m_speed[playerIndex][2] = m_gui->getRoot()->getChild(
	          screens[playerIndex] + "thousand");
	      m_positionSuffix[playerIndex] = m_gui->getRoot()->getChild(
	          screens[playerIndex] + "place_postfix");
	      m_positionPrefix[playerIndex] = m_gui->getRoot()->getChild(
	          screens[playerIndex] + "place_suffix");
	      if (m_player.isConnected())
		{
		  m_positionSuffix[playerIndex]->setVisible(false);
		  m_positionPrefix[playerIndex]->setVisible(false);
		}
	      m_start[playerIndex][0] =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "3");
	      m_start[playerIndex][0]->setVisible(false);
	      m_start[playerIndex][1] =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "2");
	      m_start[playerIndex][1]->setVisible(false);
	      m_start[playerIndex][2] =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "1");
	      m_start[playerIndex][2]->setVisible(false);
	      m_start[playerIndex][3] =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "GO");
	      m_start[playerIndex][3]->setVisible(false);
	    }
	}
      m_time.start();
    }

    virtual void disable()
    {
    }

    virtual void update()
    {
    }

    virtual void display()
    {
      if (!m_player.isConnected())
	{
	  setStart();
	}
      setSpeed();
      setPosition();
      setFinish();
    }

    virtual bool keyPressed(OIS::KeyEvent const &ke)
    {
      std::string action = m_player.settings().actionForKey(
          static_cast<std::size_t>(m_player.order()), ke.key);

#if defined(INDIE_MAP_EDITOR)
      switch (ke.key)
	{
	case OIS::KC_SPACE:
	  m_gameData.map().addPoint(m_player.car().position());
	  return true;
	case OIS::KC_RETURN:
	  m_gameData.map().save();
	  return true;
	default:
	  break;
	}
#endif // !INDIE_MAP_EDITOR

      if (action == "NO_ACTION" ||
          (m_startIdx <= 3 && !m_player.isConnected()))
	{
	  return false;
	}
      void (LocalPlayer::*ptr)() = m_player.actions(action).first;
      (m_player.*ptr)();
      return true;
    }

    virtual bool keyReleased(OIS::KeyEvent const &ke)
    {
      std::string action = m_player.settings().actionForKey(
          static_cast<std::size_t>(m_player.order()), ke.key);
      if (action == "NO_ACTION" ||
          (m_startIdx <= 3 && !m_player.isConnected()))
	{
	  return false;
	}
      void (LocalPlayer::*ptr)() = m_player.actions(action).second;
      (m_player.*ptr)();
      return true;
    }

    virtual bool mouseMoved(OIS::MouseEvent const &)
    {
      return (false);
    }

    virtual bool mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
    {
      return (false);
    }

    virtual bool mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
    {
      return (false);
    }

    void setStart()
    {
      if (m_gui)
	{
	  if (m_time.reached())
	    {
	      m_startIdx++;
	      if (m_startIdx <= 4)
		{
		  for (std::uint8_t playerIndex = 0;
		       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
		    {
		      nope::log::Log(Debug)
		          << "Player index : " << static_cast<int>(playerIndex)
		          << " StartIdx : " << m_startIdx - 1;
		      m_start[playerIndex][m_startIdx - 1]->setVisible(true);
		    }
		  nope::log::Log(Debug) << "Reset Time!";
		  m_time.reset();
		}
	      else if (m_startIdx == 5)
		{
		  for (std::uint8_t playerIndex = 0;
		       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
		    {
		      m_start[playerIndex][0]->setVisible(false);
		      m_start[playerIndex][1]->setVisible(false);
		      m_start[playerIndex][2]->setVisible(false);
		      m_start[playerIndex][3]->setVisible(false);
		    }
		}
	    }
	}
      else if (m_time.reached() && m_startIdx < 5)
	{
	  ++m_startIdx;
	  m_time.reset();
	}
    }

    void setSpeed()
    {
      if (m_gui)
	{
	  static const std::string image("Image");

	  static std::vector<std::string> gl_speedAssets = {
	      "pakpak_pack/0", "pakpak_pack/1", "pakpak_pack/2",
	      "pakpak_pack/3", "pakpak_pack/4", "pakpak_pack/5",
	      "pakpak_pack/6", "pakpak_pack/7", "pakpak_pack/8",
	      "pakpak_pack/9"};

	  for (std::uint8_t playerIndex = 0;
	       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
	    {
	      double rawSpeed = m_players[playerIndex]->car().speed();

	      std::uint32_t speed = static_cast<std::uint32_t>(
	          (rawSpeed > 0 ? rawSpeed : -rawSpeed) / 50);
	      if (speed < 1000)
		{
		  std::uint32_t unit = speed % 10;
		  std::uint32_t decade = (speed / 10) % 10;
		  std::uint32_t thousand = (speed / 100) % 10;

		  if (thousand)
		    {
		      m_speed[playerIndex][2]->setVisible(true);
		      m_speed[playerIndex]
		             [2]->setProperty(image, gl_speedAssets[thousand]);
		    }
		  else
		    {
		      m_speed[playerIndex][2]->setVisible(false);
		    }

		  if (decade)
		    {
		      m_speed[playerIndex][1]->setVisible(true);
		      m_speed[playerIndex]
		             [1]->setProperty(image, gl_speedAssets[decade]);
		    }
		  else if (thousand)
		    {
		      m_speed[playerIndex][1]->setVisible(true);
		      m_speed[playerIndex][1]->setProperty(
		          image, gl_speedAssets[game::SPEED_UNITS::U0]);
		    }
		  else
		    {
		      m_speed[playerIndex][1]->setVisible(false);
		      m_speed[playerIndex][1]->setProperty(image, "");
		    }

		  if (unit)
		    {
		      m_speed[playerIndex]
		             [0]->setProperty(image, gl_speedAssets[unit]);
		    }
		  else
		    {
		      m_speed[playerIndex][0]->setProperty(
		          image, gl_speedAssets[game::SPEED_UNITS::U0]);
		    }
		}
	    }
	}
    }

    void setPosition()
    {
      if (m_gui && !m_player.isConnected())
	{
	  static const std::string image("Image");

	  static std::vector<std::string> gl_positionAssets = {
	      "pakpak_pack/ST", "pakpak_pack/ND", "pakpak_pack/RD",
	      "pakpak_pack/TH"};

	  static std::vector<std::string> gl_speedAssets = {
	      "pakpak_pack/1", "pakpak_pack/2", "pakpak_pack/3",
	      "pakpak_pack/4", "pakpak_pack/5", "pakpak_pack/6",
	      "pakpak_pack/7", "pakpak_pack/8", "pakpak_pack/9",
	      "pakpak_pack/0"};

	  for (std::uint8_t playerIndex = 0;
	       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
	    {
	      std::uint32_t position = static_cast<std::uint32_t>(
	          m_players[playerIndex]->getRank());

	      if (position <= 9)
		m_positionPrefix[playerIndex]->setProperty(
		    image, gl_speedAssets[position]);
	      if (position <= 3)
		{
		  m_positionSuffix[playerIndex]->setProperty(
		      image, gl_positionAssets[position]);
		}
	      else
		{
		  m_positionSuffix[playerIndex]->setProperty(
		      image, gl_positionAssets[game::POSITIONS::TH]);
		}
	    }
	}
    }

    void setFinish()
    {
      if (m_gui && !m_player.isConnected())
	{
	  std::uint16_t count = 0;

	  for (std::uint8_t playerIndex = 0;
	       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
	    {
	      CEGUI::Window *finishedSplash =
	          m_gui->getRoot()->getChild(screens[playerIndex] + "game");
	      if (m_players[playerIndex]->getFinished())
		{
		  ++count;
		  if (!finishedSplash->isVisible())
		    {
		      m_gameData.addFinalPlayer(
		          m_players[playerIndex]->getID());
		      finishedSplash->setVisible(true);
		    }
		}
	    }
	  if (count == m_players.size() && !game::Pauser::isPaused())
	    {
	      game::Pauser::pause();
	      m_layerStack.push(GameLayer::PostGame);
	    }
	}
    }

  private:
    LocalPlayer &  m_player;
    CEGUI::Window *m_speed[PCOUNT][3];
    CEGUI::Window *m_positionSuffix[PCOUNT];
    CEGUI::Window *m_positionPrefix[PCOUNT];
    CEGUI::Window *m_start[PCOUNT][4];
    std::int32_t   m_startIdx;
    Timer          m_time;
  };
}

#endif // !INGAME_HPP_
