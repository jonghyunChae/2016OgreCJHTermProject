#include "TitleState.h"
#include "IngameState.h"

using namespace Ogre;

TitleState TitleState::mTitleState;
Overlay * textOverlay = nullptr;

TitleState::TitleState()
{
}

void TitleState::enter(void)
{
	mContinue = true;
	mTitleOverlay = OverlayManager::getSingleton().getByName("Overlay/Title");
	mTitleOverlay->show();

	auto overlayMgr = OverlayManager::getSingletonPtr();
	//if (nullptr == textOverlay)

	if (nullptr == textOverlay) 
	{
		textOverlay = overlayMgr->create("TextOverlay");
		auto panel = static_cast<Ogre::OverlayContainer*>
			(overlayMgr->createOverlayElement("Panel", "container1"));
		panel->setDimensions(1, 1);
		panel->setPosition(0.35f, 0.8f);
		mStartMsg = overlayMgr->createOverlayElement("TextArea", "TextID");
		mStartMsg->setMetricsMode(Ogre::GMM_PIXELS);
		mStartMsg->setPosition(10, 10);
		mStartMsg->setWidth(100);
		mStartMsg->setHeight(20);
		mStartMsg->setParameter("font_name", "Font/NanumBold18");
		mStartMsg->setParameter("char_height", "40");
		mStartMsg->setColour(Ogre::ColourValue::White);
		mStartMsg->setCaption(L"게임시작 SpaceBar");
		panel->addChild(mStartMsg);
		textOverlay->add2D(panel);
	}
	textOverlay->show();
	//mStartMsg = OverlayManager::getSingleton().getOverlayElement("StartMsg");
	//mStartMsg->show();
}

void TitleState::exit(void)
{

	mTitleOverlay->hide();
	OverlayManager::getSingletonPtr()->getByName("TextOverlay")->hide();
}

void TitleState::pause(void)
{
	std::cout << "TitleState pause\n";
}

void TitleState::resume(void)
{
	std::cout << "TitleState resume\n";
}

bool TitleState::frameStarted(GameManager* game, const FrameEvent& evt)
{
	static float elapsed = 0.0f;

	elapsed += evt.timeSinceLastFrame;

	if ((int)(elapsed * 4) % 3)
	{
		mStartMsg->show();
	}
	else
	{
		mStartMsg->hide();
	}

	return true;
}

bool TitleState::frameEnded(GameManager* game, const FrameEvent& evt)
{
	return mContinue;
}

bool TitleState::keyPressed(GameManager* game, const OIS::KeyEvent &e)
{
	// Fill Here -------------------------------------------------------
	switch (e.key)
	{
	case OIS::KC_SPACE:
		game->changeState(InGameState::getInstance());
		break;

	case OIS::KC_ESCAPE:
		mContinue = false;
		break;
	}
	// -----------------------------------------------------------------

	return true;
}
