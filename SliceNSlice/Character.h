#pragma once

#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "DynamicObject.h"
#include "PlayInfoStatus.h"

class CCharacter : public CDynamicObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime);

	virtual bool damaged(int dmg);
	virtual void setActive(bool val) { active = val; if (mCurrentNode) mCurrentNode->setVisible(val); }
public:
	void insertAnimationState(SceneNode * bodyRoot, OBJ_STATE state, string & meshName, string & animName); 
	void setAnimation(string name, bool loop = true);
	void setAnimation(OBJ_STATE stat, bool loop = true);
	Entity* getAnimEntity(OBJ_STATE state) { return mSceneMgr->getEntity(mAnimList[state]); }
	AnimationState* getAnimState() { return mAnimationState; }

	void setAutoAnimChange(bool set) { mAutoChangeAnim = set; }
	void setMoveOffsetSpeed(float speed) { mOffsetSpeed = speed; }
	//virtual SceneNode * const getRotateNode() { return mCurrentNode; }

	PlayInfoStatus & getStatus() { return mStatus; }

	void setAttackDelay(bool delay) { mAttackDelay = delay; }
	bool isAttackDelay() { return mAttackDelay; }

protected:
	virtual void _rotate(float frameTime);
	virtual void _walking(float frameTime);

protected:
	bool mAttackDelay;

	SceneManager * mSceneMgr;
	PlayInfoStatus mStatus;

private:
	void _checkAnimState(OBJ_STATE before, OBJ_STATE after);
	void _initNodeOffset();
	void _animUpdate(float frameTime);

private:
	bool mAutoChangeAnim;
	float mOffsetSpeed;

	OBJ_STATE mBeforeState;

	std::map<OBJ_STATE, string> mAnimList;
	AnimationState* mAnimationState;
	Ogre::SceneNode * mCurrentNode;

	Vector3 mOffsetVector;
};

#endif

