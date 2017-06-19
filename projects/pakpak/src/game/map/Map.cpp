#include "pakpak_stdafx.hpp"

namespace game
{
  Map::Map(game::GameData &gamedata)
      : m_gamedata(gamedata), m_points(), m_map(nullptr), m_mapbox(nullptr), m_node(nullptr),
        m_body(nullptr)
  {
  }

  Map::Map(game::GameData &gamedata, std::string const &filename)
      : m_gamedata(gamedata), m_points(), m_map(nullptr), m_mapbox(nullptr), m_node(nullptr),
        m_body(nullptr)
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

#if defined(INDIE_MAP_EDITOR)
    m_filename = filename;
#endif // !INDIE_MAP_EDITOR

    if (fs.is_open() == false)
      {
	throw IOError("Can't open file -> " + filename);
      }

    ss << fs.rdbuf();

    std::string str = ss.str();

    // Store the file content as a vector of uint8
    std::vector<std::uint8_t> content(str.begin(), str.end());

    nope::log::Log(Debug) << "Loading map: '" << filename << '\'' << "("
                          << str.size() << ")";

    // Deserialize it
    MapData data = nope::serialization::from_binary<MapData>(content);

    std::vector<MapData::Point> const &p = data.points;

    m_points.clear();
    m_points.reserve(p.size());
    for (std::size_t i = 0; i < p.size(); ++i)
      {
	m_points.emplace_back(p[i].x, p[i].y, p[i].z);
	nope::log::Log(Debug) << '\t' << nope::serialization::to_json(p[i]);
      }

    std::int32_t pathLen = static_cast<std::int32_t>(filename.length());

    while (pathLen >= 0 && filename[static_cast<std::size_t>(pathLen)] != '/')
      {
	--pathLen;
      }

    // This is now the path to our file
    filename.resize(static_cast<size_t>(pathLen));

    std::string hitbox = filename + "/map_box.mesh";

    filename += "/map.mesh";

    // Load the actual mesh
    std::FILE *meshFile = std::fopen(filename.c_str(), "rb");

    if (meshFile == nullptr)
      {
	throw MapError("Invalid Mesh Data");
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

    // Load the actual mesh
    meshFile = std::fopen(hitbox.c_str(), "rb");

    if (meshFile == nullptr)
      {
	throw std::exception(); // TODO: change exception
      }

    stat(hitbox.c_str(), &fileStat);

    size = static_cast<std::size_t>(fileStat.st_size);

    memstream = new Ogre::MemoryDataStream(hitbox, size, true);

    std::fread(memstream->getPtr(), size, 1, meshFile);
    std::fclose(meshFile);

    ss.str("");
    ss << "MapBoxMesh" << id;

    meshptr = Ogre::MeshManager::getSingleton().createManual(
        ss.str(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::DataStreamPtr stream2(memstream);

    meshSerializer.importMesh(stream2, meshptr.getPointer());

    m_mapbox =
        m_gamedata.sceneMgr()->createEntity(ss.str() + "_ent", ss.str());

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
            vertices, static_cast<unsigned int>(vertexCount), indices,
            static_cast<unsigned int>(indexCount));
    OgreBulletCollisions::TriangleMeshCollisionShape *_shape = shape.get();

    ss.str("");
    ss << "MapRigidBody" << id;

    m_body = m_gamedata.addPhysicEntity(std::move(shape), ss.str());

// body->setDebugDisplayEnabled(false);
// body->showDebugShape(false);

#ifdef DEBUG
    // Small trick to allow debug drawing
    m_body->setShape(m_node, _shape, 0.6f, 0.6f, 0.0f, Ogre::Vector3::ZERO);
#endif
    m_body->setStaticShape(_shape, 0.0f, 0.6f, Ogre::Vector3(0, 0, 0));
    // m_body->setKinematicObject(true);

    m_gamedata.sceneMgr()->setAmbientLight(
        Ogre::ColourValue(0.5f, 0.5f, 0.5f));

    Ogre::Light *l = m_gamedata.sceneMgr()->createLight("MainLight");
    l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
    l->setDirection(Ogre::Vector3(1.0, -1.0, 0.5));

    Ogre::Light *l2 = m_gamedata.sceneMgr()->createLight("MainLight2");
    l2->setPosition(200, 150, -150);

    l2->setCastShadows(false);

    ++id;
  }

  void Map::unload()
  {
    m_points.clear();
  }

#if defined(INDIE_MAP_EDITOR)
  void Map::save() const
  {
    this->saveAs(m_filename);
  }

  void Map::saveAs(std::string const &filename) const
  {
    MapData data;

    nope::log::Log(Debug) << "Saving map as '" << filename << '\'';

    for (Ogre::Vector3 const &p : m_points)
      {
	data.points.emplace_back(p.x, p.y, p.z);
	nope::log::Log(Debug)
	    << '\t' << nope::serialization::to_json(data.points.back());
      }

    nope::log::Log(Debug) << "";

    std::ofstream file(filename.c_str());

    if (file.is_open() == false)
      {
	throw IOError("Failed to open the file '" + filename + "'");
      }

    std::vector<std::uint8_t> v(nope::serialization::to_binary(data));

    nope::log::Log(Debug) << "Save file size: " << v.size();

    file.write(reinterpret_cast<const char *>(v.data()), v.size());
  }
#endif // !INDIE_MAP_EDITOR

  OgreBulletDynamics::RigidBody *Map::rigidBody()
  {
    return (m_body);
  }

  std::vector<Ogre::Vector3> const &Map::getNodes() const
  {
    return m_points;
  }


#if defined(INDIE_MAP_EDITOR)
  void Map::addPoint(Ogre::Vector3 const &pt)
  {
    nope::log::Log(Debug) << "Added point: {" << pt.x << ", " << pt.y << ", "
                          << pt.z << '}';
    m_points.emplace_back(pt);
  }

  void Map::removePoint(std::size_t index)
  {
    m_points.erase(m_points.begin() + index);
  }

  void Map::removeSelectedPoint()
  {
    m_points.erase(m_points.begin() + m_selectedPoint);
  }
#endif // !INDIE_MAP_EDITOR

  Map::MapData::MapData() : points(), elements()
  {
  }

  Map::MapData::Point::Point() : x(0.0), y(0.0), z(0.0)
  {
  }

  Map::MapData::Point::Point(float _x, float _y, float _z)
      : x(_x), y(_y), z(_z)
  {
  }

  Map::MapData::Quaternion::Quaternion() : x(0.0), y(0.0), z(0.0), w(0.0)
  {
  }

  Map::MapData::Quaternion::Quaternion(float _x, float _y, float _z, float _w)
      : x(_x), y(_y), z(_z), w(_w)
  {
  }

  Map::MapData::Element::Element() : pos(), rot(), type(0)
  {
  }
}
