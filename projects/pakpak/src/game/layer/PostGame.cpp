#include "pakpak_stdafx.hpp"

namespace game
{
  PostGame::PostGame(GameData &data, ILayerStack &layer, core::HUD *hud,
                     std::vector<std::unique_ptr<LocalPlayer>> &players)
      : ALayer(data, layer, hud, players)
  {
  }

  PostGame::~PostGame()
  {
  }

  void PostGame::enable()
  {
    if (m_gui)
      {
	nope::log::Log(Debug) << "Enabling menu ranking";
	m_gui->addLayout("ranking.layout");
	m_gui->showCursor(true);
	m_gui->grabMouse();

	CEGUI::Window *button =
	    m_gui->getRoot()->getChildRecursive("quit_button");
	if (button)
	  {
	    button->subscribeEvent(
	        CEGUI::PushButton::EventClicked,
	        CEGUI::Event::Subscriber(&PostGame::onQuitClick, this));
	  }
      }
  }

  void PostGame::disable()
  {
    if (m_gui)
    {
      nope::log::Log(Debug) << "disabling ranking menu";
      m_gui->removeLayout("ranking.layout");
      m_gui->hideCursor(true);
    }
  }

  void PostGame::update()
  {
  }

  void PostGame::display()
  {
  }

  bool PostGame::keyPressed(OIS::KeyEvent const &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return (false);
  }

  bool PostGame::keyReleased(OIS::KeyEvent const &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return (true);
  }

  bool PostGame::mouseMoved(OIS::MouseEvent const &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectMouseMove(static_cast<float>(arg.state.X.rel),
                            static_cast<float>(arg.state.Y.rel));
    return (true);
  }

  bool PostGame::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID button)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
        convertButton(button));
    return (true);
  }

  bool PostGame::mouseReleased(OIS::MouseEvent const &,
                               OIS::MouseButtonID button)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
        convertButton(button));
    return (true);
  }

  bool PostGame::onQuitClick(CEGUI::EventArgs const &)
  {
    //game::Pauser::unpause();
    m_gui->setQuit(true);
    return (true);
  }

  CEGUI::MouseButton PostGame::convertButton(OIS::MouseButtonID buttonID)
  {
    switch (buttonID)
      {
      case OIS::MB_Left:
	return CEGUI::LeftButton;

      case OIS::MB_Right:
	return CEGUI::RightButton;

      case OIS::MB_Middle:
	return CEGUI::MiddleButton;

      default:
	return CEGUI::LeftButton;
      }
  }
}
