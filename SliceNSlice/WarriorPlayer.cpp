#include "WarriorPlayer.h"
#include "WarriorPlayerState.h"

CWarriorPlayer::CWarriorPlayer()
{
}

CWarriorPlayer::~CWarriorPlayer()
{
}

void CWarriorPlayer::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	CPlayer::buildObject(pRoot, pSceneMgr, objName);

	setMaxSpeed(50.f);
	setMoveOffsetSpeed(100.f);
	setCameraDragSpeed(30.f);
	mStatus.setHP(100);

	auto yaw = getYawNode();
	yaw->scale(Vector3(0.01f, 0.01f, 0.01f));
	//yaw->rotate(Vector3(1, 0, 0), Degree(90));

	insertAnimationState(yaw, eIDLE,    string("Idle.mesh"),  string("Idle"));
	insertAnimationState(yaw, eWALKING, string("Walk.mesh"),  string("Walk"));
	insertAnimationState(yaw, eATTACK,  string("Slash.mesh"), string("Slash"));

	Entity* characterEntity = getAnimEntity(OBJ_STATE::eIDLE);
	mpEntity = characterEntity;
	mpEntity->setVisible(true);
	characterEntity->setCastShadows(true);

	mpStateMachine = new CStateMachine<CWarriorPlayer>(this);
	mpStateMachine->SetCurrentState(&CWarriorIdleState::getInstance());
}

void CWarriorPlayer::update(float frameTime)
{
	CPlayer::update(frameTime);

	mpStateMachine->Update(frameTime);
}

bool CWarriorPlayer::damaged(int dmg)
{
	bool isDeath = mStatus.damaged(dmg);
	if (isDeath)
		mpStateMachine->ChangeState(&CWarriorDeathState::getInstance());

	return isDeath;
}
