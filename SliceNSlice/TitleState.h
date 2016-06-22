#pragma once

#include "GameState.h"

class TitleState : public GameState
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

	static TitleState* getInstance() { return &mTitleState; }

private:
	TitleState();

	static TitleState mTitleState;

	bool mContinue;

	Ogre::Overlay* mTitleOverlay;
	Ogre::OverlayElement* mStartMsg;
};
