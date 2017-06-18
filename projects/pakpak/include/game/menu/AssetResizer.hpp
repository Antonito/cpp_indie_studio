//
// Created by brout_m on 16/06/17.
//

#ifndef CPP_INDIE_STUDIO_ASSETRESIZER_HPP
#define CPP_INDIE_STUDIO_ASSETRESIZER_HPP

#include "Dim.hpp"

namespace resizer
{
  enum LAYOUTS
  {
    RESIZE_HUD,
    RESIZE_PAUSE,
    RESIZE_MENU,
    RESIZE_OPTIONS,
    RESIZE_KEYMAP_EDITOR,
    RESIZE_SCORES,
    RESIZE_SOLOPLAYER,
    RESIZE_MULTIPLAYER
  };

  class AssetResizer
  {
  public:
    AssetResizer();
    ~AssetResizer();
    AssetResizer &operator=(AssetResizer const &) = delete;
    AssetResizer(AssetResizer const &) = delete;
    AssetResizer &operator=(AssetResizer &&) = delete;
    AssetResizer(AssetResizer &&) = delete;

    typedef std::map<std::string, Dimension> t_childrenDimensionMap;
    typedef std::map<LAYOUTS,
                     std::pair<CEGUI::Window *, t_childrenDimensionMap>>
        t_layoutMap;
    CEGUI::Window &operator[](LAYOUTS);
    static bool hasWindowResized(Ogre::RenderWindow &win);
    static CEGUI::Window &getLayout(LAYOUTS);
    static void           addLayout(LAYOUTS, std::string const &,
                          std::vector<std::string> const &);
    static void notifyResize(Ogre::RenderWindow &win);
    static void initResizer(std::uint32_t width, std::uint32_t height);

  private:
    static t_layoutMap   m_layouts;
    static std::uint32_t m_width;
    static std::uint32_t m_height;
  };
}

#endif // CPP_INDIE_STUDIO_ASSETRESIZER_HPP
