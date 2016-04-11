#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>
#include <string>

using namespace Ogre;

Camera* mCamera;

#define RADIAN(x) x * (3.141592 / 180.0f)

class ESCListener : public FrameListener {
  OIS::Keyboard *mKeyboard;

public:
  ESCListener(OIS::Keyboard *keyboard) : mKeyboard(keyboard) {}
  bool frameStarted(const FrameEvent &evt)
  {
	  // 카메라 움직임 관련한 내용 구현
	  // 여기다 Setposition, lookat 써라
	  static float rotAngle = 0.0f;
	  rotAngle += 0.5f;

	  mCamera->setPosition(cos(RADIAN(rotAngle)) * 500.0f, 100.0f, sin(RADIAN(rotAngle)) * 500.0f);
	  mCamera->lookAt(0, 100, 0);

    mKeyboard->capture();
    return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
  }
};

class LectureApp {

  Root* mRoot;
  RenderWindow* mWindow;
  SceneManager* mSceneMgr;

  Viewport* mViewport;
  OIS::Keyboard* mKeyboard;
  OIS::InputManager *mInputManager;
  ESCListener* mESCListener;

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
    mWindow = mRoot->initialise(true, "Professor & Ninja");

    // ESC key를 눌렀을 경우, 오우거 메인 렌더링 루프의 탈출을 처리
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));

    mESCListener = new ESCListener(mKeyboard);
    mRoot->addFrameListener(mESCListener);

    mSceneMgr = mRoot->createSceneManager(ST_GENERIC);

    mCamera = mSceneMgr->createCamera("camera");

    mCamera->setPosition(0.0f, 100.0f, 500.0f);
    mCamera->lookAt(0.0f, 100.0f, 0.0f);

    mCamera->setNearClipDistance(5.0f);
    mCamera->setNearClipDistance(5.0f);

    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.0f,0.0f,0.5f));
//    mViewport->setBackgroundColour(ColourValue(1.0f,1.0f,1.0f));
    mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
	//mCamera->SetTra

    ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // 좌표축 표시
    Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
    mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode",Ogre::Vector3(0,0,0))->attachObject(mAxesEntity);
    mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

    _drawGridPlane();

    // fill here --------------------------------------------------------------------------------------------------
	Entity* CenterEntity = mSceneMgr->createEntity("Center", SceneManager::PrefabType::PT_SPHERE);
	
	Entity* entity2 = mSceneMgr->createEntity("Ninja", "ninja.mesh");

	SceneNode * centerNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("CenterEntity");

	for (int i = 0; i < 12; ++i)
	{
		std::string pro = "Professor";
		char index = i;
		Entity* entity1 = mSceneMgr->createEntity(pro + index, "DustinBody.mesh");

		SceneNode * node1 = centerNode->
			createChildSceneNode(pro + index, Vector3(cos(RADIAN(i * 30)) * 200.0f, 0.0f, sin(RADIAN(i * 30)) * 200.0f));
		node1->attachObject(entity1);
	}



	// ------------------------------------------------------------------------------------------------------------

    mRoot->startRendering();

    mInputManager->destroyInputObject(mKeyboard);
    OIS::InputManager::destroyInputSystem(mInputManager);

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
    for(int i=0; i<21; i++)
    {
      gridPlane->position(-500, 0, 500-i*50);
      gridPlane->position(500, 0, 500-i*50);

      gridPlane->position(-500+i*50, 0, 500);
      gridPlane->position(-500+i*50, 0, -500);
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

