#include "WarriorPlayer.h"

CWarriorPlayer::CWarriorPlayer()
{
}

CWarriorPlayer::~CWarriorPlayer()
{
}

void CWarriorPlayer::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	CPlayer::buildObject(pRoot, pSceneMgr, objName);

	setMaxSpeed(100.f);
	setCameraDragSpeed(50.f);

	insertAnimationState(eIDLE, string("Idle"));
	insertAnimationState(eWALKING, string("Walk"));
}

void CWarriorPlayer::update(float frameTime)
{
	CPlayer::update(frameTime);
}
