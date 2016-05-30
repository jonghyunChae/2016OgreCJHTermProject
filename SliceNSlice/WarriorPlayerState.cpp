#include "WarriorPlayerState.h"
#include "WarriorPlayer.h"
#include "Monster.h"

CWarriorIdleState & CWarriorIdleState::getInstance()
{
	static CWarriorIdleState instance;
	return instance;
}

void CWarriorIdleState::Enter(CWarriorPlayer * pPlayer)
{
	pPlayer->setAnimation(CDynamicObject::eIDLE);
}

void CWarriorIdleState::Execute(CWarriorPlayer * pPlayer, float fFrameTime)
{
}

void CWarriorIdleState::Exit(CWarriorPlayer * pPlayer)
{
}
/////////////////////////////////////////////////////////////////////////////
CWarriorAttackState & CWarriorAttackState::getInstance()
{
	static CWarriorAttackState instance;
	return instance;
}

void CWarriorAttackState::Enter(CWarriorPlayer * pPlayer)
{
	pPlayer->setAnimation(CDynamicObject::eATTACK, false);
	pPlayer->setAutoAnimChange(false);
}

void CWarriorAttackState::Execute(CWarriorPlayer * pPlayer, float fFrameTime)
{
	const Real timePos = pPlayer->getAnimState()->getTimePosition();
	
	if (0.8f < timePos && timePos < 0.9f)
	{
		auto & monArray = pPlayer->getTargetMonsterArray();
		const Vector3 & pos = pPlayer->getPosition();
		
		for (auto & mon : monArray)
		{
			if (false == mon->getStatus().isDeath())
			{
				if (mon->getPosition().distance(pos) < attackRange)
					mon->damaged(10);
			}
		}
	}

	if (pPlayer->getAnimState()->hasEnded())
		pPlayer->getStateMachine()->ChangeState(&CWarriorIdleState::getInstance());
}

void CWarriorAttackState::Exit(CWarriorPlayer * pPlayer)
{
	pPlayer->setAutoAnimChange(true);
}
//////////////////////////////////////////////////////////////////////////////////
CWarriorDeathState & CWarriorDeathState::getInstance()
{
	static CWarriorDeathState instance;
	return instance;
}

void CWarriorDeathState::Enter(CWarriorPlayer * pPlayer)
{
	pPlayer->changeState(CDynamicObject::eDEATH);
	pPlayer->setAnimation(CDynamicObject::eDEATH, false);
	pPlayer->setAutoAnimChange(false);
}

void CWarriorDeathState::Execute(CWarriorPlayer * pPlayer, float fFrameTime)
{
}

void CWarriorDeathState::Exit(CWarriorPlayer * pPlayer)
{
	pPlayer->setAutoAnimChange(true);
}
