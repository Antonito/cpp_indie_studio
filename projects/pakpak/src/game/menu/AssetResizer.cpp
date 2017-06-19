//
// Created by brout_m on 16/06/17.
//

#include "pakpak_stdafx.hpp"

namespace resizer
{
  AssetResizer::t_layoutMap AssetResizer::m_layouts = {};
  std::uint32_t             AssetResizer::m_width = 0;
  std::uint32_t             AssetResizer::m_height = 0;

  AssetResizer::AssetResizer()
  {
  }

  AssetResizer::~AssetResizer()
  {
  }

  void AssetResizer::addLayout(LAYOUTS layout, std::string const &layoutPath,
                               std::vector<std::string> const &layoutChildren)
  {
    CEGUI::Window *win;
    win = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layoutPath);
    if (!win)
      throw(std::runtime_error("Layout '" + layoutPath + "' not loaded"));
    nope::log::Log(Debug) << "Layout '" << layoutPath << "' loaded";

    t_childrenDimensionMap map;
    for (std::string const &child : layoutChildren)
      {
	CEGUI::Window *wChild;
	wChild = win->getChildRecursive(child);
	if (!wChild)
	  throw(std::runtime_error("Layout '" + layoutPath +
	                           "' doesn't have a child '" + child + "'"));
	nope::log::Log(Debug) << "Child '" << child << "' loaded of layout '"
	                      << layoutPath;
	Dimension dim(
	    wChild->getXPosition().d_offset, wChild->getYPosition().d_offset,
	    wChild->getWidth().d_offset, wChild->getHeight().d_offset,
	    win->getWidth().d_offset, win->getHeight().d_offset);
	map[child] = std::move(dim);
      }

    m_layouts.insert(
        std::make_pair<LAYOUTS,
                       std::pair<CEGUI::Window *, t_childrenDimensionMap>>(
            std::move(layout),
            std::make_pair<CEGUI::Window *, t_childrenDimensionMap>(
                std::move(win), std::move(map))));
    nope::log::Log(Debug) << "Added '" << layoutPath << "'";
  }

  bool AssetResizer::hasWindowResized(Ogre::RenderWindow &win)
  {
    if (win.getWidth() != m_width || win.getHeight() != m_height)
      {
	m_width = win.getWidth();
	m_height = win.getHeight();
	return (true);
      }
    return (false);
  }

  void AssetResizer::notifyResize(Ogre::RenderWindow &win)
  {
    if (win.getWidth() != m_width || win.getHeight() != m_height)
      {
	m_width = win.getWidth();
	m_height = win.getHeight();
	nope::log::Log(Debug) << "Resizing window";
	for (auto &layout : m_layouts)
	  {
	    CEGUI::Window *asset = layout.second.first;

	    for (auto &childs : layout.second.second)
	      {
		Dimension &dim = childs.second;
		nope::log::Log(Debug) << "'" << childs.first
		                      << "' new X : " << dim.m_x << " * "
		                      << static_cast<float>(m_width) << " = "
		                      << dim.m_x * static_cast<float>(m_width);
		nope::log::Log(Debug)
		    << "'" << childs.first << "' new Y : " << dim.m_y << " * "
		    << static_cast<float>(m_height) << " = "
		    << dim.m_x * static_cast<float>(m_height);
		if (childs.first == "pakpak")
		  {
		    asset->setXPosition(CEGUI::UDim(
		        dim.m_x, -dim.m_x * static_cast<float>(m_width)));
		    asset->setYPosition(CEGUI::UDim(
		        dim.m_y, -dim.m_y * static_cast<float>(m_height)));
		  }
		else
		  {
		    asset->setXPosition(CEGUI::UDim(
		        dim.m_x,
		        -dim.m_x * static_cast<float>(m_width) / 2.0f));
		    asset->setYPosition(CEGUI::UDim(
		        dim.m_y,
		        -dim.m_y * static_cast<float>(m_height) / 2.0f));
		  }
	      }
	  }
      }
  }

  CEGUI::Window &AssetResizer::operator[](LAYOUTS layout)
  {
    t_layoutMap::iterator it;

    if ((it = m_layouts.find(layout)) == m_layouts.end())
      throw(std::out_of_range("Layout hasn't been pushed to resizer"));
    return *it->second.first;
  }

  CEGUI::Window &AssetResizer::getLayout(LAYOUTS layout)
  {
    t_layoutMap::iterator it;

    if ((it = m_layouts.find(layout)) == m_layouts.end())
      throw(std::out_of_range("Layout hasn't been pushed to resizer"));
    return *it->second.first;
  }

  void AssetResizer::initResizer(std::uint32_t width, std::uint32_t height)
  {
    m_width = width;
    m_height = height;
  }
}
