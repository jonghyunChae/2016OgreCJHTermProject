#include "ObjectList.h"

class UpdateListener : public FrameListener
{
	CPlayer * mPlayer;

public:
	UpdateListener(CPlayer * pPlayer) : mPlayer(pPlayer)
	{
	}

	virtual ~UpdateListener()
	{
		delete mPlayer;
	}

	bool frameStarted(const FrameEvent &evt)
	{
		mPlayer->update(evt.timeSinceLastFrame);
		return true;
	}
};

class InputController : public FrameListener, 
  public OIS::KeyListener, 
  public OIS::MouseListener
{

public:
  InputController(Root* root, OIS::Keyboard *keyboard, OIS::Mouse *mouse) : mRoot(root), mKeyboard(keyboard), mMouse(mouse)
  {
    mProfessorNode = mRoot->getSceneManager("main")->getSceneNode("Professor");
    mCamera = mRoot->getSceneManager("main")->getCamera("main");

    mContinue = true;

    keyboard->setEventCallback(this);
    mouse->setEventCallback(this);
  }


  bool frameStarted(const FrameEvent &evt)
  {
    mKeyboard->capture();
    mMouse->capture();

	if (mKeyboard->isKeyDown(OIS::KC_LEFT)) mProfessorNode->translate(-1, 0, 0);
	if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) mProfessorNode->translate(1, 0, 0);
	if (mKeyboard->isKeyDown(OIS::KC_UP)) mProfessorNode->translate(0, 0, -1);
	if (mKeyboard->isKeyDown(OIS::KC_DOWN)) mProfessorNode->translate(0, 0, 1);

	if (mKeyboard->isKeyDown(OIS::KC_A)) mProfessorNode->yaw(Degree(-1));
	if (mKeyboard->isKeyDown(OIS::KC_D)) mProfessorNode->yaw(Degree(1));


	return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
  }

  // Key Linstener Interface Implementation
  bool keyPressed( const OIS::KeyEvent &evt )
  {
	  return true;
  }

  bool keyReleased( const OIS::KeyEvent &evt )
  {
	  return true;
  }


  // Mouse Listener Interface Implementation

  bool mouseMoved( const OIS::MouseEvent &evt )
  {
    if (evt.state.buttonDown(OIS::MB_Right)) 
    {
      mCamera->yaw(Degree(-evt.state.X.rel));
      mCamera->pitch(Degree(-evt.state.Y.rel));
    }

    mCamera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.1f));

    return true;
  }

  bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
  {
    return true;
  }

  bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
  {
    return true;
  }

private:
  bool			 mContinue;
  Ogre::Root*	 mRoot;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse*	 mMouse;
  Camera*		 mCamera;
  SceneNode*	 mProfessorNode;
};


class LectureApp {

  Root*          mRoot;
  RenderWindow*  mWindow;
  SceneManager*  mSceneMgr;
  Camera*		 mCamera;
  Viewport*      mViewport;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse*    mMouse;

  OIS::InputManager *mInputManager;

public:

  LectureApp() {}
  ~LectureApp() {}

  void go(void)
  {
    // OGRE의 메인 루트 오브젝트 생성
#if !defined(_DEBUG)
    mRoot = new Root("plugins.cfg", "ogre.cfg", "ogre.log");
#else
    mRoot = new Root("plugins_d.cfg", "ogre.cfg", "ogre.log");
#endif


    // 초기 시작의 컨피규레이션 설정 - ogre.cfg 이용
    if (!mRoot->restoreConfig()) {
      if (!mRoot->showConfigDialog()) return;
    }

    mWindow = mRoot->initialise(true, CLIENT_DESCRIPTION);

    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");

    ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // 좌표축 표시
    Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
    mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode",Ogre::Vector3(0,0,0))->attachObject(mAxesEntity);
    mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

    _drawGridPlane();

	CPlayer * pPlayer = new CPlayer();
	pPlayer->buildObject(mRoot, mSceneMgr);

	mCamera = pPlayer->getCamera(); 
	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.5f));
	mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

	UpdateListener* frameUpdate = new UpdateListener(pPlayer);
	mRoot->addFrameListener(frameUpdate);

    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>( mInputManager->createInputObject(OIS::OISMouse, true));

    InputController* inputController = new InputController(mRoot, mKeyboard, mMouse);
    mRoot->addFrameListener(inputController);

    mRoot->startRendering();

    mInputManager->destroyInputObject(mKeyboard);
    mInputManager->destroyInputObject(mMouse);
    OIS::InputManager::destroyInputSystem(mInputManager);

    delete inputController;
	delete frameUpdate;

    delete mRoot;
  }

private:
  void _drawGridPlane(void)
  {
    Ogre::ManualObject* gridPlane =  mSceneMgr->createManualObject("GridPlane"); 
    Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode"); 

    Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial","General"); 
    gridPlaneMaterial->setReceiveShadows(false); 
    gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,0); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,1); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,1); 

    gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
    for(int i=0; i<41; i++)
    {
      gridPlane->position(-2000.0f, 0.0f, 2000.0f-i*100);
      gridPlane->position(2000.0f, 0.0f, 2000.0f-i*100);

      gridPlane->position(-2000.f+i*100, 0.f, 2000.0f);
      gridPlane->position(-2000.f+i*100, 0.f, -2000.f);
    }

    gridPlane->end(); 

    gridPlaneNode->attachObject(gridPlane);
  }
};


#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
    LectureApp app;

    try {

      app.go();

    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occured: " <<
        e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
  }

#ifdef __cplusplus
}
#endif

