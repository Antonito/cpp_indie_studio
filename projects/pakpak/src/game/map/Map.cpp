#include "pakpak_stdafx.hpp"

namespace game
{
  Map::Map(Ogre::SceneManager *sceneMgr)
      : m_sceneMgr(sceneMgr), m_points(), m_map(nullptr)
  {
  }

  Map::Map(Ogre::SceneManager *sceneMgr, std::string const &filename)
      : m_sceneMgr(sceneMgr), m_points(), m_map(nullptr)
  {
    this->loadFromFile(filename);
  }

  Map::~Map()
  {
  }

  void Map::loadFromFile(std::string filename)
  {
    std::ifstream     fs(filename.c_str());
    std::stringstream ss;

    if (fs.is_open() == false)
      {
	throw std::exception();
      }

    ss << fs.rdbuf();

    std::string str = ss.str();

    // Store the file content as a vector of uint8
    std::vector<std::uint8_t> content(str.begin(), str.end());

    // Deserialize it
    MapData data = nope::serialization::from_binary<MapData>(content);

    std::vector<MapData::Point> const &p = data.points;

    m_points.clear();
    m_points.reserve(p.size());
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(p.size()); i += 2)
      {
	m_points.emplace_back(
	    Ogre::Vector3(p[i].x, p[i].y, p[i].z),
	    Ogre::Vector3(p[i + 1].x, p[i + 1].y, p[i + 1].z));
      }

    std::int32_t pathLen = static_cast<std::int32_t>(filename.length());

    while (pathLen >= 0 && filename[pathLen] != '/')
      {
	--pathLen;
      }

    // This is now the path to our file
    filename.resize(static_cast<size_t>(pathLen));
    filename += "/map.mesh";

    // Load the actual mesh
    std::FILE *meshFile = std::fopen(filename.c_str(), "rb");

    if (meshFile == nullptr)
      {
	throw std::exception(); // TODO: change exception
      }

    struct stat fileStat;

    stat(filename.c_str(), &fileStat);

    Ogre::MemoryDataStream *memstream =
        new Ogre::MemoryDataStream(filename, fileStat.st_size, true);

    std::fread(memstream->getPtr(), fileStat.st_size, 1, meshFile);
    std::fclose(meshFile);

    Ogre::MeshPtr meshptr = Ogre::MeshManager::getSingleton().createManual(
        "MapMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::MeshSerializer meshSerializer;
    Ogre::DataStreamPtr  stream(memstream);

    meshSerializer.importMesh(stream, meshptr.getPointer());

    m_map = m_sceneMgr->createEntity("MapMesh_Ent", "MapMesh");
  }

  void Map::unload()
  {
    m_points.clear();
  }
}
