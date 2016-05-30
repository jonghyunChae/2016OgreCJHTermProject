#pragma once

#ifndef __WAR_ZOMBIE_STATE_H
#define __WAR_ZOMBIE_STATE_H

#include "FSM.h"

class CWarZombie;
class CWarZombieIdleState : public CAIState<CWarZombie>
{
public:
	static CWarZombieIdleState & getInstance();
	virtual void Enter(CWarZombie * pMonster);
	virtual void Execute(CWarZombie * pMonster, float fFrameTime);
	virtual void Exit(CWarZombie * pMonster);

private:
	CWarZombieIdleState() {}
	virtual ~CWarZombieIdleState() {}
	CWarZombieIdleState& operator=(const CWarZombieIdleState&);

private:
	const float chaseRangeSq = 10000.f;
};

class CWarZombieChaseState : public CAIState<CWarZombie>
{
public:
	static CWarZombieChaseState & getInstance();
	virtual void Enter(CWarZombie * pMonster);
	virtual void Execute(CWarZombie * pMonster, float fFrameTime);
	virtual void Exit(CWarZombie * pMonster);

private:
	CWarZombieChaseState() {}
	virtual ~CWarZombieChaseState() {}
	CWarZombieChaseState& operator=(const CWarZombieChaseState&);

private:
	const float attackRangeSq = 4000.f;
	const float chaseRangeSq = 100000.f;
};

class CWarZombieAttackState : public CAIState<CWarZombie>
{

public:
	static CWarZombieAttackState & getInstance();
	virtual void Enter(CWarZombie * pMonster);
	virtual void Execute(CWarZombie * pMonster, float fFrameTime);
	virtual void Exit(CWarZombie * pMonster);

private:
	CWarZombieAttackState() {}
	virtual ~CWarZombieAttackState() {}
	CWarZombieAttackState& operator=(const CWarZombieAttackState&);

private:
	const float attackRangeSq = 4000.f;
};

class CWarZombieDeathState : public CAIState<CWarZombie>
{
public:
	static CWarZombieDeathState & getInstance();
	virtual void Enter(CWarZombie * pMonster);
	virtual void Execute(CWarZombie * pMonster, float fFrameTime);
	virtual void Exit(CWarZombie * pMonster);

private:
	CWarZombieDeathState() {}
	virtual ~CWarZombieDeathState() {}
	CWarZombieDeathState& operator=(const CWarZombieDeathState&);

};

#endif