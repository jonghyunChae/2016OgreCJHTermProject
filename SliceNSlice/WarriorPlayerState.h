#pragma once

#ifndef __WARRIOR_PLAYER_STATE_H
#define __WARRIOR_PLAYER_STATE_H

#include "FSM.h"

class CWarriorPlayer;
class CWarriorIdleState : public CAIState<CWarriorPlayer>
{
public:
	static CWarriorIdleState & getInstance();
	virtual void Enter(CWarriorPlayer * pPlayer);
	virtual void Execute(CWarriorPlayer * pPlayer, float fFrameTime);
	virtual void Exit(CWarriorPlayer * pPlayer);

private:
	CWarriorIdleState(){}
	virtual ~CWarriorIdleState() {}
	CWarriorIdleState& operator=(const CWarriorIdleState&);
};

class CWarriorAttackState : public CAIState<CWarriorPlayer>
{
public:
	static CWarriorAttackState & getInstance();
	virtual void Enter(CWarriorPlayer * pPlayer);
	virtual void Execute(CWarriorPlayer * pPlayer, float fFrameTime);
	virtual void Exit(CWarriorPlayer * pPlayer);

private:
	CWarriorAttackState() {}
	virtual ~CWarriorAttackState() {}
	CWarriorAttackState& operator=(const CWarriorAttackState&);

private:
	const float attackRange = 80.f;
};

class CWarriorDeathState : public CAIState<CWarriorPlayer>
{
public:
	static CWarriorDeathState & getInstance();
	virtual void Enter(CWarriorPlayer * pPlayer);
	virtual void Execute(CWarriorPlayer * pPlayer, float fFrameTime);
	virtual void Exit(CWarriorPlayer * pPlayer);

private:
	CWarriorDeathState() {}
	virtual ~CWarriorDeathState() {}
	CWarriorDeathState& operator=(const CWarriorDeathState&);
};

#endif