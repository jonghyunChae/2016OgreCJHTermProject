#include "DynamicObject.h"



CDynamicObject::CDynamicObject() : CGameObject()
{
	mVelocity = { 0, 0, 0 };
	mDir = { 0, 0, 0 };
	mMaxSpeed = 0.0f;
}


CDynamicObject::~CDynamicObject()
{
}

void CDynamicObject::update(float fFrameTime)
{
	if (mpChildObject) mpChildObject->update(fFrameTime);
}
