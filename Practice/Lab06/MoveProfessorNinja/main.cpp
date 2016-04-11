#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#include <vector>

using namespace Ogre;
using namespace std;

SceneManager* mSceneMgr;
class KeyboardListener : public FrameListener {
	OIS::Keyboard *mKeyboard;
	Camera* mCamera;
public:
	KeyboardListener(OIS::Keyboard *keyboard) : mKeyboard(keyboard) 
	{
		mCamera = mSceneMgr->getCamera("main");
	}
  bool frameStarted(const FrameEvent &evt)
  {
    mKeyboard->capture();
	
	if (mKeyboard->isKeyDown(OIS::KC_1))
	{
		mCamera->setPosition(500, 100, 0);
		mCamera->lookAt(0.0f, 100.0f, 0.0f);
	}
	if (mKeyboard->isKeyDown(OIS::KC_2))
	{
		mCamera->setPosition(-500, 100, 0);
		mCamera->lookAt(0.0f, 100.0f, 0.0f);
	}
	if (mKeyboard->isKeyDown(OIS::KC_3))
	{
		mCamera->setPosition(0, 100, 500);
		mCamera->lookAt(0.0f, 100.0f, 0.0f);
	}
	if (mKeyboard->isKeyDown(OIS::KC_4))
	{
		mCamera->setPosition(0, 100, -500);
		mCamera->lookAt(0.0f, 100.0f, 0.0f);
	}
	return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
  }
};


class MainListener : public FrameListener {
  OIS::Keyboard *mKeyboard;
  Root* mRoot;
  SceneNode *mProfessorNode, *mNinjaNode;
  std::vector<SceneNode*> mNodeArray;
  std::vector<float> mSpeedArray;
  std::vector<float> mDirArray;



public:
  MainListener(Root* root, OIS::Keyboard *keyboard) : mKeyboard(keyboard), mRoot(root) 
  {
    // Fill Here --------------------------------------------------------------------------
	  for (int i = 0; i < 50; ++i)
	  {
		  char name[20];
		  sprintf(name, "Fish%d", i);
		  mNodeArray.push_back(mRoot->getSceneManager("main")->getSceneNode(name));
		  mSpeedArray.push_back(rand() % 10 + 10.0f);
		  mDirArray.push_back(((rand() % 2 == 0) ? -1 : 1));
	  }
    // ------------------------------------------------------------------------------------
  }

  bool frameStarted(const FrameEvent &evt)
  {
	  for (int i = 0; i < mNodeArray.size(); ++i)
	  {
		  mNodeArray[i]->translate(mSpeedArray[i] * mDirArray[i] * evt.timeSinceLastFrame, 0, 0);
	  }
    // Fill Here ------------------------------------------------------------------------------
	  //static float professorVelocity = -50.0f;
	  //if (mKeyboard->isKeyDown(OIS::KC_LEFT))
		 // mProfessorNode->translate(-professorVelocity * evt.timeSinceLastFrame, 0, 0);
	  //else if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
		 // mProfessorNode->translate(professorVelocity * evt.timeSinceLastFrame, 0, 0);

	//  mProfessorNode->translate(professorVelocity * evt.timeSinceLastFrame, 0, 0);
	//  mProfessorNode->setPosition(mProfessorNode->getPosition() + professorVelocity * evt.timeSinceLastFrame);

	  //static float ninjaVelocity = 100.0f;
	  //if (mNinjaNode->getPosition().x < -400.0f || mNinjaNode->getPosition().x > 400.0f)
		 // ninjaVelocity *= -1;
	  //mNinjaNode->translate(ninjaVelocity * evt.timeSinceLastFrame, 0, 0);
    // -----------------------------------------------------------------------------------------
    return true;
  }

};

class LectureApp {

  Root* mRoot;
  RenderWindow* mWindow;

  Camera* mCamera;
  Viewport* mViewport;
  OIS::Keyboard* mKeyboard;
  OIS::InputManager *mInputManager;

  MainListener* mMainListener;
  KeyboardListener* mKeyListener;

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

    mWindow = mRoot->initialise(true, "Moving Professor & Ninja : Copyleft by Dae-Hyun Lee");


    // ESC key를 눌렀을 경우, 오우거 메인 렌더링 루프의 탈출을 처리
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));


    // Fill Here --------------------------------------------------------------
	mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");
	mCamera = mSceneMgr->createCamera("main");


    // ------------------------------------------------------------------------

    
    mCamera->setPosition(0.0f, 100.0f, 500.0f);
    mCamera->lookAt(0.0f, 100.0f, 0.0f);

    mCamera->setNearClipDistance(5.0f);

    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.0f,0.0f,0.5f));
    mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

	ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
    ResourceGroupManager::getSingleton().addResourceLocation("fish.zip", "Zip");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // 좌표축 표시
    Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
    mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode",Ogre::Vector3(0,0,0))->attachObject(mAxesEntity);
    mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

    _drawGridPlane();


    Entity* entity1 = mSceneMgr->createEntity("Fish", "fish.mesh");
   // Entity* entity2 = mSceneMgr->createEntity("Ninja", "ninja.mesh");

	for (int i = 0; i < 50; ++i)
	{
		char name[20];
		sprintf(name, "Fish%d", i);
		Entity* entity1 = mSceneMgr->createEntity(name, "fish.mesh");
		SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, Vector3(rand() % 400 - 200, 0.0f, rand() % 400 - 200));
		node1->attachObject(entity1);
		node1->scale(10, 10, 10);
	}
  //  SceneNode* node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Ninja", Vector3(200.0f, 0.0f, -200.0f));
   // node2->attachObject(entity2);


    // Fill Here ----------------------------------------------
	mKeyListener = new KeyboardListener(mKeyboard);
	mRoot->addFrameListener(mKeyListener);

	mMainListener = new MainListener(mRoot, mKeyboard);
	mRoot->addFrameListener(mMainListener);


    // --------------------------------------------------------

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
      gridPlane->position(-500.0f, 0.0f, 500.0f-i*50);
      gridPlane->position(500.0f, 0.0f, 500.0f-i*50);

      gridPlane->position(-500.f+i*50, 0.f, 500.0f);
      gridPlane->position(-500.f+i*50, 0.f, -500.f);
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

