#include "WarZombie.h"
#include "WarZombieState.h"

CWarZombie::CWarZombie()
{
	mpStateMachine = nullptr;
}


CWarZombie::~CWarZombie()
{
}

void CWarZombie::buildObject(Root * pRoot, SceneManager * pSceneMgr, const char * objName, int index)
{
	mSceneMgr = pSceneMgr;

	setMaxSpeed(150.f);

	mpNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(objName, Vector3(0, 100000, 0));
	mpNode->scale(Vector3(0.004f, 0.004f, 0.004f));
	//mpNode->translate(Vector3(0, 0, 0));
	basicRotate(-Vector3::UNIT_Y);
	//mpNode->rotate(Vector3(1, 0, 0), Degree(90));

	static char animName[4][56];
	sprintf(animName[0], "WarZombie_Idle%d", index);
	sprintf(animName[1], "WarZombie_Walk%d", index);
	sprintf(animName[2], "WarZombie_Attack%d", index);
	sprintf(animName[3], "WarZombie_Death%d", index);
	
	insertAnimationState(mpNode, eIDLE, string("WarZombie_Idle.mesh"), string(animName[0]));
	insertAnimationState(mpNode, eWALKING, string("WarZombie_Walk.mesh"), string(animName[1]));
	insertAnimationState(mpNode, eATTACK, string("WarZombie_Attack.mesh"), string(animName[2]));
	insertAnimationState(mpNode, eDEATH, string("WarZombie_Death.mesh"), string(animName[3]));

	Entity* entity = getAnimEntity(OBJ_STATE::eIDLE);
	mpEntity = entity;
	entity->setVisible(true);
	entity->setCastShadows(true);

	mpStateMachine = new CStateMachine<CWarZombie>(this);
	mpStateMachine->SetCurrentState(&CWarZombieIdleState::getInstance());
}

void CWarZombie::update(float frameTime)
{
	CMonster::update(frameTime);

	mpStateMachine->Update(frameTime);
}
