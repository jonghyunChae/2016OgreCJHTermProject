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

	setMaxSpeed(200.f);
	setCameraDragSpeed(100.f);

	auto yaw = getYawNode();
	yaw->scale(Vector3(0.01f, 0.01f, 0.01f));
	yaw->rotate(Vector3(1, 0, 0), Degree(90));

	insertAnimationState(yaw, eIDLE, string("Idle.mesh"), string("Idle"));
	insertAnimationState(yaw, eWALKING, string("Walk.mesh"), string("Walk"));

	Entity* characterEntity = getAnimEntity(OBJ_STATE::eIDLE);
	mpEntity = characterEntity;
	mpEntity->setVisible(true);
	characterEntity->setCastShadows(true);
}

void CWarriorPlayer::update(float frameTime)
{
	CPlayer::update(frameTime);
}
