#pragma once

#ifndef __DYNAMIC_OBJECT_H
#define __DYNAMIC_OBJECT_H

#include "GameObject.h"

class CDynamicObject : public CGameObject
{
public:
	CDynamicObject();
	virtual ~CDynamicObject();

	virtual void update(float fFrameTime);

public:
	Vector3 & getDir() { return mDir; }
	void setDir(Vector3 & dir) { mDir = dir; }

	float getMaxSpeed() { return mMaxSpeed; }
	void setMaxSpeed(float fSpeed) { mMaxSpeed = fSpeed; }

protected:
	Vector3  mDir;
	float    mMaxSpeed;

	Vector3  mVelocity;
};

#endif