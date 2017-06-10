//
// Created by brout_m on 10/06/17.
//

#include "game/menu/AssetSetter.hpp"

core::AssetSetter::AssetSetter()
{
}

core::AssetSetter::~AssetSetter()
{
}

void core::AssetSetter::setTextColor(CEGUI::Window &               obj,
                                     core::AssetSetter::TEXT_COLOR col)
{
  obj.setProperty("HoverTextColour", m_texts[col]);
  obj.setProperty("NormalTextColour", m_texts[col]);
  obj.setProperty("PushedTextColour", m_texts[col]);
}

void core::AssetSetter::setButtonBack(CEGUI::Window &                 obj,
                                      core::AssetSetter::BUTTON_COLOR col)
{
  obj.setProperty("HoverImage", m_buttons[col][BUTTON_TYPE::FULL_RELEASED]);
  obj.setProperty("NormalImage", m_buttons[col][BUTTON_TYPE::DEMI_RELEASED]);
  obj.setProperty("PushedImage", m_buttons[col][BUTTON_TYPE::FULL_PRESSED]);
}

std::map<core::AssetSetter::BUTTON_COLOR,
         std::map<core::AssetSetter::BUTTON_TYPE, std::string>>
    core::AssetSetter::m_buttons = {
        {BUTTON_COLOR::BYELLOW,
         {{BUTTON_TYPE::DEMI_RELEASED, "yellow_assets/large_demi_released"},
          {BUTTON_TYPE::FULL_RELEASED, "yellow_assets/large_full_released"},
          {BUTTON_TYPE::FULL_PRESSED, "yellow_assets/large_full_pressed"}}},
        {BUTTON_COLOR::BBLUE,
         {{BUTTON_TYPE::DEMI_RELEASED, "blue_assets/large_demi_released"},
          {BUTTON_TYPE::FULL_RELEASED, "blue_assets/large_full_released"},
          {BUTTON_TYPE::FULL_PRESSED, "blue_assets/large_full_pressed"}}},
        {BUTTON_COLOR::BRED,
         {{BUTTON_TYPE::DEMI_RELEASED, "red_assets/large_demi_released"},
          {BUTTON_TYPE::FULL_RELEASED, "red_assets/large_full_released"},
          {BUTTON_TYPE::FULL_PRESSED, "red_assets/large_full_pressed"}}},
        {BUTTON_COLOR::BGREEN,
         {{BUTTON_TYPE::DEMI_RELEASED, "green_assets/large_demi_released"},
          {BUTTON_TYPE::FULL_RELEASED, "green_assets/large_full_released"},
          {BUTTON_TYPE::FULL_PRESSED, "green_assets/large_full_pressed"}}},
        {BUTTON_COLOR::BGREY,
         {{BUTTON_TYPE::DEMI_RELEASED, "grey_assets/large_demi_released"},
          {BUTTON_TYPE::FULL_RELEASED, "grey_assets/large_full_released"},
          {BUTTON_TYPE::FULL_PRESSED, "grey_assets/large_full_pressed"}}}

};

std::map<core::AssetSetter::TEXT_COLOR, std::string>
    core::AssetSetter::m_texts = {
        {TEXT_COLOR::TYELLOW,
         "tl:FFFFF032 tr:FFFFF032 bl:FFFFFF96 br:FFFFFF96"},
        {TEXT_COLOR::TBLACK,
         "tl:FF000000 tr:FF000000 bl:FF646464 br:FF646464"},
        {TEXT_COLOR::TBLUE, "tl:FFDCFAFF tr:FFDCFAFF bl:FFFAFAFF br:FFFAFAFF"},
        {TEXT_COLOR::TRED, "tl:FFAA1E00 tr:FFAA1E00 bl:FFD2500A br:FFD2500A"}};