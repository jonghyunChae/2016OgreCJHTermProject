#include "Character.h"

CCharacter::CCharacter() : CDynamicObject()
{
	mSceneMgr = nullptr;

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

void CCharacter::insertAnimationState(SceneNode * bodyRoot, OBJ_STATE state, string & meshName, string & animName)
{
	Entity * entity = mSceneMgr->createEntity(animName, meshName);
	SceneNode * node = bodyRoot->createChildSceneNode(animName);
	node->attachObject(entity);
	node->setVisible(false);

	mAnimList[state] = animName; 
}

void CCharacter::setAnimation(string name)
{
	if (mAnimationState) mAnimationState->setEnabled(false);

	mpEntity->setVisible(false);
	mpEntity = mSceneMgr->getEntity(name);
	mpEntity->setVisible(true);

	mAnimationState = mpEntity->getAnimationState("Anim");
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
