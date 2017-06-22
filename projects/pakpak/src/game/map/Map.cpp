#include "pakpak_stdafx.hpp"

namespace game
{
  Map::Map(game::GameData &gamedata)
      : m_gamedata(gamedata), m_points(), m_checkpoints(), m_map(nullptr),
        m_mapbox(nullptr), m_node(nullptr), m_body(nullptr), m_lights()
#if defined(INDIE_MAP_EDITOR)
        ,
        m_filename(""), m_selectedPoint(0)
#endif // !INDIE_MAP_EDITOR
  {
  }

  Map::Map(game::GameData &gamedata, std::string const &filename)
      : m_gamedata(gamedata), m_points(), m_checkpoints(), m_map(nullptr),
        m_mapbox(nullptr), m_node(nullptr), m_body(nullptr), m_lights()
#if defined(INDIE_MAP_EDITOR)
        ,
        m_filename(""), m_selectedPoint(0)
#endif // !INDIE_MAP_EDITOR
  {
    this->loadFromFile(filename);
  }

  Map::~Map()
  {
    nope::log::Log(Debug) << "DESTROYING MAAAAAAAAAAAAAAAAAAP";
    for (Ogre::Light *l : m_lights)
      {
	m_gamedata.sceneMgr()->destroyLight(l->getName());
      }
    m_lights.clear();
    m_node->removeAndDestroyAllChildren();
    m_gamedata.sceneMgr()->destroySceneNode(m_node->getName());
  }

