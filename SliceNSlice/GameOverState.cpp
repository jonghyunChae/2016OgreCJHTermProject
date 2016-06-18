#include "TitleState.h"
#include "GameOverState.h"

using namespace Ogre;

GameOverState GameOverState::mState;

void GameOverState::enter(void)
{
	mContinue = true;
	mScreenOverlay = OverlayManager::getSingleton().getByName("Overlay/GAME_OVER");
	mScreenOverlay->show();

	//mStartMsg = OverlayManager::getSingleton().getOverlayElement("StartMsg");
	//mStartMsg->show();
}

void GameOverState::exit(void)
{
	mScreenOverlay->hide();
}

void GameOverState::pause(void)
{
	std::cout << "TitleState pause\n";
}

void GameOverState::resume(void)
{
	std::cout << "TitleState resume\n";
}

bool GameOverState::frameStarted(GameManager* game, const FrameEvent& evt)
{
	return true;
}

bool GameOverState::frameEnded(GameManager* game, const FrameEvent& evt)
{
	return mContinue;
}

bool GameOverState::keyPressed(GameManager* game, const OIS::KeyEvent &e)
{
	// Fill Here -------------------------------------------------------
	switch (e.key)
	{
	case OIS::KC_SPACE:
		game->changeState(TitleState::getInstance());
		break;

	case OIS::KC_ESCAPE:
		mContinue = false;
		break;
	}
	// -----------------------------------------------------------------

	return true;
}
