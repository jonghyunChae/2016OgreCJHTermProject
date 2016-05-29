#pragma once

#ifndef __MONSTER_H
#define __MONSTER_H

#include "Character.h"

class CMonster : public CCharacter
{
public:
	CMonster();
	virtual ~CMonster();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName, int index);
	virtual void update(float fFrameTime);
};

#endif