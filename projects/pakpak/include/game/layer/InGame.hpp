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

  template <std::uint8_t PCOUNT>
  class InGame           final : public ALayer
  {
  public:
    InGame() = delete;
    InGame(GameData &data, LocalPlayer &player, core::HUD *hud,
           std::vector<std::unique_ptr<LocalPlayer>> &players)
        : ALayer(data, player, hud, players), m_player(player), m_speed(),
          m_positionSuffix(), m_positionPrefix(), m_start(), m_startIdx(0), m_time(2000)
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

	  static const std::vector<std::string> screens = {
	      "player1/", "player2/", "player3/", "player4/"};

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
              m_start[playerIndex][0] = m_gui->getRoot()->getChild(screens[playerIndex] + "1");
              m_start[playerIndex][0]->setVisible(false);
              m_start[playerIndex][1] = m_gui->getRoot()->getChild(screens[playerIndex] + "2");
              m_start[playerIndex][1]->setVisible(false);
              m_start[playerIndex][2] = m_gui->getRoot()->getChild(screens[playerIndex] + "3");
              m_start[playerIndex][2]->setVisible(false);
              m_start[playerIndex][3] = m_gui->getRoot()->getChild(screens[playerIndex] + "GO");
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
        if (m_time.reached() && m_startIdx < 5)
        {
            if (m_startIdx >= 1)
            {
                for (std::uint8_t playerIndex = 0;
                     playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
                {
                    m_start[playerIndex][m_startIdx - 1]->setVisible(false);
                }
            }
            m_startIdx++;
            for (std::uint8_t playerIndex = 0;
                 playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
            {
                m_start[playerIndex][m_startIdx - 1]->setVisible(true);
            }
            m_time.reset();
        }
    }

    virtual bool keyPressed(OIS::KeyEvent const &ke)
    {
      std::string action = m_player.settings().actionForKey(
          static_cast<std::size_t>(m_player.order()), ke.key);

      if (action == "NO_ACTION" || m_startIdx < 5)
	{
	  return false;
	}
      nope::log::Log(Info) << "DOING ACTION";
      void (LocalPlayer::*ptr)() = m_player.actions(action).first;
      (m_player.*ptr)();
      return true;
    }

    virtual bool keyReleased(OIS::KeyEvent const &ke)
    {
      std::string action = m_player.settings().actionForKey(
          static_cast<std::size_t>(m_player.order()), ke.key);
      if (action == "NO_ACTION" || m_startIdx < 5)
	{
	  return false;
	}
      nope::log::Log(Info) << "DOING ACTION";
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
	      std::uint32_t speed = m_players[playerIndex]->getSpeed();
	      if (speed < 1000)
		{

		  std::uint32_t unit = speed % 10;
		  std::uint32_t decade = speed / 10;
		  std::uint32_t thousand = speed / 100;

		  if (thousand)
		    {
		      m_speed[playerIndex][2]->setProperty(
		          image, gl_speedAssets[thousand - 1]);
		    }
		  else
		    {
		      m_speed[playerIndex][2]->setProperty(image, "");
		    }

		  if (decade)
		    {
		      m_speed[playerIndex][1]->setProperty(
		          image, gl_speedAssets[decade - 1]);
		    }
		  else if (thousand)
		    {
		      m_speed[playerIndex][1]->setProperty(
		          image, gl_speedAssets[game::SPEED_UNITS::U0]);
		    }
		  else
		    {
		      m_speed[playerIndex][1]->setProperty(image, "");
		    }

		  if (unit)
		    {
		      m_speed[playerIndex]
		             [0]->setProperty(image, gl_speedAssets[unit - 1]);
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
      if (m_gui)
	{
	  static const std::string image("Image");

	  static std::vector<std::string> gl_positionAssets = {
	      "pakpak_pack/ST", "pakpak_pack/ND", "pakpak_pack/RD",
	      "pakpak_pack/TH"};

	  static std::vector<std::string> gl_speedAssets = {
	      "pakpak_pack/0", "pakpak_pack/1", "pakpak_pack/2",
	      "pakpak_pack/3", "pakpak_pack/4", "pakpak_pack/5",
	      "pakpak_pack/6", "pakpak_pack/7", "pakpak_pack/8",
	      "pakpak_pack/9"};

	  for (std::uint8_t playerIndex = 0;
	       playerIndex < PCOUNT && playerIndex < 4; ++playerIndex)
	    {
	      std::uint32_t position = m_players[playerIndex]->getPosition();

	      if (position <= 9 && m_positionPrefix)
		m_positionPrefix[playerIndex]->setProperty(
		    image, gl_speedAssets[position]);
	      if (position <= 3)
		{
		  if (m_positionSuffix)
		    m_positionSuffix[playerIndex]->setProperty(
		        image, gl_positionAssets[position - 1]);
		}
	      else
		{
		  if (m_positionSuffix)
		    m_positionSuffix[playerIndex]->setProperty(
		        image, gl_positionAssets[game::POSITIONS::TH]);
		}
	    }
	}
    }

  private:
    LocalPlayer &  m_player;
    CEGUI::Window *m_speed[PCOUNT][3];
    CEGUI::Window *m_positionSuffix[PCOUNT];
    CEGUI::Window *m_positionPrefix[PCOUNT];
    CEGUI::Window *m_start[PCOUNT][4];
    std::int32_t    m_startIdx;
    Timer           m_time;
  };
}

#endif // !INGAME_HPP_
