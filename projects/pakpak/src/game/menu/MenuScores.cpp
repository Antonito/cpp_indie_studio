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
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!m_gui.getRoot()->getChild("list_best_times"))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!m_gui.getRoot()->getChild("list_finished_tracks"))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!m_gui.getRoot()->getChild("list_max_speed"))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!m_gui.getRoot()->getChild("list_collision_count"))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!m_gui.getRoot()->getChild("list_total_km"))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
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

    for (std::int32_t i = 0; i < 10; ++i)
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

	itm->setText(
	    "Place " + std::to_string(i + 1) + " : " +
	    std::to_string(m_settings.m_data[0].getData().s_bestTime[i]) +
	    " seconds");
	itm2->setText("Place " + std::to_string(i + 1) + " : " +
	              std::to_string(
	                  m_settings.m_data[0].getData().s_collisionCount[i]) +
	              " collisions");
	itm3->setText(
	    "Place " + std::to_string(i + 1) + " : " +
	    std::to_string(m_settings.m_data[0].getData().s_maxSpeed[i]) +
	    " Km/h");
	itm4->setText(
	    "Place " + std::to_string(i + 1) + " : " +
	    std::to_string(m_settings.m_data[0].getData().s_totalKm[i]) +
	    " Km");
	itm5->setText(
	    "Place " + std::to_string(i + 1) + " : " +
	    std::to_string(m_settings.m_data[0].getData().s_trackFinished[i]) +
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
