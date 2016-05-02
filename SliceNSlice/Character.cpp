#include "Character.h"

CCharacter::CCharacter() : CDynamicObject()
{
	mAnimationState = nullptr;
	mBeforeState = eIDLE;
}

CCharacter::~CCharacter()
{
}

void CCharacter::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	CDynamicObject::buildObject(pRoot, pSceneMgr, objName);
}

void CCharacter::update(float frameTime)
{
	CDynamicObject::update(frameTime);

	_checkAnimState(mBeforeState, mState);
	mBeforeState = mState;

	mAnimationState->addTime(frameTime);
}

void CCharacter::setAnimation(string name)
{
	if (mAnimationState) mAnimationState->setEnabled(false);

	mAnimationState = mpEntity->getAnimationState(name);
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
}

void CCharacter::_rotate(float frameTime)
{

}

void CCharacter::_walking(float frameTime)
{
}

void CCharacter::_checkAnimState(OBJ_STATE before, OBJ_STATE after)
{
	if (before != eIDLE && after == eIDLE) 
		setAnimation(mAnimList[eIDLE]);
	if (before == eIDLE && after != eIDLE) 
		setAnimation(mAnimList[eWALKING]);
}
