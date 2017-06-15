#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <cstdint>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreMesh.h>

namespace tools
{
  void getMeshInformation(
      Ogre::Mesh *mesh, std::size_t &vertex_count, Ogre::Vector3 *&vertices,
      std::size_t &index_count, std::uint32_t *&indices,
      Ogre::Vector3 const &   position = Ogre::Vector3::ZERO,
      Ogre::Quaternion const &orient = Ogre::Quaternion::IDENTITY,
      Ogre::Vector3 const &   scale = Ogre::Vector3::UNIT_SCALE);
}

#endif // !TOOLS_HPP_