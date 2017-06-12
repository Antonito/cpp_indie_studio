#include "pakpak_stdafx.hpp"

namespace game
{
  Map::Map(game::GameData &gamedata)
      : m_gamedata(gamedata), m_points(), m_map(nullptr), m_node(nullptr)
  {
  }

  Map::Map(game::GameData &gamedata, std::string const &filename)
      : m_gamedata(gamedata), m_points(), m_map(nullptr), m_node(nullptr)
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

    m_map = m_gamedata.sceneMgr()->createEntity(ss.str() + "_ent", ss.str());

    ss.str("");
    ss << "MapNode" << id;
    m_node = m_gamedata.sceneMgr()->getRootSceneNode()->createChildSceneNode(
        ss.str());
    m_node->attachObject(m_map);

    m_node->setScale(1, 1, 1);
    m_node->setPosition(0, 0, 0);

    std::size_t    vertexCount;
    Ogre::Vector3 *vertices;
    std::size_t    indexCount;
    std::uint32_t *indices;

    tools::getMeshInformation(meshptr.getPointer(), vertexCount, vertices,
                              indexCount, indices);

    std::unique_ptr<OgreBulletCollisions::TriangleMeshCollisionShape> shape =
        std::make_unique<OgreBulletCollisions::TriangleMeshCollisionShape>(
            vertices, vertexCount, indices, indexCount);
    nope::log::Log(Warning) << "VCount: " << vertexCount
                            << "\nICount: " << indexCount << std::endl;
    OgreBulletCollisions::TriangleMeshCollisionShape *_shape = shape.get();

    ss.str("");
    ss << "MapRigidBody" << id;
    OgreBulletDynamics::RigidBody *body;

    body = m_gamedata.addPhysicEntity(std::move(shape), ss.str());

    body->setStaticShape(_shape, 0, 0.6, Ogre::Vector3(0, 0, 0));
    // body->setDebugDisplayEnabled(false);
    // body->showDebugShape(false);
    // body->setShape(m_node, _shape2, 0.6, 0.6, 0, Ogre::Vector3::ZERO);

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
