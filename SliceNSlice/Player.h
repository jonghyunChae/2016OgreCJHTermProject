#pragma once

#ifndef __PLAYER_H
#define __PLAYER_H

#include "Character.h"

class CPlayer : public CCharacter
{
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update(float fFrameTime);

public:
	void setCamera(Camera * pCamera) { mCamera = pCamera; }
	Camera* getCamera() { return mCamera; }

private:
	Camera * mCamera;
};

#endif