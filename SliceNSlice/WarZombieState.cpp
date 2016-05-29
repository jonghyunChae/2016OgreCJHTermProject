#include "WarZombieState.h"
#include "WarZombie.h"
#include "IngameState.h"

static CWarriorPlayer * pPlayer = nullptr;

CWarZombieIdleState & CWarZombieIdleState::getInstance()
{
	static CWarZombieIdleState instance;
	return instance;
}

void CWarZombieIdleState::Enter(CWarZombie * pMonster)
{
	if (nullptr == pPlayer)
		pPlayer = static_cast<CWarriorPlayer*>(InGameState::getInstance()->getPlayer());

	pMonster->setAnimation(CDynamicObject::eIDLE);
}

void CWarZombieIdleState::Execute(CWarZombie * pMonster, float fFrameTime)
{
	if (pPlayer->getPosition().squaredDistance(pMonster->getPosition()) < 3600)
	{
		pMonster->getStateMachine()->ChangeState(&CWarZombieChaseState::getInstance());
	}
}

void CWarZombieIdleState::Exit(CWarZombie * pMonster)
{
}

////////////////////////////////////////////////////////////////////
CWarZombieChaseState & CWarZombieChaseState::getInstance()
{
	static CWarZombieChaseState instance;
	return instance;
}

void CWarZombieChaseState::Enter(CWarZombie * pMonster)
{
	pMonster->setAnimation(CDynamicObject::eWALKING);

	Vector3 myPos = pMonster->getPosition();
	Vector3 targetPos = pPlayer->getPosition();
	targetPos.y = myPos.y;
	pMonster->move((targetPos - myPos).normalisedCopy() * 30.f);

//	pMonster->moveToPoint(targetPos);

#if 0
	auto quad = pMonster->getBasicLookVector().getRotationTo(-(targetPos - myPos).normalisedCopy());
	pMonster->getNode()->setOrientation(quad);
#endif
}

void CWarZombieChaseState::Execute(CWarZombie * pMonster, float fFrameTime)
{
	if (pPlayer->getPosition().squaredDistance(pMonster->getPosition()) > 10000)
	{
		pMonster->getStateMachine()->ChangeState(&CWarZombieIdleState::getInstance());
	}
}

void CWarZombieChaseState::Exit(CWarZombie * pMonster)
{
}
