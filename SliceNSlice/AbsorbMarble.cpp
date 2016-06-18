#include "AbsorbMarble.h"
#include "IngameState.h"

AbsorbMarble::AbsorbMarble()
{
	active = false;
}

AbsorbMarble::~AbsorbMarble()
{
}

void AbsorbMarble::buildObject(Root* pRoot, SceneManager* pSceneMgr, int index)
{
	char name[20], nameroot[20];
	sprintf(name, "Absorb%d", index);
	//mpEntity = pSceneMgr->getEntity(name);

	//if (nullptr == mpEntity)
	{
		mpEntity = pSceneMgr->createEntity(name, "Sphere001.mesh");

		sprintf(nameroot, "AbsorbRoot%d", index);
		auto root = pSceneMgr->getRootSceneNode()->createChildSceneNode(nameroot, Vector3(0, 10, 0));
		mpNode = root->createChildSceneNode(name);
		mpNode->attachObject(mpEntity);
		mpNode->scale(Vector3(0.01, 0.01, 0.01));
	}
	mpNode = pSceneMgr->getSceneNode(name);
	mpNode->setVisible(false);
	active = false;
}

void AbsorbMarble::update(float fFrameTime)
{
	if (false == active) return;

	auto player = InGameState::getInstance()->getPlayer();
	auto playerPos = player->getPosition();
	auto myPos = getPosition();

	if (myPos.squaredDistance(playerPos) <= 900)
	{
		player->getStatus().healHP(3);
		active = false;
		mpNode->setVisible(active);
	}
}

bool AbsorbMarble::allocMarble(Vector3 & pos)
{
	if (active) return false;

	active = true;
	mpNode->setVisible(active);
	mpNode->setPosition(pos);
	return true;
}
