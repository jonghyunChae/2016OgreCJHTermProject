#pragma once

#ifndef __WARRIOR_H
#define __WARRIOR_H

#include "Player.h"
#include "FSM.h"

class CMonster;
class CWarriorPlayer : public CPlayer
{
public:
	CWarriorPlayer();
	virtual ~CWarriorPlayer();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime);

	virtual bool damaged(int dmg);

public:
	CStateMachine<CWarriorPlayer> * getStateMachine() { return mpStateMachine; }
	std::vector<CMonster*> & getTargetMonsterArray() { return mTargetMonsterArray;	}

private:
	CStateMachine<CWarriorPlayer> * mpStateMachine;
	std::vector<CMonster*> mTargetMonsterArray;
};

#endif