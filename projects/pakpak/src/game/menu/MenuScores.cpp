//
// Created by brout_m on 12/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuScores::MenuScores(menu::MenuManager &menuManager, GUI &gui,
                         SettingsPlayer &settings)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_settings(settings)

  {
  }

  void MenuScores::draw()
  {
  }

  void MenuScores::entry()
  {
    m_gui.loadLayout("scores.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuScores::onBackClick, this));
      CEGUI::WindowManager *winManager = CEGUI::WindowManager::getSingletonPtr();
      CEGUI::ItemEntry* itm = (CEGUI::ItemEntry*)winManager->createWindow("TaharezLook/ListboxItem");
      CEGUI::ItemEntry* itm2 = (CEGUI::ItemEntry*)winManager->createWindow("TaharezLook/ListboxItem");
      itm->setText("COUILLE");
      itm2->setText("BITE");
      ((CEGUI::ItemListbox *)m_gui.getRoot()->getChild("list_best_times"))->addItem(itm);
      ((CEGUI::ItemListbox *)m_gui.getRoot()->getChild("list_total_km"))->addItem(itm2);

//    m_gui.getRoot()->getChild("list_finished_tracks")->setProperty("Text", "Hoy");

  //  m_gui.getRoot()->getChild("list_total_km")->setProperty("Text", "Hoy");

    //m_gui.getRoot()->getChild("list_max_speed")->setProperty("Text", "Hay");

    //m_gui.getRoot()->getChild("list_collision_count")->setProperty("Text", "Hiy");
  }

  void MenuScores::exit()
  {
  }

  void MenuScores::destroy()
  {
  }

  GameState MenuScores::update() const
  {
    return m_curState;
  }

  void MenuScores::build()
  {
  }

  bool MenuScores::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);
    return true;
  }

  bool MenuScores::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuScores::mousePressed(const OIS::MouseEvent &arg,
                                OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuScores::mouseReleased(const OIS::MouseEvent &arg,
                                 OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuScores::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        (CEGUI::Key::Scan)arg.key);
    return true;
  }

  CEGUI::MouseButton MenuScores::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuScores::onBackClick(CEGUI::EventArgs const &)
  {
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }
}