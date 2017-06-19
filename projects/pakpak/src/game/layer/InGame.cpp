#include "pakpak_stdafx.hpp"

namespace game
{
  static std::vector<std::string> gl_speedAssets = {
      "pakpak_pack/0", "pakpak_pack/1", "pakpak_pack/2", "pakpak_pack/3",
      "pakpak_pack/4", "pakpak_pack/5", "pakpak_pack/6", "pakpak_pack/7",
      "pakpak_pack/8", "pakpak_pack/9"};

  static std::vector<std::string> gl_positionAssets = {
      "pakpak_pack/ST", "pakpak_pack/ND", "pakpak_pack/RD", "pakpak_pack/TH"};

  InGame::InGame(GameData &data, LocalPlayer &player, core::HUD *hud)
      : ALayer(data, player, hud), m_player(player), m_speed(),
        m_positionSuffix(nullptr), m_positionPrefix(nullptr)
  {
  }

  InGame::~InGame()
  {
  }

  void InGame::enable()
  {
    nope::log::Log(Debug) << "Enabling InGame";
    if (m_gui)
      {
	m_gui->loadLayout("gui_ingame.layout");
	m_speed[0] = m_gui->getRoot()->getChildRecursive("unit");
	m_speed[1] = m_gui->getRoot()->getChildRecursive("decade");
	m_speed[2] = m_gui->getRoot()->getChildRecursive("thousand");
	m_positionSuffix =
	    m_gui->getRoot()->getChildRecursive("place_postfix");
	m_positionPrefix = m_gui->getRoot()->getChildRecursive("place_suffix");
      }
  }

  void InGame::disable()
  {
  }

  void InGame::update()
  {
  }

  void InGame::display()
  {
  }

  bool InGame::keyPressed(OIS::KeyEvent const &ke)
  {
    std::string action = m_player.settings().actionForKey(
        static_cast<std::size_t>(m_player.order()), ke.key);

#if defined(INDIE_MAP_EDITOR)
    switch (ke.key)
      {
      case OIS::KC_SPACE:
	m_gameData.map().addPoint(m_player.car().position());
	break;
      case OIS::KC_RETURN:
	m_gameData.map().save();
	break;
      default:
	break;
      }
#endif // !INDIE_MAP_EDITOR

    if (action == "NO_ACTION")
      {
	return false;
      }

    nope::log::Log(Info) << "DOING ACTION";
    void (LocalPlayer::*ptr)() = m_player.actions(action).first;
    (m_player.*ptr)();
    return true;
  }

  bool InGame::keyReleased(OIS::KeyEvent const &ke)
  {
    std::string action = m_player.settings().actionForKey(
        static_cast<std::size_t>(m_player.order()), ke.key);
    if (action == "NO_ACTION")
      {
	return false;
      }
    nope::log::Log(Info) << "DOING ACTION";
    void (LocalPlayer::*ptr)() = m_player.actions(action).second;
    (m_player.*ptr)();
    return true;
  }

  bool InGame::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool InGame::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool InGame::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  void InGame::setSpeed(std::uint32_t speed)
  {
    static const std::string image("Image");

    if (speed < 1000)
      {
	std::uint32_t unit = speed % 10;
	std::uint32_t decade = speed / 10;
	std::uint32_t thousand = speed / 100;

	if (thousand)
	  {
	    m_speed[2]->setProperty(image, gl_speedAssets[thousand - 1]);
	  }
	else
	  {
	    m_speed[2]->setProperty(image, "");
	  }

	if (decade)
	  {
	    m_speed[1]->setProperty(image, gl_speedAssets[decade - 1]);
	  }
	else if (thousand)
	  {
	    m_speed[1]->setProperty(image,
	                            gl_speedAssets[game::SPEED_UNITS::U0]);
	  }
	else
	  {
	    m_speed[1]->setProperty(image, "");
	  }

	if (unit)
	  {
	    m_speed[0]->setProperty(image, gl_speedAssets[unit - 1]);
	  }
	else
	  {
	    m_speed[0]->setProperty(image,
	                            gl_speedAssets[game::SPEED_UNITS::U0]);
	  }
      }
  }

  void InGame::setPosition(std::uint32_t position)
  {
    static const std::string image("Image");

    if (position <= 9 && m_positionPrefix)
      m_positionPrefix->setProperty(image, gl_speedAssets[position]);
    if (position <= 3)
      {
	if (m_positionSuffix)
	  m_positionSuffix->setProperty(image,
	                                gl_positionAssets[position - 1]);
      }
    else
      {
	if (m_positionSuffix)
	  m_positionSuffix->setProperty(
	      image, gl_positionAssets[game::POSITIONS::TH]);
      }
  }
}
