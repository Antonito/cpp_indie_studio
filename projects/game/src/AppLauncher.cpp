#include "AppLauncher.h"

AppLauncher::AppLauncher()
    : mRoot(nullptr), mWindow(nullptr), mSceneMgr(nullptr), mCamera(nullptr)
{
}

AppLauncher::~AppLauncher()

{
}

bool AppLauncher::start()

{

  // Create the Root
  mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

  // Load Ressource config file
  Ogre::ConfigFile configFile;
  configFile.load("resources.cfg");

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
  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    {
      return false;
    }

  // Render System
  // TODO: Render System dynamiques
  Ogre::RenderSystem *rs = mRoot->getRenderSystemByName(
      "OpenGL Rendering Subsystem"); // Pour DirectX : "Direct3D9 Rendering
                                     // Subsystem
  mRoot->setRenderSystem(rs);
  rs->setConfigOption("Full Screen", "No");
  rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
  rs->setConfigOption("VSync", "Yes");

  // Render Window
  mWindow = mRoot->initialise(true, "Pak Pak Studio");

  // Initialize Ressources
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  // Create the Scene Manager
  mSceneMgr =
      mRoot->createSceneManager("DefaultSceneManager", "Mon Scene Manager");

  // Set A light
  mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

  // Create Camera
  mCamera = mSceneMgr->createCamera("PlayerCam");
  mCamera->setPosition(Ogre::Vector3(0, 0, 100));
  mCamera->lookAt(Ogre::Vector3(0, 0, 0));
  mCamera->setNearClipDistance(5);

  // Set View Port
  Ogre::Viewport *vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) /
                          Ogre::Real(vp->getActualHeight()));

  // Create Entity
  Ogre::Entity *ent = mSceneMgr->createEntity("pinguin", "penguin.mesh");

  // Attach the mesh to the scene
  Ogre::SceneNode *node =
      mSceneMgr->getRootSceneNode()->createChildSceneNode();
  node->attachObject(ent);

  // Render Loop
  while (true)
    {
      Ogre::WindowEventUtilities::messagePump();
      if (mWindow->isClosed())
	return false;
      if (!mRoot->renderOneFrame())
	return false;
    }

  return true;
}