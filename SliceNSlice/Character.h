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
	void insertAnimationState(SceneNode * bodyRoot, OBJ_STATE state, string & meshName, string & animName); 
	void setAnimation(string name);
	Entity* getAnimEntity(OBJ_STATE state) { return mSceneMgr->getEntity(mAnimList[state]); }

protected:
	virtual void _rotate(float frameTime);
	virtual void _walking(float frameTime);

protected:
	SceneManager * mSceneMgr;

private:
	void _checkAnimState(OBJ_STATE before, OBJ_STATE after);

private:
	OBJ_STATE mBeforeState;

	std::map<OBJ_STATE, string> mAnimList;
	AnimationState* mAnimationState;

};

#endif

