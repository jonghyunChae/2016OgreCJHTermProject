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
	void setAnimation(string name, bool loop = true);
	void setAnimation(OBJ_STATE stat, bool loop = true);
	Entity* getAnimEntity(OBJ_STATE state) { return mSceneMgr->getEntity(mAnimList[state]); }
	AnimationState* getAnimState() { return mAnimationState; }

protected:
	virtual void _rotate(float frameTime);
	virtual void _walking(float frameTime);

protected:
	SceneManager * mSceneMgr;

private:
	void _checkAnimState(OBJ_STATE before, OBJ_STATE after);
	void _initNodeOffset();
	void _animUpdate(float frameTime);

private:
	OBJ_STATE mBeforeState;

	std::map<OBJ_STATE, string> mAnimList;
	AnimationState* mAnimationState;
	Ogre::SceneNode * mCurrentNode;

	Vector3 mOffsetVector;
};

#endif

