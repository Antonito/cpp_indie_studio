//
// Created by duhieu_b on 13/06/17.
//

#ifndef CPP_INDIE_STUDIO_IA_HPP
#define CPP_INDIE_STUDIO_IA_HPP

#include "pakpak_stdafx.hpp"

class Ia
{
public:
  Ia() = default;
  Ia(Ia const &) = delete;
  Ia(Ia &&) = delete;
  Ia &operator=(Ia &) = delete;
  Ia(Ogre::Vector3 &);
  virtual ~Ia();

  void           feedNodeRace(std::vector<Ogre::Vector3> &);
  Ogre::Vector3 &getPos() const;
  void           race(Ogre::Vector3 &, Ogre::Vector3 &, float);
  void           distNode();
  Ogre::Vector3 &getDir() const;

private:
  Ogre::Vector3              m_pos;
  std::int32_t               m_curNode;
  std::vector<Ogre::Vector3> m_nodes;
  Ogre::Vector3              m_newDir;
};

#endif // CPP_INDIE_STUDIO_IA_HPP
