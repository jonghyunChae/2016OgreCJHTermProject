#pragma once

#ifndef _IN_GAME_H
#define _IN_GAME_H

#include "GameState.h"
#include "ObjectList.h"
//class CPlayer;

class InGameState : public GameState
{
public:
	void enter();
	void exit();
	void pause();
	void resume();

	bool frameStarted(GameManager* game, const Ogre::FrameEvent& evt);
	bool frameEnded(GameManager* game, const Ogre::FrameEvent& evt);

	bool mouseMoved(GameManager* game, const OIS::MouseEvent &e);
	bool mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool keyPressed(GameManager* game, const OIS::KeyEvent &e);
	bool keyReleased(GameManager* game, const OIS::KeyEvent &e);

	static InGameState* getInstance() { return &mInGameState; }

private:
	//InGameState() {}
	~InGameState() {}

	static InGameState mInGameState;

	bool mContinue;

	void _drawGridPlane(void);
	void _setLights(void);


private:
	CPlayer * mpPlayer;

	Ogre::Root *mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	//Ogre::Light *mLightP, *mLightD, *mLightS;

	Ogre::SceneNode* mCharacterRoot;
	Ogre::SceneNode* mCharacterYaw;
	Ogre::SceneNode* mCameraHolder;
	Ogre::SceneNode* mCameraYaw;
	Ogre::SceneNode* mCameraPitch;

	Ogre::Entity* mCharacterEntity;

	Ogre::AnimationState* mAnimationState;

	//Ogre::Overlay*           mInformationOverlay;
};


#endif