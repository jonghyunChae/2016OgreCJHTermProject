#pragma once

#ifndef __WAR_ZOMBIE_STATE_H
#define __WAR_ZOMBIE_STATE_H

#include "FSM.h"

class CWarZombie;
class CWarZombieIdleState : public CAIState<CWarZombie>
{
	CWarZombieIdleState() {}
	virtual ~CWarZombieIdleState() {}
	CWarZombieIdleState& operator=(const CWarZombieIdleState&);

public:
	static CWarZombieIdleState & getInstance();
	virtual void Enter(CWarZombie * pMonster);
	virtual void Execute(CWarZombie * pMonster, float fFrameTime);
	virtual void Exit(CWarZombie * pMonster);

};

class CWarZombieChaseState : public CAIState<CWarZombie>
{
	CWarZombieChaseState() {}
	virtual ~CWarZombieChaseState() {}
	CWarZombieChaseState& operator=(const CWarZombieChaseState&);

public:
	static CWarZombieChaseState & getInstance();
	virtual void Enter(CWarZombie * pMonster);
	virtual void Execute(CWarZombie * pMonster, float fFrameTime);
	virtual void Exit(CWarZombie * pMonster);
};

#endif