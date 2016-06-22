#include "TitleState.h"
#include "GameOverState.h"
#include <fstream>

using namespace Ogre;

GameOverState GameOverState::mState;

void GameOverState::enter(GameManager* game)
{
	mContinue = true;
	mScreenOverlay = OverlayManager::getSingleton().getByName("Overlay/GAME_OVER");
	mScreenOverlay->show();

	mOverlayMgr = OverlayManager::getSingletonPtr();
	
	if (nullptr == mTextOverlay)
	{
		mTextOverlay = mOverlayMgr->create("TextOverlayResult");
		mPanel = static_cast<Ogre::OverlayContainer*>
			(mOverlayMgr->createOverlayElement("Panel", "containerResult"));
		mTextUIOverlay = mOverlayMgr->createOverlayElement("TextArea", "Result");


		mTextUIOverlay->setMetricsMode(Ogre::GMM_PIXELS);
		mTextUIOverlay->setPosition(0, 0);
		mTextUIOverlay->setWidth(100);
		mTextUIOverlay->setHeight(20);
		mTextUIOverlay->setParameter("font_name", "Font/NanumBold18");
		mTextUIOverlay->setParameter("char_height", "40");
		mTextUIOverlay->setColour(Ogre::ColourValue::Red);

		mPanel->addChild(mTextUIOverlay);
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.2f, 0.04f);

		mTextOverlay->add2D(mPanel);
		mTextOverlay->setZOrder(102);

	}
	else
	{
		mTextOverlay = mOverlayMgr->getByName("TextOverlayResult");
		//mPanel = static_cast<Ogre::OverlayContainer*>
		//	(mOverlayMgr->getOverlayElement("Panel", "containerResult"));
		//mTextUIOverlay = mOverlayMgr->getOverlayElement("TextArea", "Result");
	}

	mTextOverlay->show();
	_setResultCaption(game);
}

void GameOverState::exit(GameManager* game)
{
	mScreenOverlay->hide();
	mTextOverlay->hide();
	game->setScore(0);
}

void GameOverState::pause(GameManager* game)
{
	std::cout << "TitleState pause\n";
}

void GameOverState::resume(GameManager* game)
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

void GameOverState::_setResultCaption(GameManager * game)
{

	int maxScore = 0;
	int myScore = game->getScore();
	bool renew = false;

	ifstream in("data/record/record.txt");
	in >> maxScore;
	in.close();

	renew = maxScore < myScore;

	if (renew)
	{
		ofstream out("data/record/record.txt");
		out << myScore;
		out.close();
	}

	wchar_t ret[52];
	if (renew)
		swprintf(ret, L"[갱신!] Kill : %d / 이전 최고 스코어 : %d", myScore, maxScore);
	else
		swprintf(ret, L"[결과] Kill : %d / 이전 최고 스코어 : %d", myScore, maxScore);

	mTextUIOverlay->setCaption(ret);
}
