#include "pakpak_stdafx.hpp"
#include "AppLauncher.hpp"

namespace core
{
  AppLauncher::AppLauncher()
      : m_root(nullptr), m_window(nullptr), m_inputListener(nullptr),
        m_contexts(), m_currentContext(nullptr), m_gameState(GameState::None),
        m_settings()
  {
  }

  AppLauncher::~AppLauncher()
  {
  }

  bool AppLauncher::start()
  {

// TODO : Create .cfg
// Create the Root

#ifdef DEBUG
#ifdef _WIN32
    if (m_root)
      delete m_root;
    m_root = new Ogre::Root("../indie_resource/conf/windows/plugins_d.cfg",
                            "../indie_resource/conf/windows/ogre_d.cfg",
                            "Ogre.log");
#else
    if (m_root)
      delete m_root;
    m_root =
        new Ogre::Root("../indie_resource/conf/linux/plugins_d.cfg",
                       "../indie_resource/conf/linux/ogre_d.cfg", "Ogre.log");
#endif
#else
#ifdef _WIN32
    if (m_root)
      delete m_root;
    m_root =
        new Ogre::Root("../indie_resource/conf/windows/plugins.cfg",
                       "../indie_resource/conf/windows/ogre.cfg", "Ogre.log");
#else
    if (m_root)
      delete m_root;
    m_root =
        new Ogre::Root("../indie_resource/conf/linux/plugins.cfg",
                       "../indie_resource/conf/linux/ogre.cfg", "Ogre.log");
#endif
#endif // !DEBUG

    // Load Ressource config file
    Ogre::ConfigFile configFile;
#ifdef DEBUG
    configFile.load("../indie_resource/conf/resources_d.cfg");
#else
    configFile.load("../indie_resource/conf/resources.cfg");
#endif // !DEBUG

    // Load all the Ressources
    Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
    Ogre::String                      secName, typeName, archName;

    while (seci.hasMoreElements())
      {
	secName = seci.peekNextKey();
	Ogre::ConfigFile::SettingsMultiMap *         settings = seci.getNext();
	Ogre::ConfigFile::SettingsMultiMap::iterator i;
	for (i = settings->begin(); i != settings->end(); ++i)
	  {
	    typeName = i->first;
	    archName = i->second;
	    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
	        archName, typeName, secName);
	  }
      }

    // Check Config
    if (!(m_root->restoreConfig() || m_root->showConfigDialog()))
      {
	return false;
      }

    // Render System
    // TODO: Render System dynamiques
    Ogre::RenderSystem *rs =
        m_root->getRenderSystemByName("OpenGL Rendering Subsystem");
    // Pour DirectX : "Direct3D9 Rendering Subsystem
    m_root->setRenderSystem(rs);
    rs->setConfigOption("Full Screen", "No");
    rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
    rs->setConfigOption("VSync", "Yes");

    // Render Window
    m_window = m_root->initialise(true, "Pak Pak Studio");

    // Initialize Ressources
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    m_window->removeAllViewports();

    //// Create the Scene Manager
    // m_sceneMgr =
    //    m_root->createSceneManager("DefaultSceneManager", "Mon Scene
    //    Manager");

    //// Set A light
    // m_sceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

    //// Create Camera
    // m_camera =
    //    std::unique_ptr<Ogre::Camera>(m_sceneMgr->createCamera("PlayerCam"));
    // m_camera->setPosition(Ogre::Vector3(0, 0, 100));
    // m_camera->lookAt(Ogre::Vector3(0, 0, 0));
    // m_camera->setNearClipDistance(5);

    //// Set View Port
    // Ogre::Viewport *vp = m_window->addViewport(m_camera.get());
    // vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    // m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) /
    //                         Ogre::Real(vp->getActualHeight()));

    //// Create Entity
    // Ogre::Entity *ent = m_sceneMgr->createEntity("pinguin", "penguin.mesh");

    //// Attach the mesh to the scene
    // Ogre::SceneNode *node =
    //    m_sceneMgr->getRootSceneNode()->createChildSceneNode();
    // node->attachObject(ent);

    createFrameListener();

    // Splash context
    m_contexts[static_cast<std::size_t>(GameState::Splash)] =
        std::make_unique<splash::ContextSplash>(m_window, m_inputListener);

    // Menu context
    m_contexts[static_cast<std::size_t>(GameState::Menu)] =
        std::make_unique<menu::ContextMenu>(m_window, m_inputListener,
                                            m_settings);

    // Game context
    m_contexts[static_cast<std::size_t>(GameState::InGame)] =
        std::make_unique<game::ContextGame>(m_window, m_inputListener,
                                            m_settings);

    m_currentContext =
        m_contexts[static_cast<std::size_t>(GameState::Splash)].get();

    m_currentContext->enable();

    // Render Loop
    while (true)
      {
	GameState state;

	Ogre::WindowEventUtilities::messagePump();
	if (m_window->isClosed())
	  return false;

	// Update Window Size
	CEGUI::Size<float> sizef;
	sizef.d_height = m_window->getHeight();
	sizef.d_width = m_window->getWidth();
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(sizef);

	// Update game logic
	state = m_currentContext->update();

	if (state == GameState::Quit)
	  {
	    m_currentContext->disable();
	    break;
	  }

	// Display
	m_currentContext->display();

	// Update the context if needed
	if (state != m_gameState)
	  {
	    m_gameState = state;
	    m_currentContext->disable();
	    m_currentContext =
	        m_contexts[static_cast<std::size_t>(state)].get();
	    m_currentContext->enable();
	  }

	if (!m_root->renderOneFrame())
	  return false;
      }

    return true;
  }

  void AppLauncher::createFrameListener()
  {
    // Create and add a Framelistener
    m_inputListener = new InputListener(m_window);
    m_root->addFrameListener(m_inputListener);
  }
}
