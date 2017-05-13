#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <OgreVector4.h>
#include "MapBonus.hpp"
#include "MapElement.hpp"

class Map
{
public:
private:
  std::vector<MapBonus>      m_bonus;
  std::vector<MapElement>    m_elements;
  std::vector<ogre::Vector4> m_path;
  std::vector<Model>         m_objects;
  Model                      m_model;
  SkyBox                     m_sky;
};

#endif // !MAP_HPP_
