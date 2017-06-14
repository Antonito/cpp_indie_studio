//
// Created by brout_m on 09/06/17.
//

#ifndef MENUOPTIONS_HPP
#define MENUOPTIONS_HPP

#include "game/menu/GUI.hpp"
#include "game/menu/MenuManager.hpp"
#include "game/menu/IMenuLayer.hpp"
#include "game/menu/AssetSetter.hpp"

namespace core
{
  class MenuOptions : public IMenuLayer
  {
  public:
    MenuOptions(menu::MenuManager &menuManager, GUI &gui);
    virtual ~MenuOptions(){};
    void      draw();
    void      entry();
    void      exit();
    void      destroy();
    GameState update() const;
    void      build();
    bool keyPressed(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool keyReleased(const OIS::KeyEvent &arg);

  private:
    MenuOptions(MenuOptions const &) = delete;
    MenuOptions(MenuOptions &&) = delete;
    MenuOptions &      operator=(MenuOptions const &) = delete;
    MenuOptions &      operator=(MenuOptions &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
    bool onVolumeLevel0(CEGUI::EventArgs const &);
    bool onVolumeLevel25(CEGUI::EventArgs const &);
    bool onVolumeLevel50(CEGUI::EventArgs const &);
    bool onVolumeLevel75(CEGUI::EventArgs const &);
    bool onVolumeLevel100(CEGUI::EventArgs const &);
    bool onLowClick(CEGUI::EventArgs const &);
    bool onHighClick(CEGUI::EventArgs const &);
    bool onKeymapEdit(CEGUI::EventArgs const &);
    bool onBackClick(CEGUI::EventArgs const &);
    void swapButtons(CEGUI::Window **, size_t &, size_t,
                     core::AssetSetter::ButtonStyle const &,
                     core::AssetSetter::ButtonStyle const &);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
    CEGUI::Window *    m_volumeButtons[5];
    size_t             m_volumeSelected;
    CEGUI::Window *    m_graphicButtons[2];
    size_t             m_graphicSelected;
  };
}

#endif // MENUOPTIONS_HPP
