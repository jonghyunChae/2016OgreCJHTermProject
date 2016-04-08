#pragma once
#ifndef __STATIC_OBJECT_H
#define __STATIC_OBJECT_H

#include "GameObject.h"

class CStaticObject : public CGameObject
{

public:
	CStaticObject();
	virtual ~CStaticObject();

	virtual void update(float fFrameTime);
};

#endif