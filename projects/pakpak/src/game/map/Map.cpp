#include "pakpak_stdafx.hpp"

namespace game
{
  Map::Map(Ogre::SceneManager *sceneMgr)
      : m_sceneMgr(sceneMgr), m_points(), m_map(nullptr), m_node(nullptr)
  {
  }

  Map::Map(Ogre::SceneManager *sceneMgr, std::string const &filename)
      : m_sceneMgr(sceneMgr), m_points(), m_map(nullptr), m_node(nullptr)
  {
    this->loadFromFile(filename);
  }

  Map::~Map()
  {
  }

  void Map::loadFromFile(std::string filename)
  {
    static std::int32_t id = 0;
    std::stringstream   ss;
    std::ifstream       fs(filename.c_str());

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
    for (std::size_t i = 0; i < p.size(); i += 2)
      {
	m_points.emplace_back(
	    Ogre::Vector3(p[i].x, p[i].y, p[i].z),
	    Ogre::Vector3(p[i + 1].x, p[i + 1].y, p[i + 1].z));
      }

    std::int32_t pathLen = static_cast<std::int32_t>(filename.length());

    while (pathLen >= 0 && filename[static_cast<std::size_t>(pathLen)] != '/')
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

    std::size_t size = static_cast<std::size_t>(fileStat.st_size);

    Ogre::MemoryDataStream *memstream =
        new Ogre::MemoryDataStream(filename, size, true);

    std::fread(memstream->getPtr(), size, 1, meshFile);
    std::fclose(meshFile);

    ss.str("");
    ss << "MapMesh" << id;

    Ogre::MeshPtr meshptr = Ogre::MeshManager::getSingleton().createManual(
        ss.str(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::MeshSerializer meshSerializer;
    Ogre::DataStreamPtr  stream(memstream);

    meshSerializer.importMesh(stream, meshptr.getPointer());

    m_map = m_sceneMgr->createEntity(ss.str() + "_ent", ss.str());

    ss.str("");
    ss << "MapNode" << id;
    m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode(ss.str());
    m_node->attachObject(m_map);

    m_node->setScale(1000, 100, 1000);
    m_node->setPosition(0, 100, 0);

    ++id;
  }

  void Map::unload()
  {
    m_points.clear();
  }

  Map::MapData::MapData() : points(), elements()
  {
  }

  Map::MapData::Point::Point() : x(0.0), y(0.0), z(0.0)
  {
  }

  Map::MapData::Quaternion::Quaternion() : x(0.0), y(0.0), z(0.0), w(0.0)
  {
  }

  Map::MapData::Element::Element() : pos(), rot(), type(0)
  {
  }
}
