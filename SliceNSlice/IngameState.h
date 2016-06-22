#pragma once

#ifndef _IN_GAME_H
#define _IN_GAME_H

#include "GameState.h"
#include "ObjectList.h"
//class CPlayer;

class InGameState : public GameState
{
public:
	void enter(GameManager* game);
	void exit(GameManager* game);
	void pause(GameManager* game);
	void resume(GameManager* game);

	bool frameStarted(GameManager* game, const Ogre::FrameEvent& evt);
	bool frameEnded(GameManager* game, const Ogre::FrameEvent& evt);

	bool mouseMoved(GameManager* game, const OIS::MouseEvent &e);
	bool mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool keyPressed(GameManager* game, const OIS::KeyEvent &e);
	bool keyReleased(GameManager* game, const OIS::KeyEvent &e);

	static InGameState* getInstance() { return &mInGameState; }

	CPlayer * getPlayer() { return mpPlayer; }

	void msgDeathLocations(std::vector<Vector3>& vectorList);
	void msgGameOver();

private:
	InGameState() { mTextOverlay = nullptr; }
	~InGameState() {}

	static InGameState mInGameState;

	bool mContinue;

	void _buildObjects(void);
	void _drawGridPlane(void);
	void _setLights(void);
	void _drawGroundPlane(void);
	void _setResources(void);
	void _buildUI(void);

private:
	CPlayer * mpPlayer;
	std::vector<CMonster*> mpMonsters;

#define ABSORB_NUM 1000
	std::vector<AbsorbMarble*> mpAbsorbs;

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

	Ogre::SceneNode* mPlayerLight;

	Ogre::Entity* mCharacterEntity;

	Ogre::AnimationState* mAnimationState;

	Ogre::Overlay* mHPBarOverlay;

	Ogre::OverlaySystem* mOverlaySystem;
	Ogre::OverlayManager*    mOverlayMgr;
	Ogre::Overlay*           mTextOverlay;
	Ogre::Overlay*           mLogoOverlay;
	Ogre::Overlay*           mDebugOverlay;
	Ogre::OverlayElement*	 mTextUIOverlay;
	Ogre::OverlayContainer*  mPanel;

	float mfRegenTime;
	const float REGEN_TERM = 15.0f;
	int mKillNum;
};


#endif