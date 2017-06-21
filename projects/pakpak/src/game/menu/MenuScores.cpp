//
// Created by brout_m on 12/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuScores::MenuScores(menu::MenuManager &menuManager, GUI &gui,
                         SettingsPlayer &settings, SoundManager &sound)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_settings(settings), m_sound(sound)

  {
  }

  void MenuScores::draw()
  {
  }

  void MenuScores::entry()
  {
    m_gui.loadLayout("scores.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    if (!m_gui.getRoot()->getChild("back_button"))
      {
	throw GUIError("Missing asset back_button");
      }
    if (!m_gui.getRoot()->getChild("list_best_times"))
      {
	throw GUIError("Missing asset list_best_times");
      }
    if (!m_gui.getRoot()->getChild("list_finished_tracks"))
      {
	throw GUIError("Missing asset list_finished_tracks");
      }
    if (!m_gui.getRoot()->getChild("list_max_speed"))
      {
	throw GUIError("Missing asset list_max_speed");
      }
    if (!m_gui.getRoot()->getChild("list_collision_count"))
      {
	throw GUIError("Missing asset list_collision_count");
      }
    if (!m_gui.getRoot()->getChild("list_total_km"))
      {
	throw GUIError("Missing asset list_total_km");
      }
    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuScores::onBackClick, this));

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventMouseEntersArea,
            CEGUI::Event::Subscriber(&MenuScores::onBackArea, this));

    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_best_times"))
        ->setAutoResizeEnabled(1);
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_finished_tracks"))
        ->setAutoResizeEnabled(1);
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_max_speed"))
        ->setAutoResizeEnabled(1);
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_collision_count"))
        ->setAutoResizeEnabled(1);
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_total_km"))
        ->setAutoResizeEnabled(1);
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_best_times"))
        ->disable();
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_finished_tracks"))
        ->disable();
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_max_speed"))
        ->disable();
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_collision_count"))
        ->disable();
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("list_total_km"))
        ->disable();
    CEGUI::WindowManager *winManager = CEGUI::WindowManager::getSingletonPtr();

    for (std::int32_t i = 0; i < m_settings.getSaveData().size(); ++i)
      {
	CEGUI::ItemEntry *itm = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));
	CEGUI::ItemEntry *itm2 = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));
	CEGUI::ItemEntry *itm3 = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));
	CEGUI::ItemEntry *itm4 = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));
	CEGUI::ItemEntry *itm5 = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));

	itm->setText("Player " + std::to_string(i + 1) + " : " +
	             m_settings.getSaveData()[i].getData().s_bestTime);
	itm2->setText(
	    "Player " + std::to_string(i + 1) + " : " +
	    std::to_string(
	        m_settings.getSaveData()[i].getData().s_collisionCount) +
	    " collisions");
	itm3->setText(
	    "Player " + std::to_string(i + 1) + " : " +
	    std::to_string(m_settings.getSaveData()[i].getData().s_maxSpeed) +
	    " Km/h");
	itm4->setText(
	    "Player " + std::to_string(i + 1) + " : " +
	    std::to_string(m_settings.getSaveData()[i].getData().s_totalKm) +
	    " Km");
	itm5->setText(
	    "Player " + std::to_string(i + 1) + " : " +
	    std::to_string(
	        m_settings.getSaveData()[i].getData().s_trackFinished) +
	    " track finished");

	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("list_best_times"))
	    ->addItem(itm);
	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("list_collision_count"))
	    ->addItem(itm2);
	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("list_max_speed"))
	    ->addItem(itm3);
	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("list_total_km"))
	    ->addItem(itm4);
	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("list_finished_tracks"))
	    ->addItem(itm5);
      }
    nope::log::Log(Debug) << "Nb Item of best_times : "
                          << static_cast<CEGUI::ItemListbox *>(
                                 m_gui.getRoot()->getChild("list_best_times"))
                                 ->getItemCount();
    nope::log::Log(Debug) << "Nb Item of best_times : "
                          << static_cast<CEGUI::ItemListbox *>(
                                 m_gui.getRoot()->getChild(
                                     "list_finished_tracks"))
                                 ->getItemCount();
    nope::log::Log(Debug) << "Nb Item of best_times : "
                          << static_cast<CEGUI::ItemListbox *>(
                                 m_gui.getRoot()->getChild("list_max_speed"))
                                 ->getItemCount();
    nope::log::Log(Debug) << "Nb Item of best_times : "
                          << static_cast<CEGUI::ItemListbox *>(
                                 m_gui.getRoot()->getChild(
                                     "list_collision_count"))
                                 ->getItemCount();
    nope::log::Log(Debug) << "Nb Item of best_times : "
                          << static_cast<CEGUI::ItemListbox *>(
                                 m_gui.getRoot()->getChild("list_total_km"))
                                 ->getItemCount();
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
    context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
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
        static_cast<CEGUI::Key::Scan>(arg.key));
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
    soundClick();
    m_sound.playSound(core::ESound::BACK_RACE_SOUND);
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuScores::onBackArea(CEGUI::EventArgs const &)
  {
    soundPass();
    return false;
  }

  void MenuScores::soundPass()
  {
    m_sound.playSound(core::ESound::PASS_BUTTON);
  }

  void MenuScores::soundClick()
  {
    m_sound.playSound(core::ESound::CLICK_BUTTON);
  }
}
