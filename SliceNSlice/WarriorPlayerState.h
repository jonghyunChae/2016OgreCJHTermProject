#pragma once

#ifndef __WARRIOR_PLAYER_STATE_H
#define __WARRIOR_PLAYER_STATE_H

#include "FSM.h"

class CWarriorPlayer;
class CWarriorIdleState : public CAIState<CWarriorPlayer>
{
	CWarriorIdleState(){}
	virtual ~CWarriorIdleState() {}
	CWarriorIdleState& operator=(const CWarriorIdleState&);

public:
	static CWarriorIdleState & GetInstance();
	virtual void Enter(CWarriorPlayer * pPlayer);
	virtual void Execute(CWarriorPlayer * pPlayer, float fFrameTime);
	virtual void Exit(CWarriorPlayer * pPlayer);

};

#endif