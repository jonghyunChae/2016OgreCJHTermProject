#include "IngameState.h"
#include "DynamicObject.h"
#include "WarriorPlayerState.h"
//#include "common.h"
//#include "ObjectList.h"
//#include ""

using namespace Ogre;
InGameState  InGameState::mInGameState;

void InGameState::enter()
{
	mContinue = true;
	mRoot = Root::getSingletonPtr();
	mRoot->getAutoCreatedWindow()->resetStatistics();

	mSceneMgr = mRoot->getSceneManager("main");
	mCamera = mSceneMgr->getCamera("main");
	mCamera->setPosition(Ogre::Vector3::ZERO);

	_buildObjects();
	_drawGridPlane();
	_setLights();
	_drawGroundPlane();
	_setResources();
}

void InGameState::exit()
{
	mSceneMgr->clearScene();
	//mInformationOverlay->hide();

	if (mpPlayer) delete mpPlayer;
	for (auto & monster : mpMonsters)
	{
		delete monster;
	}
	mpMonsters.clear();
}

void InGameState::pause()
{
}

void InGameState::resume()
{
}

bool InGameState::frameStarted(GameManager * game, const Ogre::FrameEvent & evt)
{
	const float frameTime = evt.timeSinceLastFrame;
	mpPlayer->update(frameTime);

	for (auto & monster : mpMonsters)
		monster->update(frameTime);

	return true;
}

bool InGameState::frameEnded(GameManager * game, const Ogre::FrameEvent & evt)
{
	return mContinue;
}

bool InGameState::mouseMoved(GameManager * game, const OIS::MouseEvent & e)
{
	mpPlayer->mouseMoved(e);
	return true;
}

bool InGameState::mousePressed(GameManager * game, const OIS::MouseEvent & e, OIS::MouseButtonID id)
{
	if (e.state.buttonDown(OIS::MB_Right))
	{
		CWarriorPlayer* player = static_cast<CWarriorPlayer*>(mpPlayer);
		auto & monArray = player->getTargetMonsterArray();
		monArray.clear();

		for (auto & monster : mpMonsters)
		{
			if (false == monster->getStatus().isDeath())
				monArray.push_back(monster);
		}
		player->getStateMachine()->ChangeState(&CWarriorAttackState::getInstance());
	}

	mpPlayer->setCanRotate(true);
	return true;
}

bool InGameState::mouseReleased(GameManager * game, const OIS::MouseEvent & e, OIS::MouseButtonID id)
{
	mpPlayer->setCanRotate(false);
	return true;
}

bool InGameState::keyPressed(GameManager * game, const OIS::KeyEvent & e)
{
	switch (e.key)
	{
	case OIS::KC_LEFT:  mpPlayer->move(-Vector3::UNIT_X); break;
	case OIS::KC_RIGHT: mpPlayer->move(Vector3::UNIT_X);  break;
	case OIS::KC_UP:    mpPlayer->move(-Vector3::UNIT_Z); break;
	case OIS::KC_DOWN:  mpPlayer->move(Vector3::UNIT_Z);  break;

	case OIS::KC_ESCAPE:
		mContinue = false;
		break;
	}
	return true;
}

bool InGameState::keyReleased(GameManager * game, const OIS::KeyEvent & e)
{
	switch (e.key)
	{
	case OIS::KC_LEFT:  mpPlayer->move(Vector3::UNIT_X); break;
	case OIS::KC_RIGHT: mpPlayer->move(-Vector3::UNIT_X);  break;
	case OIS::KC_UP:    mpPlayer->move(Vector3::UNIT_Z); break;
	case OIS::KC_DOWN:  mpPlayer->move(-Vector3::UNIT_Z);  break;

	}
	return true;
}

void InGameState::_buildObjects(void)
{
	mpPlayer = new CWarriorPlayer();
	mpPlayer->buildObject(mRoot, mSceneMgr, "Warrior");
	mpPlayer->setAnimation("Idle");

	char name[56];
	for (int i = 0; i < 10; ++i)
	{
		sprintf(name, "Zombie%d", i);

		CMonster * pMonster = new CWarZombie();
		pMonster->buildObject(mRoot, mSceneMgr, name, i);
		pMonster->setAnimation(CDynamicObject::eIDLE);
		pMonster->getNode()->setPosition(Vector3(rand() % 400 - 200, 0, rand() % 400 - 200));
		mpMonsters.push_back(pMonster);
	}
}

void InGameState::_drawGridPlane(void)
{
	Ogre::ManualObject* gridPlane = mSceneMgr->createManualObject("GridPlane");
	Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

	Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
	gridPlaneMaterial->setReceiveShadows(false);
	gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

	gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	for (int i = 0; i < 41; i++)
	{
		gridPlane->position(-2000.0f, 1.0f, 2000.0f - i * 100);
		gridPlane->position(2000.0f, 1.0f, 2000.0f - i * 100);

		gridPlane->position(-2000.f + i * 100, 1.f, 2000.0f);
		gridPlane->position(-2000.f + i * 100, 1.f, -2000.f);
	}

	gridPlane->end();

	gridPlaneNode->attachObject(gridPlane);
}

void InGameState::_setLights(void)
{
	mSceneMgr->setAmbientLight(ColourValue(0.1f, 0.1f, 0.1f));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	
	Light* light;

	light = mSceneMgr->createLight("DirectLight");
	light->setType(Light::LT_DIRECTIONAL);
	light->setDirection(Vector3(1, -2.0f, -1).normalisedCopy());
	light->setDiffuseColour(ColourValue(0.4f, 0.1f, 0.1f));
	light->setVisible(true);
	
	light = mSceneMgr->createLight("PlayerLight");
#if 1
	light->setType(Light::LT_SPOTLIGHT);
	light->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
	light->setPosition(Vector3(0, 100, 0));
	light->setDiffuseColour(ColourValue(2.f, 2.f, 2.f));
	light->setSpotlightRange(Degree(20), Degree(80));
	light->setVisible(true);
#endif
#if 0
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(0, 100, 0));
	light->setDiffuseColour(ColourValue(1.f, 1.f, 1.f));
	light->setVisible(true);
#endif
	SceneNode * lightNode = 
		mpPlayer->getRootNode()->createChildSceneNode("PlayerLight", Vector3(0, 100, 0));

	lightNode->attachObject(light);
}

void InGameState::_drawGroundPlane(void)
{
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		5000, 5000,
		1, 1,
		true, 1, 100, 100,
		Vector3::NEGATIVE_UNIT_Z
		);

	Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("Terrain");
	groundEntity->setCastShadows(false);
	Ogre::MaterialManager::getSingleton().getByName("Terrain")->setReceiveShadows(true);
//	groundEntity->getMateri setReceiveShadows(true);
}

void InGameState::_setResources(void)
{
	mSceneMgr->setSkyBox(true, "3D-Diggers/SkyBox", 10000);
#if _DEBUG
	mSceneMgr->setShowDebugShadows(true);
#endif
}
