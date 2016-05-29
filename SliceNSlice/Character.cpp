#include "Character.h"

CCharacter::CCharacter() : CDynamicObject()
{
	mSceneMgr = nullptr;

	mAnimationState = nullptr;
	mCurrentNode = nullptr;
	mBeforeState = eIDLE;

	mOffsetVector = Vector3::ZERO;
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
	
#if 0
	Real animPos = mAnimationState->getTimePosition() * 100;
	if (mDir != Vector3::ZERO)
	{
		if (0.f == animPos)
		{
			_initNodeOffset();
		}
		else
		{
			Vector3 offset = -mDir * 600 * frameTime;
			mOffsetVector += offset;
			mCurrentNode->setPosition(mOffsetVector);
			Vector3 pos = mCurrentNode->getPosition();
			pos += Vector3::ZERO;
			
		}
	}
#endif
}

void CCharacter::insertAnimationState(SceneNode * bodyRoot, OBJ_STATE state, string & meshName, string & animName)
{
	Entity * entity = mSceneMgr->createEntity(animName, meshName);
	entity->setCastShadows(true);

	SceneNode * node = bodyRoot->createChildSceneNode(animName, Vector3::ZERO);
	node->attachObject(entity);
	node->setVisible(false);
	mCurrentNode = node;

	mAnimList[state] = animName; 
}

void CCharacter::setAnimation(string name)
{
	if (mAnimationState) mAnimationState->setEnabled(false);

	//mpEntity->setVisible(false);
	mpEntity = mSceneMgr->getEntity(name);
	mpEntity->setCastShadows(true);
	//mpEntity->setVisible(true);

	mCurrentNode->setVisible(false);
	mCurrentNode = mSceneMgr->getSceneNode(name);
	mCurrentNode->setVisible(true);

	mAnimationState = mpEntity->getAnimationState("Anim");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
	mAnimationState->setTimePosition(0);
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
	{
		_initNodeOffset();

		setAnimation(mAnimList[eIDLE]);
	}
	if (before == eIDLE && after != eIDLE) 
		setAnimation(mAnimList[eWALKING]);
}

void CCharacter::_initNodeOffset()
{
	mCurrentNode->setPosition(Vector3(0, 0, 0));
	//mCurrentNode->translate(mOffsetVector);
	mOffsetVector = Vector3::ZERO;
}