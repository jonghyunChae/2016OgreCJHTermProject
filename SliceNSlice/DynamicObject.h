#pragma once

#ifndef __DYNAMIC_OBJECT_H
#define __DYNAMIC_OBJECT_H

#include "GameObject.h"

class CDynamicObject : public CGameObject
{
public:
	CDynamicObject();
	virtual ~CDynamicObject();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime);

public:
	Vector3 & getDir() { return mDir; }
	void setDir(Vector3 & dir) { mDir = dir; }

	float getMaxSpeed() { return mMaxSpeed; }
	void setMaxSpeed(float fSpeed) { mMaxSpeed = fSpeed; }

public:
	enum OBJ_STATE { eNONE = -1, eIDLE, eWALKING, eROTATING, eATTACK, eDEATH };

	bool changeState(const Vector3 & before, const Vector3 & afterVelocity);
	void changeState(OBJ_STATE stat) { mState = stat; }
	bool isMovingToPoint() { return mTargetDistance > 0.f; }
	
	void moveToPoint(const Vector3 & pos);
	void move(const Vector3 & addVelocity);

protected:
	Vector3  mDir;
	float    mMaxSpeed;

	Vector3  mVelocity;

	OBJ_STATE mState;

private:
	Quaternion mSrcQuat, mDestQuat;
	float mRotatingTime;

	Vector3 mTargetPos;
	float mTargetDistance;

};

#endif