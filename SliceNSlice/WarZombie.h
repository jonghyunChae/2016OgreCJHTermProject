#pragma once

#ifndef __WAR_ZOMBIE_H
#define __WAR_ZOMBIE_H

#include "Monster.h"
#include "FSM.h"

class CWarZombie : public CMonster
{

public:
	CWarZombie();
	virtual ~CWarZombie();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName, int index);
	virtual void update(float fFrameTime);

	virtual bool damaged(int dmg);
	virtual void revive();
public:
	CStateMachine<CWarZombie> * getStateMachine() { return mpStateMachine; }

private:
	CStateMachine<CWarZombie> * mpStateMachine;
};

#endif