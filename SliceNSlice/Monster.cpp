#include "Monster.h"

CMonster::CMonster()
{
	mfDeathTime = 0.f;
}

CMonster::~CMonster()
{
}

void CMonster::buildObject(Root * pRoot, SceneManager * pSceneMgr, const char * objName, int index)
{
	//CCharacter::buildObject(pRoot, pSceneMgr, objName);
	mSceneMgr = pSceneMgr;

	setMaxSpeed(150.f);

	char nodeName[56];
	sprintf(nodeName, "%sRoot", objName);
	SceneNode * pRootNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName, Vector3::ZERO);
	mpNode = pRootNode->createChildSceneNode(objName);
	mpNode->scale(Vector3(0.004f, 0.004f, 0.004f));
	mpNode->rotate(Vector3(1, 0, 0), Degree(90));
	mpNode->setInheritOrientation(false);
	mpNode = pRootNode;

	static char animName[4][56];
	sprintf(animName[0], "WarZombie_Idle%d", index);
	sprintf(animName[1], "WarZombie_Walk%d", index);
	sprintf(animName[2], "WarZombie_Attack%d", index);
	sprintf(animName[3], "WarZombie_Death%d", index);

	insertAnimationState(mpNode, eIDLE,    string("WarZombie_Idle.mesh"),   string(animName[0]));
	insertAnimationState(mpNode, eWALKING, string("WarZombie_Walk.mesh"),   string(animName[1]));
	insertAnimationState(mpNode, eATTACK,  string("WarZombie_Attack.mesh"), string(animName[2]));
	insertAnimationState(mpNode, eDEATH,   string("WarZombie_Death.mesh"),  string(animName[3]));

	Entity* entity = getAnimEntity(OBJ_STATE::eIDLE);
	mpEntity = entity;
	entity->setVisible(true);
	entity->setCastShadows(true);
}

void CMonster::update(float fFrameTime)
{
	if (mStatus.isDeath())
	{
		mfDeathTime += fFrameTime;
		if (mfDeathTime >= 4.0f)
			mpEntity->setVisible(false);
	}

	CCharacter::update(fFrameTime);
}

bool CMonster::damaged(int dmg)
{
	bool death = mStatus.damaged(dmg);
	if (death) mfDeathTime = 0.0f;
	return death;
}

void CMonster::revive()
{
	mStatus.healHP(1000);

}