  void Map::loadFromFile(std::string filename)
  {
    static std::int32_t id_ = 0;
    std::stringstream   ss;
    std::ifstream       fs(filename.c_str());
    ss << id_;
    std::string         id = ss.str();
    ss.str("");

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

    Ogre::MeshPtr meshptr = Ogre::MeshManager::getSingleton().createManual(
        "MapMesh" + id,
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::MeshSerializer meshSerializer;
    Ogre::DataStreamPtr  stream(memstream);

    meshSerializer.importMesh(stream, meshptr.getPointer());

    m_map = m_gamedata.sceneMgr()->createEntity("MapMesh" + id + "_ent",
                                                "MapMesh" + id);

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

    meshptr = Ogre::MeshManager::getSingleton().createManual(
        "MapBoxMesh" + id,
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::DataStreamPtr stream2(memstream);

    meshSerializer.importMesh(stream2, meshptr.getPointer());

    m_mapbox = m_gamedata.sceneMgr()->createEntity("MapBoxMesh" + id + "_ent",
                                                   "MapBoxMesh" + id);

    m_node = m_gamedata.sceneMgr()->getRootSceneNode()->createChildSceneNode(
        "MapNode" + id);
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

    m_body = m_gamedata.addPhysicEntity(std::move(shape), "MapRigidBody" + id);

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

    Ogre::Light *l = m_gamedata.sceneMgr()->createLight("MainLight" + id);
    l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
    l->setDirection(Ogre::Vector3(1.0, -1.0, 0.5));

    Ogre::Light *l2 = m_gamedata.sceneMgr()->createLight("MainLight_" + id);
    l2->setPosition(200, 150, -150);

    l2->setCastShadows(false);
    m_lights.push_back(l);
    m_lights.push_back(l2);

    if (m_points.size() >= 2)
      {
	m_checkpoints.emplace_back(m_points.front(), m_points.back());
      }

    for (std::int32_t i = 1; i < static_cast<std::int32_t>(m_points.size());
         ++i)
      {
	m_checkpoints.emplace_back(m_points[static_cast<std::size_t>(i)],
	                           m_points[static_cast<std::size_t>(i - 1)]);
      }

#if defined(INDIE_MAP_EDITOR)
    m_points.clear();
    m_checkpoints.clear();
#endif // !INDIE_MAP_EDITOR

#if defined(DEBUG)
    for (Ogre::Vector3 const &pt : m_points)
      {
	ss.str("");
	ss << "Checkpoint" << id_;
	Ogre::Entity *ent = m_map->clone(ss.str());
	// m_gamedata.sceneMgr()->createEntity(
	// ss.str(), Ogre::SceneManager::PT_CUBE);

	ss.str("");
	ss << "CheckpointNode" << id_;
	Ogre::SceneNode *node =
	    m_gamedata.sceneMgr()->getRootSceneNode()->createChildSceneNode(
	        ss.str(), pt);
	node->attachObject(ent);
	node->setScale(static_cast<Ogre::Real>(0.01),
	               static_cast<Ogre::Real>(0.01),
	               static_cast<Ogre::Real>(0.01));
	++id_;
      }
#endif // !DEBUG

    ++id_;
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

    // file << nope::serialization::to_json(data);
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
    m_points.push_back(pt);
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

  std::vector<std::int32_t> Map::getPlayerOrder()
  {
    if (m_checkpoints.size() < 2)
      return (std::vector<std::int32_t>());

    for (std::size_t i = 0; i < m_gamedata.getPlayerNb(); ++i)
      {
	std::int32_t chkpt = m_gamedata[i].getCheckPoint() + 1;

	chkpt %= static_cast<std::int32_t>(m_checkpoints.size());

	if (m_checkpoints[static_cast<std::size_t>(chkpt)].hasPassed(
	        m_gamedata[i].car().position()))
	  {
	    nope::log::Log(Debug) << "Checkpoint done!";

	    m_gamedata[i].nextCheckPoint();
	    m_checkpoints[static_cast<std::size_t>(chkpt)].addCheck(
	        static_cast<std::int32_t>(i));
	  }
      }

    using info_t = std::pair<std::int32_t, std::int32_t>;

    std::vector<std::int32_t> res;
    std::vector<info_t>       curPos;

    for (std::size_t i = 0; i < m_gamedata.getPlayerNb(); ++i)
      {
	curPos.emplace_back(i, m_gamedata[i].getCheckPoint());
      }

    std::sort(curPos.begin(), curPos.end(),
              [](info_t const &left, info_t const &right) {
                return (left.second > right.second);
              });

    for (info_t const &info : curPos)
      {
	res.push_back(info.first);
      }

    return (res);
  }

  Map::MapData::MapData() : points(), elements()
  {
  }

  Map::MapData::Point::Point() : x(0.0), y(0.0), z(0.0)
  {
  }

  Map::MapData::Point::Point(Point &&that) : x(that.x), y(that.y), z(that.z)
  {
  }

  Map::MapData::Point::Point(std::int32_t _x, std::int32_t _y, std::int32_t _z)
      : x(_x), y(_y), z(_z)
  {
  }

  Map::MapData::Point &Map::MapData::Point::operator=(Point &&that)
  {
    if (this == &that)
      return (*this);
    x = that.x;
    y = that.y;
    z = that.z;
    return (*this);
  }

  Map::MapData::Quaternion::Quaternion(Map::MapData::Quaternion &&that)
      : x(that.x), y(that.y), z(that.z), w(that.w)
  {
  }

  Map::MapData::Quaternion::Quaternion() : x(0.0), y(0.0), z(0.0), w(0.0)
  {
  }

  Map::MapData::Quaternion::Quaternion(std::int32_t _x, std::int32_t _y,
                                       std::int32_t _z, std::int32_t _w)
      : x(_x), y(_y), z(_z), w(_w)
  {
  }

  Map::MapData::Quaternion &Map::MapData::Quaternion::
                            operator=(Map::MapData::Quaternion &&that)
  {
    if (this == &that)
      return (*this);
    x = that.x;
    y = that.y;
    z = that.z;
    w = that.w;
    return (*this);
  }

  Map::MapData::Element::Element() : pos(), rot(), type(0)
  {
  }

  Map::MapData::Element::Element(Element &&that)
      : pos(std::move(that.pos)), rot(std::move(that.rot)), type(that.type)
  {
  }

  Map::MapData::Element &Map::MapData::Element::
                         operator=(Map::MapData::Element &&that)
  {
    if (this == &that)
      return (*this);
    pos = std::move(that.pos);
    rot = std::move(that.rot);
    type = that.type;
    return (*this);
  }

  std::int32_t Map::getNbCheckPoint() const
  {
    return (static_cast<int32_t>(m_checkpoints.size()));
  }

  std::vector<CheckPoint> const &Map::getCheckPoints() const
  {
    return m_checkpoints;
  }
}
