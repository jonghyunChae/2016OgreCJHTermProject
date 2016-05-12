#include "IngameState.h"
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

	_drawGridPlane();
	_setLights();
	//_drawGroundPlane();

	//mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
	//mInformationOverlay->show();


	mpPlayer = new CWarriorPlayer();
	mpPlayer->buildObject(mRoot, mSceneMgr, "Professor");
	mpPlayer->setAnimation("Idle");


	//mAnimationState = mCharacterEntity->getAnimationState("Run");
	//mAnimationState->setLoop(true);
	//mAnimationState->setEnabled(true);
}

void InGameState::exit()
{
	mSceneMgr->clearScene();
	//mInformationOverlay->hide();

	if (mpPlayer) delete mpPlayer;
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
	return true;
}

bool InGameState::mouseReleased(GameManager * game, const OIS::MouseEvent & e, OIS::MouseButtonID id)
{
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
		gridPlane->position(-2000.0f, 0.0f, 2000.0f - i * 100);
		gridPlane->position(2000.0f, 0.0f, 2000.0f - i * 100);

		gridPlane->position(-2000.f + i * 100, 0.f, 2000.0f);
		gridPlane->position(-2000.f + i * 100, 0.f, -2000.f);
	}

	gridPlane->end();

	gridPlaneNode->attachObject(gridPlane);
}

void InGameState::_setLights(void)
{
	mSceneMgr->setAmbientLight(ColourValue(10.0f, 10.0f, 10.0f));
}
