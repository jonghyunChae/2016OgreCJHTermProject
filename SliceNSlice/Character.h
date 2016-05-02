#pragma once

#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "DynamicObject.h"

class CCharacter : public CDynamicObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime);

public:
	void insertAnimationState(OBJ_STATE state, string & animName) { mAnimList[state] = animName; }
	void setAnimation(string name);


protected:
	virtual void _rotate(float frameTime);
	virtual void _walking(float frameTime);

private:
	void _checkAnimState(OBJ_STATE before, OBJ_STATE after);

private:
	OBJ_STATE mBeforeState;

	std::map<OBJ_STATE, string> mAnimList;
	AnimationState* mAnimationState;

};

#endif

