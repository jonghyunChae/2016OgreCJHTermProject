#pragma once

#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "DynamicObject.h"

class CCharacter : public CDynamicObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr);
	virtual void update(float fFrameTime);
};

#endif

