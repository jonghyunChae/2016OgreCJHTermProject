#pragma once

#include "GameState.h"

class GameOverState : public GameState
{
public:
	// Fill Here --------------------------------------------------------------------------------------------
	void enter(GameManager* game);
	void exit(GameManager* game);
	void pause(GameManager* game);
	void resume(GameManager* game);
	bool frameStarted(GameManager* game, const Ogre::FrameEvent& evt);
	bool frameEnded(GameManager* game, const Ogre::FrameEvent& evt);
	bool mouseMoved(GameManager* game, const OIS::MouseEvent &e)
	{
		return true;
	}
	bool mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}
	bool mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}
	bool keyPressed(GameManager* game, const OIS::KeyEvent &e);
	bool keyReleased(GameManager* game, const OIS::KeyEvent &e) { return true; }
	// -------------------------------------------------------------------------------------------------------

	static GameOverState* getInstance() { return &mState; }

private:
	static GameOverState mState;
	GameOverState() { mTextOverlay = nullptr; }

	void _setResultCaption(GameManager * game);

	bool mContinue;

	Ogre::Overlay* mScreenOverlay;

	Ogre::OverlaySystem* mOverlaySystem;
	Ogre::OverlayManager*    mOverlayMgr;
	Ogre::Overlay*           mTextOverlay;
	Ogre::Overlay*           mLogoOverlay;
	Ogre::Overlay*           mDebugOverlay;
	Ogre::OverlayElement*	 mTextUIOverlay;
	Ogre::OverlayContainer*  mPanel;
};
