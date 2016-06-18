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
	pMonster->setAutoAnimChange(true);

	pPlayer = static_cast<CWarriorPlayer*>(InGameState::getInstance()->getPlayer());

	pMonster->setAnimation(CDynamicObject::eIDLE);
}

void CWarZombieIdleState::Execute(CWarZombie * pMonster, float fFrameTime)
{
	if (pPlayer->getPosition().squaredDistance(pMonster->getPosition()) < chaseRangeSq)
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

	pMonster->moveToPoint(targetPos);
	pMonster->setAutoAnimChange(false);

#if 0
	auto quad = pMonster->getBasicLookVector().getRotationTo(-(targetPos - myPos).normalisedCopy());
	pMonster->getNode()->setOrientation(quad);
#endif
}

void CWarZombieChaseState::Execute(CWarZombie * pMonster, float fFrameTime)
{
	const Real targetDisSq = pPlayer->getPosition().squaredDistance(pMonster->getPosition());
	if (targetDisSq > chaseRangeSq)
	{
		pMonster->getStateMachine()->ChangeState(&CWarZombieIdleState::getInstance());
	}
	if (targetDisSq < attackRangeSq)
	{
		pMonster->getStateMachine()->ChangeState(&CWarZombieAttackState::getInstance());
	}
}

void CWarZombieChaseState::Exit(CWarZombie * pMonster)
{
	pMonster->setAutoAnimChange(true);
}
////////////////////////////////////////////////////////////////////////

CWarZombieAttackState & CWarZombieAttackState::getInstance()
{
	static CWarZombieAttackState instance;
	return instance;
}

void CWarZombieAttackState::Enter(CWarZombie * pMonster)
{
	pMonster->changeState(CDynamicObject::eATTACK);
	pMonster->setAnimation(CDynamicObject::eATTACK);
	pMonster->setAutoAnimChange(false);
}

void CWarZombieAttackState::Execute(CWarZombie * pMonster, float fFrameTime)
{
	const Real targetDisSq = pPlayer->getPosition().squaredDistance(pMonster->getPosition());
	if (targetDisSq > attackRangeSq)
	{
		pMonster->getStateMachine()->ChangeState(&CWarZombieIdleState::getInstance());
	}
	else
	{
		auto timePos = pMonster->getAnimState()->getTimePosition();
		if (0.7f < timePos && timePos < 0.8f)
		{
			if (pMonster->isAttackDelay()) return;

			auto player = InGameState::getInstance()->getPlayer();
			auto pos = pMonster->getPosition();
			auto targetPos = player->getPosition();
			if (targetPos.squaredDistance(pos) < attackRangeSq)
			{
				player->damaged(10);
				pMonster->setAttackDelay(true);
			}
		}
		else
			pMonster->setAttackDelay(false);
	}
}

void CWarZombieAttackState::Exit(CWarZombie * pMonster)
{
	pMonster->setAutoAnimChange(true);
}


///////////////////////////////////////////////////////////////////////
CWarZombieDeathState & CWarZombieDeathState::getInstance()
{
	static CWarZombieDeathState instance;
	return instance;
}

void CWarZombieDeathState::Enter(CWarZombie * pMonster)
{
	pMonster->setAnimation(CDynamicObject::eDEATH, false);
	pMonster->setAutoAnimChange(false);
}

void CWarZombieDeathState::Execute(CWarZombie * pMonster, float fFrameTime)
{
}

void CWarZombieDeathState::Exit(CWarZombie * pMonster)
{
	pMonster->setAutoAnimChange(true);
}
