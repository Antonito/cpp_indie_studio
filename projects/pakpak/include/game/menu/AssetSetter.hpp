//
// Created by brout_m on 10/06/17.
//

#ifndef CPP_INDIE_STUDIO_ASSETSETTER_HPP
#define CPP_INDIE_STUDIO_ASSETSETTER_HPP

#include <map>
#include <CEGUI/Window.h>

namespace core
{
  class AssetSetter
  {
  public:
    enum BUTTON_TYPE
    {
      FULL_RELEASED,
      DEMI_RELEASED,
      FULL_PRESSED
    };

    enum BUTTON_COLOR
    {
      BYELLOW,
      BRED,
      BGREEN,
      BBLUE,
      BGREY
    };

    enum TEXT_COLOR
    {
      TBLACK,
      TYELLOW,
      TBLUE,
      TRED
    };

    AssetSetter();
    ~AssetSetter();

    static void setTextColor(CEGUI::Window &obj,
                             enum TEXT_COLOR col);
    static void setButtonBack(CEGUI::Window &obj,
                               enum BUTTON_COLOR col);

  private:
    AssetSetter(AssetSetter const &) = delete;
    AssetSetter(AssetSetter &&) = delete;
    AssetSetter &operator=(AssetSetter const &) = delete;
    AssetSetter &operator=(AssetSetter &&) = delete;

    static std::map<BUTTON_COLOR, std::map<BUTTON_TYPE, std::string>> m_buttons;
    static std::map<TEXT_COLOR, std::string>   m_texts;
  };
}

#endif // CPP_INDIE_STUDIO_ASSETSETTER_HPP
