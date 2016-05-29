#include "TitleState.h"
#include "IngameState.h"

using namespace Ogre;

TitleState TitleState::mTitleState;

void TitleState::enter(void)
{
	mContinue = true;
	mTitleOverlay = OverlayManager::getSingleton().getByName("Overlay/Title");
	//mStartMsg = OverlayManager::getSingleton().getOverlayElement("StartMsg");
	mTitleOverlay->show();
	//mStartMsg->show();

	auto overlayMgr = OverlayManager::getSingletonPtr();
	auto textOverlay = overlayMgr->create("TextOverlay");
	auto panel = static_cast<Ogre::OverlayContainer*>
		(overlayMgr->createOverlayElement("Panel", "container1"));
	panel->setDimensions(1, 1);
	panel->setPosition(0.35f, 0.8f);
	OverlayElement* textBox = overlayMgr->createOverlayElement("TextArea", "TextID");
	textBox->setMetricsMode(Ogre::GMM_PIXELS);
	textBox->setPosition(10, 10);
	textBox->setWidth(100);
	textBox->setHeight(20);
	textBox->setParameter("font_name", "Font/NanumBold18");
	textBox->setParameter("char_height", "40");
	textBox->setColour(Ogre::ColourValue::White);
	textBox->setCaption(L"게임시작 SpaceBar");
	panel->addChild(textBox);
	textOverlay->add2D(panel);
	textOverlay->show();
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

	if ((int)(elapsed * 4) % 2)
	{
		//mStartMsg->show();
	}
	else
	{
		//mStartMsg->hide();
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
