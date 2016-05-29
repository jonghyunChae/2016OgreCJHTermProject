#include "WarriorPlayerState.h"
#include "WarriorPlayer.h"

CWarriorIdleState & CWarriorIdleState::getInstance()
{
	static CWarriorIdleState instance;
	return instance;
}

void CWarriorIdleState::Enter(CWarriorPlayer * pPlayer)
{
}

void CWarriorIdleState::Execute(CWarriorPlayer * pPlayer, float fFrameTime)
{
}

void CWarriorIdleState::Exit(CWarriorPlayer * pPlayer)
{
}
