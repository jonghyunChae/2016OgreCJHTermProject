#pragma once

#ifndef __WARRIOR_H
#define __WARRIOR_H

#include "Player.h"

class CWarriorPlayer : public CPlayer
{
public:
	CWarriorPlayer();
	virtual ~CWarriorPlayer();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime);

};

#endif